/*
 * Code by Chris Mansley
 */

#ifndef PLANNER_HH
#define PLANNER_HH

/* Definition dependencies */

#include "state.hh"
#include "action.hh"
#include "domain.hh"
#include "chopper.hh"

class Planner
{
public:
  /** Constructor */
  Planner(Domain *d, Chopper *c, double e) : domain(d), chopper(c), epsilon(e) { }
 
  /** Destructor */
  virtual ~Planner( ) { }

  /** Initialize planner */
  virtual void initialize(std::string filename) = 0;

  /** Plan for one state */
  virtual Action plan(State s) = 0;

  /** Restrict planner by queries */
  virtual void setMaxQueries(int queries) = 0;

  /** Print data structure */
  virtual void print(State s) = 0;

protected:
  /** Storage for domain */
  Domain *domain;

  /** Storage for discretizer */
  Chopper *chopper;

  /** Algorithm tolerence */
  double epsilon;

  /** Maximum number of generative model queries */
  int maxQueries;
};

#endif // PLANNER_HH
