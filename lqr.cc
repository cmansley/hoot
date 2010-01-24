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
void LQR::initialize()
{
}

Action LQR::plan(State s)
{
  Action a(1);

  a[0] = -(s[0]*sqrt(2) + s[1]);

  return a;
}
