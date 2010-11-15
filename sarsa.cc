/*
 * Code by Chris Mansley
 */
#include <iostream>
#include <iterator>
#include <cmath>

#include "sarsa.hh"


SARSA::SARSA(Domain *d, Chopper *c, double epsilon) : Planner(d, c, epsilon)
{
  alpha = 0.1;
}

/*
 *
 */
void SARSA::initialize()
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
void SARSA::updateValue(int depth, SARS *sars, double qvalue)
{
  /* Create vector of ints for state, action and depth */
  std::vector<int> sd = chopper->discretizeState(sars->s);
  int da;
  std::vector<int> sad = sd;
  sd.push_back(depth);
  sad.push_back(depth);
  sad.push_back(0);

  /* max Q step */
  da = chopper->discretizeAction(selectAction(sars->s_prime, 0, false));
  sad.back() = da;
  double q_prime;
  if(Q.find(sad) != Q.end()) {
    q_prime = Q[sad];
  } else {
    /* Uninformative initialization */
    q_prime = 0;
  }

  /* Find Q value */
  da = chopper->discretizeAction(sars->a);
  sad.back() = da;
  double q;
  if(Q.find(sad) != Q.end()) {
    q = Q[sad];
  } else {
    /* Uninformative initialization */
    q = 0;
  }  

  /* SARSA rule */
  Q[sad] = q + alpha*(sars->reward + gamma*q_prime - q);
}

/*
 *
 */
Action SARSA::selectAction(State s, int depth, bool greedy)
{
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
      /* Store Q-value */
      qtemp.push_back(Q[sad]);
    } else {
      qtemp.push_back(0);
    }
  }

  /* Create max action or random if there are more than one */
  int discreteAction;

  /* Grab max action */
  std::vector<double>::const_iterator largest = max_element(qtemp.begin(), qtemp.end());
  discreteAction = largest - qtemp.begin();

  Action a = chopper->continuousAction(discreteAction);

  return a;
}
