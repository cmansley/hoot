/*
 * Code by Chris Mansley
 */
#include <iostream>
#include <cmath>
#include <limits>

#include "hoo.hh"


/*
 *
 */
HOO::HOO()
{
  /* Initialize random elements */
  rng = gsl_rng_alloc(gsl_rng_taus);

  /* Initialize root of tree */
  tree = new Node();
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



