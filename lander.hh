/*
 * Code by Chris Mansley
 */

#ifndef LANDER_HH
#define LANDER_HH

/* Definition dependencies */


#include "domain.hh"

/*!
 *
 */
class Lander: public Domain
{
public:
  /** Constructor */
  Lander(double gamma);

  /** Destructor */
  ~Lander() { }

  /** Perform an interaction with the environment */
  SARS *step(State s, Action a);

  /** Get starting state from domain */
  State getInitialState( );

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
  static const int stateDimension = 3;
  static const int actionDimension = 1;
  static const double rmin = -300;
  static const double rmax = 0;

  // only if discrete actions
  static const int numActions = 10;

  /** Domain Properties */
  double gamma;

  /** Domain Specific */
  static const double kg;
  static const double kf;
  static const double c;
  static const double dt;

  double rC(double action);
};

#endif // DOMAIN_HH
