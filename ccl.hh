/*
 * Code by Chris Mansley
 */

#ifndef CCL_HH
#define CCL_HH

/* Definition dependencies */

#include "domain.hh"

/*!
 * 
 */
class CCL : public Domain
{
public:
  /** Constructor */
  CCL(double gamma);
  
  /** Destructor */
  ~CCL() { }

  /** Simulate an interaction with the environment */
  SARS *simulate(State s, Action a);

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

private:
  /** Store starting state */
  State initialState;

  /** Domain Parameters */
  std::vector<double> maxRange;
  std::vector<double> minRange;
  static const int stateDimension = 1;
  static const int actionDimension = 1;

  // only if discrete actions
  static const int numActions = 2;

  /** Domain Properties */
  double gamma;
};

#endif // CCL_HH
