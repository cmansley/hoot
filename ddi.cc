/* Implementation dependencies */
#include <iostream>
#include <algorithm>
#include <cmath>

#include "ddi.hh"

const double DDI::dt = 0.05; // 50 ms update
const double DDI::noise = 0.01; // noise 

/*!
 *
 */
DDI::DDI(double gamma) : stateDimension(2), actionDimension(1)
{
  /* Initialize our initial state */
  initialState.resize(stateDimension);
  for(int i=0; i<actionDimension; i++) {
    initialState[i] = 0.0;
    initialState[i+actionDimension] = 1.0;
  }

  /* Create max and min action range */
  maxStateRange.resize(stateDimension);
  minStateRange.resize(stateDimension);

  std::fill(maxStateRange.begin(), maxStateRange.end(), 2.0);
  std::fill(minStateRange.begin(), minStateRange.end(), -2.0);
  
  maxActionRange.resize(actionDimension);
  minActionRange.resize(actionDimension);

  std::fill(maxActionRange.begin(), maxActionRange.end(), 2.0);
  std::fill(minActionRange.begin(), minActionRange.end(), -2.0);

  /* Initialize gamma */
  this->gamma = gamma;
}

void DDI::setParam(double d, int i)
{
  actionDimension = i; 
  stateDimension = 2*i; 

  /* Initialize our initial state */
  initialState.resize(stateDimension);
  for(int i=0; i<actionDimension; i++) {
    initialState[i] = 0.0;
    initialState[i+actionDimension] = 1.0;
  }

  /* Create max and min action range */
  maxStateRange.resize(stateDimension);
  minStateRange.resize(stateDimension);

  std::fill(maxStateRange.begin(), maxStateRange.end(), 2.0);
  std::fill(minStateRange.begin(), minStateRange.end(), -2.0);
  
  maxActionRange.resize(actionDimension);
  minActionRange.resize(actionDimension);

  std::fill(maxActionRange.begin(), maxActionRange.end(), 2.0);
  std::fill(minActionRange.begin(), minActionRange.end(), -2.0);

}

/*!
 *
 */
SARS *DDI::step(State s, Action a)
{
  SARS *sars = new SARS(stateDimension, actionDimension);

  sars->s = s;
  sars->a = a;

  /* 
   * Compute update step. This is simple linear dynamics with noise
   * added. A = [1 0;dt 1] and B = [dt 0]
   */
  unsigned int numActions = a.size();
  for(unsigned int i=0; i<numActions; i++) {
    sars->s_prime[i] = s[i] + a[i] * dt;// + gsl_ran_flat(rng, -noise, noise);
    sars->s_prime[i+numActions] = s[i+numActions] + s[i] * dt;// + gsl_ran_flat(rng, -noise, noise);
  }

  /*
   * Reward function is a simple quadratic reward with Q = [0 0; 0 1]
   * and R = [1]. For some reason, we convert this to reward instead
   * of cost as the LQR forumulation states.
   */
  sars->reward = 0.0;
  for(unsigned int i=0; i<numActions; i++) {
    sars->reward += pow(sars->s[i+numActions],2) + pow(a[i],2);
  }
  sars->reward = -sars->reward;

  /*
   * Terminate if we exceed operating parameters. This may or may not
   * change optimal policies.
   */ 
  sars->terminal = false;
  for(unsigned int i = 0; i<sars->s_prime.size(); i++) {
    if(sars->s_prime[i] > maxStateRange[i] || sars->s_prime[i] < minStateRange[i]) {
      sars->terminal = true;
    }
  }

  /* 
   * Rescale reward the reward function to zero to one. This allows us
   * to standardize our algorithms to match most theoretical work
   */
  sars->reward = (1.0 - 0.0) / (0.0 - (-8*actionDimension)) * (sars->reward - (-8*actionDimension));

  return sars;
}
