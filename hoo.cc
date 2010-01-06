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
  tree = new Node();
}

HOO::~HOO()
{
  // better clean up?

  delete tree;
}

/*
 *
 */
void HOO::insertAction(Action a, double q)
{

  rebuildTree(this, node);
}

/*
 *
 */
Action HOO::bestAction()
{
  Action a = bestAction(tree);

  return a;
}


/*
 * Helper Functions
 */

/*
 *
 */
Action bestAction(Node *node)
{ 
  /* Terminate and sample from best node */
  if(node->inS()) {
    return node->sampleAction();
  }

  /* Follow B-values down tree */
  Action a;
  if(node->left->Bval < node->right->Bval)
    a = bestAction(node->right);
  else 
    a = bestAction(node->left);

  return a;
}

/*
 *
 */
double rebuildTree(HOO *hoo, Node *node)
{
  /* If in node, increment nsamples and add value, 
   * if in node and inS, change flag, increment nsamples, add value, add children    
   */
  
  /* If in set S, return B-value */
  if(node->inS()) {
    return node->Bval;
  }

  /* Compute values */
  double mu = node->sum/node->nsamples;
  double U = mu + sqrt(2*log(hoo->N)/node->nsamples) + hoo->v1*pow(hoo->rho, node->depth); 

  /* Compute this node's B-value */
  double b1 = rebuildTree(hoo, node->left);
  double b2 = rebuildTree(hoo, node->right);
  node->Bval = min(U, max(b1, b2));

  return node->Bval;
}
