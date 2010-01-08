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
HOO::HOO(Domain *d) : domain(d), totalSamples(0)
{
  /* Initialize random elements */
  rng = gsl_rng_alloc(gsl_rng_taus);

  /* Number of action dimensions */
  numDim = domain->getActionDimension();

  /* Initialize root of tree */
  tree = new Node(this);
  tree->rangeInit(domain->getMinimumActionRange(), domain->getMaximumActionRange());

  /* Initialize parameters using advice from paper */
  v1 = sqrt(numDim)/2;
  rho = 0.5;
}

HOO::~HOO()
{
  /* Delete all memory recursivly? */

  /* Delete root of tree */
  delete tree;
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
Action HOO::queryAction()
{
  Action a;

  tree->bestAction(a);

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
  tree->rangeInit(domain->getMinimumActionRange(), domain->getMaximumActionRange());

}



