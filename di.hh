/*
 * Code by Chris Mansley
 */

#ifndef DI_HH
#define DI_HH

/* Definition dependencies */

#include "domain.hh"

/*!
 *
 */
class DI: public Domain
{
public:
  /** Constructor */
  DI(double gamma);

  /** Destructor */
  ~DI() { }

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
  static const double dt;
  static const double noise;
};

#endif // DI_HH
