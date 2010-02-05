/*
 * Code by Chris Mansley
 */

#ifndef GAUSSIAN_HH
#define GAUSSIAN_HH

/* Definition dependencies */


#include "domain.hh"

/*!
 *
 */
class Gaussian: public Domain
{
public:
  /** Constructor */
  Gaussian();

  /** Destructor */
  ~Gaussian() { }

  /** Perform an interaction with the environment */
  SARS *step(State s, Action a);

  /** Get starting state from domain */
  State getInitialState( ) { return initialState; }

  /** Get number of discrete actions for domain */
  int getNumActions( ) { return numActions; }

  /** Get discount factor for domain */
  double getDiscountFactor( ) { return 0.0; }

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

  void setParam(double d, int i) {}

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
  static const int stateDimension = 0;
  static const int actionDimension = 1;
  static const double rmin = 0;
  static const double rmax = 1;

  // only if discrete actions
  static const int numActions = 20;

  /** Domain Specific */
  std::vector<double> mu;
  std::vector<double> diag;
};

#endif // DOMAIN_HH
