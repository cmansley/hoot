/*
 * Code by Chris Mansley
 */
#include <iostream>
#include <cmath>

#include "uct.hh"


UCT::UCT(Domain *d, double epsilon) : Planner(d, epsilon)
{
}

/*
 *
 */
void UCT::initialize()
{
  /* Locally store values and compute vmax */
  rmax = domain->getRmax();
  rmin = domain->getRmin();
  gamma = domain->getDiscountFactor();
  vmax = rmax/(1-gamma);
}

/*
 *
 */
void UCT::setMaxQueries(int queries)
{
  /* Sort sweet queries */
  maxQueries = queries;

  /* Set max depth here based on some cool math */
  // maxDepth = logblah blah 
  maxDepth = 100;
}

/*
 *
 */
Action UCT::plan(State s)
{
  /* Clear out data structues */
  Nsd.clear();
  Nsad.clear();
  Q.clear();  

  /* Store initial number of simulated steps */
  numInitialSamples = domain->getNumSamples();
  
  /* Do your rollouts */
  while((domain->getNumSamples() - numInitialSamples) < maxQueries) {
    search(0, s, false);
  }

  Action a(1);
  a = selectAction(s, 0, true);
          
  return a;
}


/*
 *
 */
double UCT::search(int depth, State s, bool terminal)
{
  double q;

  /* Terminate if a terminal state has been reached */
  if(terminal) {
    return 0;
  }

  /* Return if exceeded the maximum rollout depth (possible use a
   * heuristic not zero) 
   */
  if(depth > maxDepth) {
    return 0;
  }

  /* select the next action according to the UCT heuristic */
  Action a(1);
  a = selectAction(s, depth, false);

  /* Sample next state from generative model */
  SARS *sars = domain->simulate(s,a);  

  /* Compute the Q-value */
  q = sars->reward + gamma * search(depth + 1, sars->s_prime, sars->terminal);
  
  /* Update the Q-value (only if we have not exceeded our samples */
  if((domain->getNumSamples() - numInitialSamples) < maxQueries) {
    updateValue(depth, sars, q);
  }

  delete sars;

  return q;
}

/*
 *
 */
void UCT::updateValue(int depth, SARS *sars, double qvalue)
{
  /* Create vector of ints for state, action and depth */
  std::vector<int> sd = discretizeState(sars->s);
  std::vector<int> sad = sd;
  sd.push_back(depth);
  sad.push_back(depth);
  sad.push_back(sars->a[0]);

  /* Update counts */
  Nsd[sd] += 1 ;
  Nsad[sad] += 1;
  
  /* Compute mean of Q-values via Knuth */
  int n; double mean, delta;
  if(Q.find(sad) != Q.end()) {
    n = Nsad[sad];
    mean = Q[sad];
    delta = qvalue - mean;
    Q[sad] = mean + delta/n;
  } else {
    Q[sad] = qvalue;  
  }

}

/*
 *
 */
Action UCT::selectAction(State s, int depth, bool greedy)
{
  std::vector<int> vmaxActions;

  int k = domain->getNumActions();

  /* Create vector of ints for state, action and depth */
  std::vector<int> sd = discretizeState(s);
  std::vector<int> sad = sd;
  sd.push_back(depth);
  sad.push_back(depth);
  sad.push_back(0); // action slot

  /* Grab the Q-value for this state action*/
  double rewardRange = (rmax-rmin) * (rmax-rmin);
  int nsd_temp = Nsd[sd];
  double c;
  std::vector<double> qtemp;
  for(int action=0; action < k; action++) {
    sad.back() = action;
    if(Q.find(sad) != Q.end()) {
      /* Do not include bonus term in greedy operation*/
      c = 0;
      if(!greedy) {
	c = sqrt(rewardRange * log(nsd_temp) / (float) Nsad[sad]);
      }
      /* Store Q-value plus bonus term*/
      qtemp.push_back(Q[sad] + c);
    } else {
      qtemp.push_back(vmax);
      vmaxActions.push_back(action);
    }

  }

  /* Create max action or random if there are more than one */
  Action a(1);
  if(vmaxActions.empty()) {
    /* Grab max action */
    std::vector<double>::const_iterator largest = max_element(qtemp.begin(), qtemp.end());
    a[0] = largest - qtemp.begin();
  } else {
    random_shuffle(vmaxActions.begin(), vmaxActions.end());
    a[0] = vmaxActions[0];
  }
  
  return a;
}

/*
 *
 */
std::vector<int> UCT::discretizeState(State s)
{
  std::vector<int> ds;
  
  /* Random Discretization - BE AFRAID */
  int numofgrids = 20;

  /* Get range of attributes */
  std::vector<double> maxRange = domain->getMaximumStateRange();
  std::vector<double> minRange = domain->getMinimumStateRange();
 
  int temp;
  for(unsigned int i=0; i<s.size(); i++) {
    temp = (int) floor(numofgrids / (maxRange[i] - minRange[i]) * (s[i] - minRange[i]));
    ds.push_back(temp);
  }

  return ds;
}
