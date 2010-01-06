/*
 * Code by Chris Mansley
 */

#ifndef MCPLANNER_HH
#define MCPLANNER_HH

/* Definition dependencies */

#include "state.hh"
#include "action.hh"
#include "domain.hh"

class MCPlanner
{
public:
  /** Constructor */
  MCPlanner(Domain *d, double e) : Planner(d, epsilon) { }
 
  /** Destructor */
  virtual ~Planner( ) { }

  /** Plan for one state */
  Action plan(State s);

  /** Restrict planner by queries */
  void setMaxQueries(int queries);

protected:
  /** Search (or rollout) state space*/
  double search(int depth, State s, bool terminal);

  /** Update value */
  virtual void updateValue(int depth, SARS *sars, double qvalue) = 0;

  virtual Action selectAction(State s, int depth, bool greedy) = 0;
};

#endif // MCPLANNER_HH
