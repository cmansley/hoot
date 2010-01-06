/*
 * Code by Chris Mansley
 */

#ifndef HOO_HH
#define HOO_HH

/* Definition dependencies */
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "action.hh"
#include "node.hh"

class HOO
{
public:
  /** Constructor */
  HOO();

  /** Destructor */
  ~HOO();

  /** Insert a selected action and value */
  void insertAction(Action a, double q);

  /** Return current best action */
  Action queryAction();

private:
  /** For randomness */
  gsl_rng *rng;

  /** HOO Tree */
  Node *tree;
  
  /** Total number of samples to date */
  int totalSamples;

  /** Number of action dimensions */
  int numDim;

  /** Allow Node to access HOO */
  friend class Node;
};

#endif // HOO_HH
