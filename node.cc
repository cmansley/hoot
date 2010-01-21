/*
 * Code by Chris Mansley
 */
#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "node.hh"
#include "hoo.hh"

/*
 *
 */
Node::Node(HOO *h) : hoo(h), left(NULL), right(NULL), mu(0), nsamples(0), depth(0), Sflag(true) 
{ 
  Bval = std::numeric_limits<double>::infinity(); 
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
  if(isLeaf()) { 

    /* Generate children */
    left = new Node(hoo);
    right = new Node(hoo);
    
    /* Pick splitting dimension */
    splitDim = depth % hoo->numDim;
  
    /* Grab split point */
    splitValue = (maxRange[splitDim] - minRange[splitDim]) / 2.0 + minRange[splitDim];  

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
  double U = mu + sqrt(2.0*log(hoo->totalSamples)/nsamples) + hoo->v1*pow(hoo->rho, depth); 

  /* Compute this node's B-value */
  double b1 = left->rebuildSubTree();
  double b2 = right->rebuildSubTree();
  Bval = std::min(U, std::max(b1, b2));  

  return Bval;
}

/*
 *
 */
void Node::bestAction(Action &a, bool greedy)
{ 
  /* Terminate and sample from best node */
  if(inS()) {
    a = sampleAction();
    return;
  }

  if(!greedy) {
    /* Follow B-values down tree */
    if(left->Bval < right->Bval)
      right->bestAction(a, greedy);
    else 
      left->bestAction(a, greedy);
  } else {
    /* Follow mu down tree */
    if(left->mu < right->mu)
      right->bestAction(a, greedy);
    else 
      left->bestAction(a, greedy);
  }
}


/*
 *
 */
void Node::insertValue(Action a, double q)
{
  /* Update the number of samples and mean of returns in this
     subtree */
  nsamples++;
  mu = mu + (q-mu)/nsamples;

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

/*
 *
 */
void Node::clear()
{
  if(isLeaf()) {
    return;
  }

  left->clear();
  right->clear();
  
  delete left;
  delete right;
}

/*
 *
 */
void Node::print()
{
  if(inS()) {
    return;
  }
  
  std::cout << depth << " " <<  splitValue << std::endl;
  
  left->print();
  right->print();
}
