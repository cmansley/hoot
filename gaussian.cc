/* Implementation dependencies */
#include <iostream>
#include <algorithm>
#include <cmath>

#include "gaussian.hh"

/*!
 *
 */
Gaussian::Gaussian()
{
  /* Initialize our initial state */
  initialState.resize(stateDimension);
  std::fill(initialState.begin(), initialState.end(), 0.0);

  /* Create max and min state range */
  maxStateRange.resize(stateDimension);
  minStateRange.resize(stateDimension);
  std::fill(minStateRange.begin(), minStateRange.end(), 0.0);
  std::fill(maxStateRange.begin(), maxStateRange.end(), 0.0);

  /* Create max and min action range */
  maxActionRange.resize(actionDimension);
  minActionRange.resize(actionDimension);
  maxActionRange[0] = 1;
  minActionRange[0] = 0;
  maxActionRange[1] = 1;
  minActionRange[1] = 0;

  /* Create params */
  mu.resize(actionDimension);
  diag.resize(actionDimension);
  mu[0] = 0.5;
  mu[1] = 0.5;
  diag[0] = 0.001;
  diag[1] = 0.01;
}

/*!
 *
 */
SARS *Gaussian::step(State s, Action a)
{
  SARS *sars = new SARS();

  sars->s = s;
  sars->a = a;
  sars->s_prime = s;

  double det = 1.0;
  for(unsigned int i=0; i<diag.size(); i++) {
    det *= diag[i];
  }

  double temp = 0.0;
  for(unsigned int i=0; i<diag.size(); i++) {
    temp += (a[i] - mu[i]) * 1 / diag[i] * (a[i] - mu[i]);
  }

  //double reward = 1 / (pow((2*M_PI), actionDimension/2) * sqrt(det)) * exp(-0.5*temp);
  double reward = exp(-0.5*temp);

  reward += gsl_ran_flat(rng, -0.05, 0.05);
  
  if(reward < 0.0) {
    reward = 0.0;
  } else if(reward > 1.0) {
    reward = 1.0;
  }
  
  sars->reward = reward;
  sars->terminal = false;

  return sars;
}
