/*
 * Code by Chris Mansley
 */

#ifndef SARSA_HH
#define SARSA_HH

/* Definition dependencies */
#include <fstream>
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
  void initialize(std::string filename);

  /** Query action */
  Action plan(State s);

  /** Restrict planner by queries */
  void setMaxQueries(int queries) { }

  /** Print data structure */
  void print(State s) { }

protected:
  /** Learning rate */
  double alpha;

  /** Local domain parameters */
  double gamma;
  int stateDimension;
  int actionDimension;

  /** Algorithm Data Structures */
  boost::unordered_map<std::vector<int>, double> Q;

  /** Logfile */
  std::ifstream logfile;

  /** Parse logfile */
  void parseData(std::string filename);
};

#endif // SARSA_HH
