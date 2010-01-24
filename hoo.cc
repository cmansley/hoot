/*
 * Code by Chris Mansley
 */
#include <iostream>
#include <cmath>
#include <limits>

#include "hoo.hh"
#include "node.hh"

/*
 *
 */
HOO::HOO(Domain *d, Chopper *c) : domain(d), chopper(c), totalSamples(0)
{
  /* Initialize random elements */
  rng = gsl_rng_alloc(gsl_rng_taus);
  gsl_rng_set(rng, rand());

  /* Number of action dimensions */
  numDim = domain->getActionDimension();

  /* Initialize root of tree */
  tree = new Node(this);
  tree->rangeInit(chopper->minActionZero(), chopper->maxActionOne());

  /* Initialize parameters using advice from paper */
  v1 = sqrt(numDim)/2;
  rho = 0.5;
}

HOO::~HOO()
{
  /* Delete all memory recursivly? */
  tree->clear();

  /* Delete root of tree */
  delete tree;

  /* Remove random number generator */
  gsl_rng_free(rng);
}

/*
 *
 */
void HOO::insertAction(Action a, double q)
{
  
  /* Insert the action/value in tree*/
  tree->insertValue(a, q);
  totalSamples++;

  /* Rebuild the B-values in the subtree */
  tree->rebuildSubTree();
}

/*
 *
 */
Action HOO::queryAction(bool greedy)
{
  Action a;

  tree->bestAction(a, greedy);

  return a;
}

/*
 *
 */
void HOO::clear() 
{
  tree->clear();
  totalSamples = 0;
  
  delete tree;

  /* Initialize root of tree */
  tree = new Node(this);
  tree->rangeInit(chopper->minActionZero(), chopper->maxActionOne());
}

void HOO::print()
{
  tree->print();
}
