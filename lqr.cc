/*
 * Code by Chris Mansley
 */
#include <iostream>
#include <iterator>
#include <cmath>

#include "lqr.hh"


LQR::LQR(Domain *d, Chopper *c, double epsilon) : Planner(d, c, epsilon)
{
}

/*
 *
 */
void LQR::initialize(std::string filename)
{
}

Action LQR::plan(State s)
{
  Action a(domain->getActionDimension());

  for(unsigned int i=0; i<a.size(); i++) {
    a[i] = -(s[i]*sqrt(2) + s[i+a.size()]);
  }

  return a;
}
