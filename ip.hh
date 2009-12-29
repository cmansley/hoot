/*
 * Code by Chris Mansley
 */

#ifndef IP_HH
#define IP_HH

/* Definition dependencies */


#include "domain.hh"

/*!
 *
 */
class IP: public Domain
{
public:
  /** Constructor */
  IP(double gamma);

  /** Destructor */
  ~IP() { }

  /** Perform an interaction with the environment */
  SARS *step(State s, Action a);

  /** Get starting state from domain */
  State getInitialState( ) { return initialState; }

  /** Get number of discrete actions for domain */
  int getNumActions( ) { return numActions; }

  /** Get discount factor for domain */
  double getDiscountFactor( ) { return gamma; }

  /** Get maximum range for state features */
  std::vector<double> getMaximumRange( ) { return maxRange; }

  /** Get maximum range for state features */
  std::vector<double> getMinimumRange( ) { return minRange; }

  /** Get maximum reward */
  double getRmax( ) { return rmax; }

  /** Get minimum reward */
  double getRmin( ) { return rmin; }

private:
  /** Store starting state */
  State initialState;

  /** Domain Parameters */
  std::vector<double> maxRange;
  std::vector<double> minRange;
  static const int stateDimension = 2;
  static const int actionDimension = 1;
  //static const double rmin = -1000;
  //static const double rmax = 0;
  static const double rmin = 0;
  static const double rmax = 1;

  // only if discrete actions
  static const int numActions = 20;

  /** Domain Properties */
  double gamma;

  /** Domain Specific */
  static const double g;
  static const double mp;
  static const double mc;
  static const double l;
  static const double dt;
  static const double noise;
  double alpha;

  double dynamics(State s, double a);
};

#endif // DOMAIN_HH
