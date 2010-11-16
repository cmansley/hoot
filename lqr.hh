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
  void initialize(std::string filename);

  /** Plan for one state */
  Action plan(State s);

  /** Restrict planner by queries */
  void setMaxQueries(int queries) { maxQueries = queries; }

  /** Print data structure */
  void print(State s) {};
};

#endif // LQR_HH
