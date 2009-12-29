/*
 * Code by Chris Mansley
 */

#ifndef PLANNER_HH
#define PLANNER_HH

/* Definition dependencies */

#include "state.hh"
#include "action.hh"
#include "domain.hh"

class Planner
{
public:
  /** Constructor */
  Planner(Domain *d, double e) : domain(d), epsilon(e) { }
 
  /** Destructor */
  virtual ~Planner( ) { }

  /** Initialize planner */
  virtual void initialize() = 0;

  /** Plan for one state */
  virtual Action plan(State s) = 0;

  /** Restrict planner by queries */
  void setMaxQueries(int queries) { maxQueries = queries; }

protected:
  /** Storage for domain */
  Domain *domain;

  /** Algorithm tolerence */
  double epsilon;

  /** Maximum number of generative model queries */
  int maxQueries;
};

#endif // PLANNER_HH
