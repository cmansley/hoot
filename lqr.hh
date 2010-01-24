/*
 * Code by Chris Mansley
 */

#ifndef LQR_HH
#define LQR_HH

/* Definition dependencies */
#include <string>
#include <vector>

#include "planner.hh"
#include "chopper.hh"
#include "domain.hh"

class LQR : public Planner
{
public:
  /** Constructor */
  LQR(Domain *d, Chopper *c, double epsilon);

  /** Destructor */
  ~LQR() { }

  /** Initialize the planner */
  void initialize();

  /** Plan for one state */
  Action plan(State s);

  /** Restrict planner by queries */
  void setMaxQueries(int queries) { maxQueries = queries; }
};

#endif // LQR_HH
