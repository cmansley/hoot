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

  /** Get discount factor for domain */
  double getDiscountFactor( ) { return gamma; }

  /** Get maximum range for action features */
  std::vector<double> getMaximumActionRange( ) { return maxActionRange; }

  /** Get minimum range for action features */
  std::vector<double> getMinimumActionRange( ) { return minActionRange; }

  /** Get maximum range for state features */
  std::vector<double> getMaximumStateRange( ) { return maxStateRange; }

  /** Get maximum range for state features */
  std::vector<double> getMinimumStateRange( ) { return minStateRange; }

  /** Get number of state dimensions */
  int getStateDimension( ) { return stateDimension; }

  /** Get number of action dimensions */
  int getActionDimension( ) { return actionDimension; }

  /** Set domain parameters */ /* This is ugly? */
  void setParam(double d, int i) { noise = d; }

  /** Get maximum reward */
  double getRmax( ) { return rmax; }

  /** Get minimum reward */
  double getRmin( ) { return rmin; }

private:
  /** Store starting state */
  State initialState;

  /** Domain Parameters */
  std::vector<double> maxStateRange;
  std::vector<double> minStateRange;
  std::vector<double> maxActionRange;
  std::vector<double> minActionRange;
  static const int stateDimension = 2;
  static const int actionDimension = 1;
  static const double rmin = 0;
  static const double rmax = 1;

  /** Domain Properties */
  double gamma;

  /** Domain Specific */
  static const double g;
  static const double mp;
  static const double mc;
  static const double l;
  static const double dt;
  double noise;
  double alpha;

  double dynamics(State s, double a);
};

#endif // IP_HH
