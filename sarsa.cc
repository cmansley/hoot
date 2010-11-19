/*
 * Code by Chris Mansley
 */
#include <fstream>
#include <iterator>
#include <cmath>

#include "sarsa.hh"


SARSA::SARSA(Domain *d, Chopper *c, double epsilon) : Planner(d, c, epsilon)
{
  alpha = 0.9;
}

/*
 *
 */
void SARSA::initialize(std::string filename)
{
  /* Locally store gamma */
  gamma = domain->getDiscountFactor();
  stateDimension = domain->getStateDimension();
  actionDimension = domain->getActionDimension();

  /*Parse log file data */
  parseData(filename);
}

/*
 *
 */
void SARSA::parseData(std::string infile)
{
  SARS *sars = new SARS(stateDimension, actionDimension);
  SARS *nextSARS = new SARS(stateDimension, actionDimension);
  double q, q_prime;

  /* Open log file */
  logfile.open(infile.c_str());

  for(int i=0; i<100; i++) {

    /* Always grab at least one */
    logfile >> *sars;

    while(!logfile.eof()) {
      /* Parse log file */
      logfile >> *nextSARS;

      /* Don't process samples straddling a terminal */
      if(!sars->terminal) {

	/* Grab Q-values for next state and this state */
	std::vector<int> sa = chopper->discretizeState(nextSARS->s);
	int a = chopper->discretizeAction(nextSARS->a);
	sa.push_back(a);
	q_prime = Q[sa]; /* depends on map initializing to default of 0.0 */
      
	sa = chopper->discretizeState(sars->s);
	a = chopper->discretizeAction(sars->a);
	sa.push_back(a);
	q = Q[sa]; /* depends on map initializing to default of 0.0 */
      
	/* SARSA rule */
	Q[sa] = q + alpha*(sars->reward + gamma*q_prime - q);      
      }

      /* Attempting deep copy may not work */
      *sars = *nextSARS;
    }

    logfile.clear();
    logfile.seekg(0);
  }

  /* Close log file */
  logfile.close();
}

/*
 *
 */
Action SARSA::plan(State s)
{
  int k = chopper->getNumDiscreteActions();

  /* Create vector of ints for state and action*/
  std::vector<int> sad = chopper->discretizeState(s);
  sad.push_back(0); // action slot

  /* Grab the Q-value for this state action */
  std::vector<double> qtemp;
  for(int action=0; action < k; action++) {

    sad.back() = action;

    /* Store Q-value */
    if(Q.find(sad) != Q.end()) {
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
