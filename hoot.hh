/*
 * Code by Chris Mansley
 */

#ifndef HOOT_HH
#define HOOT_HH

/* Definition dependencies */
#include <boost/unordered_map.hpp>
#include <string>
#include <vector>

#include "mcplanner.hh"
#include "domain.hh"
#include "chopper.hh"
#include "hoo.hh"

class HOOT : public MCPlanner
{
public:
  /** Constructor */
  HOOT(Domain *d, Chopper *c, double epsilon);

  /** Destructor */
  ~HOOT() { /* Possible mem clean up? */ }

  /** Initialize the planner */
  void initialize(std::string filename);

  void print(State s);

private:
  /** Algorithm Data Structures */
  boost::unordered_map<std::vector<int>, HOO*> HOOS;

  /** Update value */
  void updateValue(int depth, SARS *sars, double qvalue);
  
  /** Select next action (greedily or not) */
  Action selectAction(State s, int depth, bool greedy);

  /** Clear out data stuctures */
  void reset();
};

#endif // HOOT_HH
