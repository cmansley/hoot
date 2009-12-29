/* Implementation dependencies */
#include <iostream>
#include <algorithm>
#include <cmath>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "ccl.hh"

/*!
 *
 */
CCL::CCL(double gamma)
{
  /* Initialize our initial state */
  initialState.resize(stateDimension);
  std::fill(initialState.begin(), initialState.end(), 0.0);

  /* Create max and min range */
  maxRange.resize(stateDimension);
  minRange.resize(stateDimension);
  
  maxRange[0] = 1;
  minRange[0] = 0;

  /* Initialize gamma */
  this->gamma = gamma;
}

/*!
 *
 */
SARS *CCL::simulate(State s, Action a)
{
  //bookkeeping 

  return step(s, a);
}

/*!
 *
 */
SARS *CCL::step(State s, Action a)
{
  SARS *sars = new SARS();

  sars->s = s;
  sars->a = a;
  sars->reward = -1.0;

  /* Perform action */ 
  if(sars->a[0] == 0) {
    sars->s_prime[0] = 0.0;
  } else {
    sars->s_prime[0] = s[0] + 0.02 + gsl_ran_gaussian(rng, 0.005);
  }

  /* Check reward */ 
  if(sars->s_prime[0] > 0.98) {
    sars->terminal = true;
  } else {
    sars->terminal = false;
  }

  return sars;
}
