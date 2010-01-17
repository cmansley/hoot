/*
 * Code by Chris Mansley
 */
#include <iostream>
#include <cmath>

#include "uct.hh"


UCT::UCT(Domain *d, double epsilon) : MCPlanner(d, epsilon)
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
  std::vector<int> sd = domain->discretizeState(sars->s);
  int da = discretizeAction(sars->a);
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

  int k = domain->getNumDiscreteActions();

  /* Create vector of ints for state, action and depth */
  std::vector<int> sd = domain->discretizeState(s);
  std::vector<int> sad = sd;
  sd.push_back(depth);
  sad.push_back(depth);
  sad.push_back(0); // action slot

  /* Grab the Q-value for this state action */
  double rewardRange = (rmax-rmin) * (rmax-rmin);
  int nsd_temp = Nsd[sd];
  double c;
  std::vector<double> qtemp;
  for(int action=0; action < k; action++) {
    sad.back() = action;
    if(Q.find(sad) != Q.end()) {
      /* Do not include bonus term in greedy operation */
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
  int discreteAction;
  if(vmaxActions.empty()) {
    /* Grab max action */
    std::vector<double>::const_iterator largest = max_element(qtemp.begin(), qtemp.end());
    discreteAction = largest - qtemp.begin();
  } else {
    random_shuffle(vmaxActions.begin(), vmaxActions.end());
    discreteAction = vmaxActions[0];
  }

  Action a = continuousAction(discreteAction);

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

/*
 *
 */
int UCT::discretizeAction(Action a)
{  
  /* Random Discretization - FIX ME */
  int numofgrids = domain->getNumDiscreteActions();

  /* Get range of attributes */
  std::vector<double> maxRange = domain->getMaximumActionRange();
  std::vector<double> minRange = domain->getMinimumActionRange();
 
  int id = 0;
  int temp;
  for(unsigned int i=0; i<a.size(); i++) {
    id *= numofgrids;

    temp = (int) floor(numofgrids / (maxRange[i] - minRange[i]) * (a[i] - minRange[i]));
    /* Handle upper end */
    if(temp == numofgrids) {
      temp = temp - 1;
    }

    id += temp;
    
  }

  return temp;
}


/*
 *
 */
Action UCT::continuousAction(int a)
{
  Action action;
  
  /* Must bubble this parameter up to the top */
  int numofgrids = domain->getNumDiscreteActions();

  /* Get range of attributes */
  std::vector<double> maxRange = domain->getMaximumActionRange();
  std::vector<double> minRange = domain->getMinimumActionRange();

  /* Convert to tuple of continuous numbers */
  int temp;
  double u;
  unsigned int i = 0;
  for(i = 0; i < maxRange.size()-1; i++) {
    temp = a % numofgrids;
    u = (maxRange[i] - minRange[i]) * a / (numofgrids - 1) + minRange[i];
    action.push_back(u);
    a = (a - temp) / numofgrids;
  }

  u = (maxRange[i] - minRange[i]) * a / (numofgrids - 1) + minRange[i];
  action.push_back(u);
  
  return action;
}
