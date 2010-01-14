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

#include "planner.hh"
#include "domain.hh"

class UCT : public Planner
{
public:
  /** Constructor */
  UCT(Domain *d, double epsilon);

  /** Destructor */
  ~UCT() { }

  /** Initialize the planner */
  void initialize();

  /** Plan for one state */
  Action plan(State s);

  /** Restrict planner by queries */
  void setMaxQueries(int queries);

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
  //std::map<std::vector<int>, int> Nsd;
  //std::map<std::vector<int>, int> Nsad;
  //std::map<std::vector<int>, double> Q;
  boost::unordered_map<std::vector<int>, int> Nsd;
  boost::unordered_map<std::vector<int>, int> Nsad;
  boost::unordered_map<std::vector<int>, double> Q;

  /** Algorithm Aux Functions */
  double search(int depth, State s, bool terminal);
  void updateValue(int depth, SARS *sars, double qvalue);
  // Combine the next functions with a greedy boolean
  Action selectAction(State s, int depth, bool greedy);

  /** Domain Dependent but Algorithm Defined */
  std::vector<int> discretizeState(State S);
  int discretizeAction(Action a);
  Action continuousAction(int a);
};

#endif // UCT_HH
