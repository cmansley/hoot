/*
 * Code by Chris Mansley
 */

#ifndef MCPLANNER_HH
#define MCPLANNER_HH

/* Definition dependencies */

#include "state.hh"
#include "action.hh"
#include "planner.hh"
#include "domain.hh"
#include "chopper.hh"

class MCPlanner : public Planner
{
public:
  /** Constructor */
  MCPlanner(Domain *d, Chopper *c, double e) : Planner(d, c, e) { }
 
  /** Destructor */
  virtual ~MCPlanner( ) { }

  /** Plan for one state */
  Action plan(State s);

  /** Restrict planner by queries */
  void setMaxQueries(int queries);

protected:
  /** Maximum rollout depth */
  int maxDepth;

  /** Bookkeeping */
  int numInitialSamples;

  /** Search (or rollout) state space*/
  double search(int depth, State s, bool terminal);

  /** Update value */
  virtual void updateValue(int depth, SARS *sars, double qvalue) = 0;

  /** Select next action (greedily or not) */
  virtual Action selectAction(State s, int depth, bool greedy) = 0;

  /** Clear out data stuctures */
  virtual void reset() = 0;
};

#endif // MCPLANNER_HH
