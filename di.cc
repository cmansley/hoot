/* Implementation dependencies */
#include <iostream>
#include <algorithm>
#include <cmath>

#include "di.hh"

const double DI::dt = 0.05; // 50 ms update
const double DI::noise = 0.01; // noise 

/*!
 *
 */
DI::DI(double gamma)
{
  /* Initialize our initial state */
  initialState.resize(stateDimension);
  initialState[0] = 0.0;
  initialState[1] = 1.0;

  /* Create max and min action range */
  maxStateRange.resize(stateDimension);
  minStateRange.resize(stateDimension);
  
  maxStateRange[0] = 2;
  minStateRange[0] = -2;
  maxStateRange[1] = 2;
  minStateRange[1] = -2;

  maxActionRange.resize(actionDimension);
  minActionRange.resize(actionDimension);
  
  maxActionRange[0] = 2;
  minActionRange[0] = -2;

  /* Initialize gamma */
  this->gamma = gamma;
}

/*!
 *
 */
SARS *DI::step(State s, Action a)
{
  SARS *sars = new SARS();

  sars->s = s;
  sars->a = a;

  /* Grab action */
  double u = a[0];

  /* 
   * Compute update step. This is simple linear dynamics with noise
   * added. A = [1 0;dt 1] and B = [dt 0]
   */
  sars->s_prime[0] = s[0] + u * dt + gsl_ran_flat(rng, -noise, noise);
  sars->s_prime[1] = s[1] + s[0] * dt + gsl_ran_flat(rng, -noise, noise);

  /*
   * Reward function is a simple quadratic reward with Q = [0 0; 0 1]
   * and R = [1]. For some reason, we convert this to reward instead
   * of cost as the LQR forumulation states.
   */
  sars->reward = -(pow(sars->s[1],2) + pow(u,2));

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
  sars->reward = (1.0 - 0.0) / (0.0 - (-4)) * (sars->reward - (-4));

  return sars;
}
