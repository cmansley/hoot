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
#include "hoo.hh"

class HOOT : public MCPlanner
{
public:
  /** Constructor */
  HOOT(Domain *d, double epsilon);

  /** Destructor */
  ~HOOT() { }

  /** Initialize the planner */
  void initialize();

private:
  /** Local store of domain params */
  double gamma;
  double rmax;
  double rmin;
  double vmax;

  /** Algorithm Parameters/Variables */
  int maxDepth;
  int numInitialSamples;

  /** Algorithm Data Structures */
  boost::unordered_map<std::vector<int>, HOO*> HOOS;

  /** Algorithm Aux Functions */
  void updateValue(int depth, SARS *sars, double qvalue);
  Action selectAction(State s, int depth, bool greedy);

  /** Reset */
  void reset();

  /** Domain Dependent but Algorithm Defined */
  std::vector<int> discretizeState(State s);
};

#endif // HOOT_HH
