/*
 * Code by Chris Mansley
 */

#ifndef HOO_HH
#define HOO_HH

/* Definition dependencies */
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "domain.hh"
#include "chopper.hh"
#include "action.hh"

class Node;

class HOO
{
public:
  /** Constructor */
  HOO(Domain *d, Chopper *c);

  /** Destructor */
  ~HOO();

  /** Insert a selected action and value */
  void insertAction(Action a, double q);

  /** Return current best action */
  Action queryAction(bool greedy);

  /** Destroy structure */
  void clear();

  void print();

private:
  /** Current HOO domain */
  Domain *domain;

  /** Current chopper */
  Chopper *chopper;

  /** For randomness */
  gsl_rng *rng;

  /** HOO Tree */
  Node *tree;
  
  /** Total number of samples to date */
  int totalSamples;

  /** Number of action dimensions */
  int numDim;

  /** HOO parameters */
  double v1;
  double rho;
  
  /** Allow Node to access HOO */
  friend class Node;
};

#endif // HOO_HH
