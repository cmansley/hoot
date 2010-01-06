/*
 * Code by Chris Mansley
 */

#ifndef NODE_HH
#define NODE_HH

#include <limits>

#include "action.hh"

class Node
{
public:  
  /** Constructor */
  Node(HOO *h);

  /** Destructor */
  ~Node();

  /** Leaf status */
  bool inS() { return Sflag; }

  /** Leaf status */
  bool isLeaf() { return ((left==NULL) && (right==NULL)); }

  /** Split this leaf */
  void split();

  /** Rebuild the B-values of this node's subtree */
  double rebuildSubTree();

  /** Return the currently best action */
  void bestAction(Action &a);

private:
  /** Parent stucture */
  HOO *hoo;

  /** Children */
  Node *left;
  Node *right;

  /** HOO Values */
  double sum;
  int nsamples;
  double Bval;
  int depth;

  /** Tree data */
  int splitDim;
  double splitValue;

  bool Sflag; // Do I need this

  /** Split ranges */
  std::vector<double> minRange;
  std::vector<double> maxRange;

  /** Sample an action from the node */
  Action sampleAction();
};


#endif // NODE_HH
