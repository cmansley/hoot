/*
 * Code by Chris Mansley
 */

#ifndef NODE_HH
#define NODE_HH

#include "action.hh"

class HOO;

class Node
{
public:  
  /** Constructor */
  Node(HOO *h);

  /** Destructor */
  ~Node() {}

  /** Leaf status */
  bool inS() { return Sflag; }

  /** Leaf status */
  bool isLeaf() { return ((left==NULL) && (right==NULL)); }

  /** Initialize node range value */
  void rangeInit(std::vector<double> min, std::vector<double> max) { minRange = min; maxRange = max; }

  /** Split this leaf */
  void split();

  /** Rebuild the B-values of this node's subtree */
  double rebuildSubTree();

  /** Return the currently best action */
  void bestAction(Action &a, bool greedy);

  /** Recursively insert a value at action a */
  void insertValue(Action a, double q);

  /** Recursively delete subtrees */
  void clear();

  void print();

private:
  /** Parent stucture */
  HOO *hoo;

  /** Children */
  Node *left;
  Node *right;

  /** HOO Values */
  double mu;
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
