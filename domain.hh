/*
 * Code by Chris Mansley
 */

#ifndef DOMAIN_HH
#define DOMAIN_HH

/* Definition dependencies */
#include <vector>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "sars.hh"
#include "state.hh"
#include "action.hh"


class Domain
{
public:
  /** Constructor */
  Domain() 
  {   
    /* Initialize random elements */
    rng = gsl_rng_alloc(gsl_rng_taus);
    gsl_rng_set(rng, rand());

    /* Initialize number of samples */
    numSamples = 0;
  }

  /** Destructor */
  virtual ~Domain() { }

  /** Simulate an interaction with the environment */
  SARS *simulate(State s, Action a) { numSamples++; return step(s,a); }

  /** Perform an interaction with the environment */
  virtual SARS *step(State s, Action a) = 0;

  /** Get starting state from domain */
  virtual State getInitialState( ) = 0;

  /** Get discount factor for domain */
  virtual double getDiscountFactor( ) = 0;

  /** Get maximum range for action features */
  virtual std::vector<double> getMaximumActionRange( ) = 0;

  /** Get minimum range for action features */
  virtual std::vector<double> getMinimumActionRange( ) = 0;

  /** Get maximum range for state features */
  virtual std::vector<double> getMaximumStateRange( ) = 0;

  /** Get maximum range for state features */
  virtual std::vector<double> getMinimumStateRange( ) = 0;

  /** Get number of state dimensions */
  virtual int getStateDimension( ) = 0;

  /** Get number of action dimensions */
  virtual int getActionDimension( ) = 0;

  /** Get maximum reward */
  virtual double getRmax( ) = 0;

  /** Get minimum reward */
  virtual double getRmin( ) = 0;

  /** Set domain parameters */ /* This is ugly? */
  virtual void setParam(double d, int i) = 0;

  /** Return number of samples */
  int getNumSamples() { return numSamples; }

  /** Reset number of samples */
  void resetSamples() { numSamples = 0; }

protected:
  /** For randomness */
  gsl_rng *rng;

  /** Book-keeping */
  int numSamples;

  /*
   * Note: I have made the conscious decision here to allow the
   * compiler to do its thing. This also goes for passing by value,
   * which could be force-optimized as follows
   *
   * State function(const State &s)
   * 
   * instead of 
   *
   * State function(State s)
   */
};

#endif // DOMAIN_HH
