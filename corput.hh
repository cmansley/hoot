/*
 * Code by Chris Mansley
 */

#ifndef CORPUT_HH
#define CORPUT_HH

/* Definition dependencies */
#include <map>
#include <string>
#include <vector>

#include "planner.hh"
#include "domain.hh"

class Corput : public Planner
{
public:
  /** Constructor */
  Corput(Domain *d, double epsilon);

  /** Destructor */
  ~Corput() { }

  /** Plan for one state */
  Action plan(State s);

private:
  /** Algorithm Parameters */
  int maxDepth;

  /** Algorithm Data Structures */
  std::map<std::vector<int>, int> Nsd;
  std::map<std::vector<int>, int> Nsad;
  std::map<std::vector<int>, double> Q;

  /** Algorithm Aux Functions */
  double search(int depth, State s, bool terminal);
  void updateValue(int depth, SARS *sars, double qvalue);
  Action getBestAction(State s);
  Action selectAction(State s, int depth);
  std::vector<int> discretizeState(State S);
};

#endif // CORPUT_HH
