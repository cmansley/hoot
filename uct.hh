/*
 * Code by Chris Mansley
 */

#ifndef UCT_HH
#define UCT_HH

/* Definition dependencies */
//#include <map>
#include <boost/unordered_map.hpp>
#include <string>
#include <vector>

#include "mcplanner.hh"
#include "domain.hh"

class UCT : public MCPlanner
{
public:
  /** Constructor */
  UCT(Domain *d, double epsilon);

  /** Destructor */
  ~UCT() { }

  /** Initialize the planner */
  void initialize();

private:
  /** Local store of domain params */
  double gamma;
  double rmax;
  double rmin;
  double vmax;

  /** Algorithm Data Structures */
  //std::map<std::vector<int>, int> Nsd;
  //std::map<std::vector<int>, int> Nsad;
  //std::map<std::vector<int>, double> Q;
  boost::unordered_map<std::vector<int>, int> Nsd;
  boost::unordered_map<std::vector<int>, int> Nsad;
  boost::unordered_map<std::vector<int>, double> Q;

  /** Update value */
  void updateValue(int depth, SARS *sars, double qvalue);
  
  /** Select next action (greedily or not) */
  Action selectAction(State s, int depth, bool greedy);

  /** Clear out data stuctures */
  void reset();

  /** Domain Dependent but Algorithm Defined */
  std::vector<int> discretizeState(State S);
  int discretizeAction(Action a);
  Action continuousAction(int a);
};

#endif // UCT_HH
