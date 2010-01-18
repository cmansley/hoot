/* Implementation dependencies */
#include <iostream>
#include <algorithm>
#include <cmath>

#include "ip.hh"

const double IP::g = 9.8; // gravity constant in m/s^2
const double IP::mp = 2.0; // mass of pendulum in kg
const double IP::mc = 8.0; // mass of cart in kg
const double IP::l = 0.5; // length of pendulum in m
const double IP::dt = 0.1; // 100 ms update
const double IP::noise = 10.0; // noise from the Lagoudakis paper

/*!
 *
 */
IP::IP(double gamma)
{
  /* Initialize our initial state */
  initialState.resize(stateDimension);
  std::fill(initialState.begin(), initialState.end(), 0.0);

  /* Create max and min action range */
  maxStateRange.resize(stateDimension);
  minStateRange.resize(stateDimension);
  
  maxStateRange[0] = M_PI;
  minStateRange[0] = -M_PI;
  maxStateRange[1] = 8;
  minStateRange[1] = -8;

  maxActionRange.resize(actionDimension);
  minActionRange.resize(actionDimension);
  
  maxActionRange[0] = 50;
  minActionRange[0] = -50;

  /* Initialize gamma */
  this->gamma = gamma;

  /* Create constant*/
  alpha = 1.0/(mc+mp);    
}

/*!
 *
 */
SARS *IP::step(State s, Action a)
{
  SARS *sars = new SARS();

  sars->s = s;
  sars->a = a;

  /* Grab action */
  double u = a[0];

  /* 
   * Run the dynamics simulator using the state and action passed
   * in. The experiments in the paper used a large amount of
   * noise on the control input.
   */
  u += gsl_ran_flat(rng, -noise, noise);
  double acc = dynamics(s, u);

  /* 
   * Update the state variables based on the output of the
   * dynamics computation. This includes the time step. This
   * might be changed in the future to simulate faster, but only
   * allow dt control intervals
   */
  sars->s_prime[1] = s[1] + acc * dt;
  sars->s_prime[0] = s[0] + sars->s_prime[1] * dt;

  /*
   * Compute the reward function. If the pole falls below a
   * specified angle, the state becomes terminal and a large
   * reward accrues. Otherwise, the reward is generate as a
   * function of state and action, favoring small actions
   */
  if(fabs(sars->s_prime[0]) < M_PI_2) {
    sars->reward = -(pow(2 * sars->s_prime[0] / M_PI, 2.0) + pow(sars->s_prime[1], 2.0) + pow(u / 50, 2.0));
    sars->terminal = false;
  } else {
    sars->reward = -1000;
    sars->terminal = true;
  }

  /* 
   * Rescale reward the reward function to zero to one. This allows us
   * to standardize our algorithms to match most theoretical work
   */
  sars->reward = (1 - 0) / (0 - (-1000)) * (sars->reward - (-1000));

  return sars;
}

/*!
 *
 */
double IP::dynamics(State s, double u)
{

  double num, den;

  double theta = s[0];
  double theta_dot = s[1];

  num = g * sin(theta) - alpha * mp * l * pow(theta_dot, 2.0) * sin(2 * theta) / 2 - alpha * cos(theta) * u;
  den = 4.0 * l / 3.0 - alpha * mp * l * pow(cos(theta), 2.0);
    
  return num/den;
}
