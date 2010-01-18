/*
 * Code by Chris Mansley
 */
#include <iostream>
#include <cmath>

#include "uct.hh"


UCT::UCT(Domain *d, Chopper *c, double epsilon) : MCPlanner(d, c, epsilon)
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
void UCT::updateValue(int depth, SARS *sars, double qvalue)
{
  /* Create vector of ints for state, action and depth */
  std::vector<int> sd = chopper->discretizeState(sars->s);
  int da = chopper->discretizeAction(sars->a);
  std::vector<int> sad = sd;
  sd.push_back(depth);
  sad.push_back(depth);
  sad.push_back(da);

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

  int k = chopper->getNumDiscreteActions();

  /* Create vector of ints for state, action and depth */
  std::vector<int> sd = chopper->discretizeState(s);
  std::vector<int> sad = sd;
  sd.push_back(depth);
  sad.push_back(depth);
  sad.push_back(0); // action slot

  /* Grab the Q-value for this state action */
  int nsd_temp = Nsd[sd];
  double c;
  std::vector<double> qtemp;
  for(int action=0; action < k; action++) {
    sad.back() = action;
    if(Q.find(sad) != Q.end()) {
      /* Do not include bonus term in greedy operation */
      c = 0;
      if(!greedy) {
	c = sqrt(2 * log(nsd_temp) / (float) Nsad[sad]);
      }
      /* Store Q-value plus bonus term*/
      qtemp.push_back(Q[sad] + c);
    } else {
      qtemp.push_back(vmax);
      vmaxActions.push_back(action);
    }

  }

  /* Create max action or random if there are more than one */
  int discreteAction;
  if(vmaxActions.empty()) {
    /* Grab max action */
    std::vector<double>::const_iterator largest = max_element(qtemp.begin(), qtemp.end());
    discreteAction = largest - qtemp.begin();
  } else {
    random_shuffle(vmaxActions.begin(), vmaxActions.end());
    discreteAction = vmaxActions[0];
  }

  Action a = chopper->continuousAction(discreteAction);

  return a;
}

/*
 *
 */
void UCT::reset()
{
  /* Clear out data structues */
  Nsd.clear();
  Nsad.clear();
  Q.clear();  
}
