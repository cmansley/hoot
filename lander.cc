/* Implementation dependencies */
#include <iostream>
#include <algorithm>
#include <cmath>
#include <boost/math/special_functions/atanh.hpp>
#include "lander.hh"

const double Lander::kg = 0.2;
const double Lander::kf = 2.0;
const double Lander::c = 1.0;
const double Lander::dt = 1.0;


/*!
 *
 */
Lander::Lander(double gamma)
{
  /* Initialize our initial state */
  initialState.resize(stateDimension);  

  /* Create max and min range */
  maxRange.resize(stateDimension);
  minRange.resize(stateDimension);
  
  maxRange[0] = 10.0;
  minRange[0] = 0.0;
  maxRange[1] = 20;
  minRange[1] = -20;
  maxRange[2] = 400.0;
  minRange[2] = 0.0;

  /* Initialize gamma */
  this->gamma = gamma;
}

/*!
 *
 */
State Lander::getInitialState() 
{
  /* Random start state */
  initialState[0] = gsl_ran_flat(rng, 90.0, 100.0);
  initialState[1] = gsl_ran_flat(rng, -1, 1);
  initialState[2] = 400.0;

  return initialState;
}

/*!
 *
 */
SARS *Lander::step(State s, Action a)
{
  SARS *sars = new SARS();

  sars->s = s;
  sars->a = a;

  /* Works only for discrete actions */
  double arange = 1;
  double alower = 0;
  double u = arange * a[0] / (numActions- 1) - alower;

  sars->s_prime[0] = s[0] + s[1] * dt;
  sars->s_prime[1] = s[1] + (u - kg) * dt;
  sars->s_prime[2] = s[2] + -u * dt;

  /* Impulse reward for terminal state */
  if(sars->s_prime[0] <= 0.0 || sars->s_prime[2] <= 0.0) {
    sars->reward = -sars->s_prime[1]*sars->s_prime[1] - 2*kg*sars->s_prime[0];
    sars->terminal = true;
  }



  // FIX Reward Signal
  if(fabs(sars->s_prime[0]) < M_PI_2) {
    sars->reward = -(pow(2 * sars->s_prime[0] / M_PI, 2.0) + pow(sars->s_prime[1], 2.0) + pow(u / 50, 2.0));
    sars->terminal = false;
  } else {
    sars->reward = -1000;
    sars->terminal = true;
  }        

  return sars;
}


/*!
 *
 */
double Lander::rC(double action)
{
  double r;

  double term1 = action*atanh(1 - 2*action) - 0.5*log(1 - action);
  double term2 = 0.5*atanh(0) - 0.5*log(0.5);

  r = c*(term1-term2);

  return r;
}
