/*
 * Code by Chris Mansley
 */

#ifndef SARSA_HH
#define SARSA_HH

/* Definition dependencies */
#include <boost/unordered_map.hpp>

#include "planner.hh"
#include "sars.hh"

class SARSA : public Planner
{
public:
  /** Constructor */
  SARSA(Domain *d, Chopper *c, double epsilon);

  /** Destructor */
   ~SARSA( ) { }

  /** Initialize the planner */
  void initialize();

  /** Update SARSA with a SARSA */
  void updateValue(int depth, SARS *sars, double qvalue);

  /** Query action */
  Action plan(State s);

protected:
  /** Learning rate */
  double alpha;
  
  /** Algorithm Data Structures */
  boost::unordered_map<std::vector<int>, double> Q;

};

#endif // SARSA_HH
