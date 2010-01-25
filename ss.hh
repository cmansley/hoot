/*
 * Code by Chris Mansley
 */

#ifndef SS_HH
#define SS_HH

/* Definition dependencies */
#include <vector>

#include "planner.hh"
#include "state.hh"
#include "action.hh"
#include "domain.hh"
#include "chopper.hh"

class SS : public Planner
{
public:
  /** Constructor */
  SS(Domain *d, Chopper *c, double epsilon);

  /** Destructor */
  ~SS() { }

  /** Plan for one state */
  Action plan(State s);
  
  /** Restrict planner by queries */
  void setMaxQueries(int queries);

private:
  /** Estimate the Q-value */
  std::vector<double> estimateQ(int h, State s);

  /** Estimate the value */
  double estimateV(int h, State s);

  /** Algorithm Parameters */
  int C;
  int H;

  /** Local cache */
  double gamma;
};

#endif // SS_HH
