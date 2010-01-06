/*
 * Code by Chris Mansley
 */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "node.hh"

/*
 *
 */
Node::Node(HOO *h) : hoo(h), left(NULL), right(NULL), nsamples(0), sum(0), depth(0), Sflag(true) 
{ 
  Bval = std::numerical_limits<double>::infinity(); 
}

/*
 *
 */
Action Node::sampleAction()
{
  Action a;

  /* Grab sample from space */
  for(int i=0; i<hoo->numDim; i++) {
    a.push_back( gsl_ran_flat(hoo->rng, minRange[i], maxRange[i]) );
  }

  return a;
}

/*
 *
 */
void Node::split()
{
  /* Poor check (should throw error or something) */ 
  if(!isLeaf()) { 

    /* Generate children */
    left = new Node();
    right = new Node();
    
    /* Pick splitting dimension */
    splitDim = depth % hoo->numDim;
  
    /* Grab split point */
    splitValue = (maxRange[splitDim] - minRange[splitDim]) / 2;  

    /* Intialize nodes (expensive?) */
    left->depth = right->depth = depth + 1;
    left->maxRange = right->maxRange = maxRange;
    left->minRange = right->minRange = minRange;

    /* Split childrens ranges */
    left->maxRange[splitDim] = splitValue;
    right->minRange[splitDim] = splitValue;
  }
}

/*
 *
 */
double Node::rebuildSubTree()
{ 
  /* If in set S, return B-value */
  if(inS()) {
    return Bval;
  }

  /* Compute values */
  double mu = sum/nsamples;
  double U = mu + sqrt(2*log(hoo->totalSamples)/nsamples) + hoo->v1*pow(hoo->rho, depth); 

  /* Compute this node's B-value */
  double b1 = left->rebuildSubTree();
  double b2 = right->rebuildSubTree();
  Bval = min(U, max(b1, b2));

  return Bval;
}

/*
 *
 */
void Node::bestAction(Action &a)
{ 
  /* Terminate and sample from best node */
  if(inS()) {
    a = sampleAction();
  }

  /* Follow B-values down tree */
  if(node->left->Bval < node->right->Bval)
    right->bestAction(a);
  else 
    left->bestAction(a);
}


/*
 *
 */
void Node::insertValue(Action a, double q)
{
  /* Update the number of samples and sum of returns in this
     subtree */
  nsamples++;
  sum += q;

  /* If in the set S, recursion is done */
  if(inS()) {
    Sflag = false;
    split();
    return;
  }

  /* Move down tree */
  if(a[splitDim] < splitValue) {
    left->insertValue(a, q);
  } else {
    right->insertValue(a, q);
  }
}
