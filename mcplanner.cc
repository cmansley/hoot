#include <iostream>

#include "mcplanner.hh"

/*
 *
 */
void MCPlanner::setMaxQueries(int queries)
{
  /* Store sweet queries */
  maxQueries = queries;

  /* Set max depth here based on some cool math */
  // maxDepth = logblah blah FIXME
  maxDepth = 100;
}

/*
 *
 */
Action MCPlanner::plan(State s)
{
  /* Clear out data structues */
  reset();

  /* Store initial number of simulated steps */
  numInitialSamples = domain->getNumSamples();
  
  /* Do your rollouts */
  while((domain->getNumSamples() - numInitialSamples) < maxQueries) {
    search(0, s, false);
  }

  /* Return the greedy action */
  Action a = selectAction(s, 0, true);
          
  return a;
}

/*
 *
 */
double MCPlanner::search(int depth, State s, bool terminal)
{
  double q;

  /* Terminate if a terminal state has been reached */
  if(terminal) {
    return 0;
  }

  /* Return if exceeded the maximum rollout depth 
   * (possible use a heuristic instead of zero) 
   */
  if(depth > maxDepth) {
    return 0;
  }

  /* select the next action non-greedily 
   * in other words according to some heuristic */
  Action a = selectAction(s, depth, false);

  /* Sample next state from generative model */
  SARS *sars = domain->simulate(s,a);  

  /* Compute the Q-value */
  q = sars->reward + domain->getDiscountFactor() * search(depth + 1, sars->s_prime, sars->terminal);
  
  /* Update the Q-value (only if we have not exceeded our samples */
  if((domain->getNumSamples() - numInitialSamples) < maxQueries) {   // Pretty me?
    updateValue(depth, sars, q);
  }

  delete sars;

  return q;
}
