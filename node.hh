/*
 * Code by Chris Mansley
 */

#ifndef NODE_HH
#define NODE_HH

#include <limits>

class Node
{
public:  
  /** Constructor */
  Node();

  /** Destructor */
  ~Node();

  /** Leaf status */
  bool inS() { return Sflag; }

private:
  /** Children */
  Node *left;
  Node *right;

  /** HOO Values */
  double sum;
  int nsamples;
  double Bval;

  int depth;

  bool Sflag;

  /** Split ranges */
  std::vector<double> minRange;
  std::vector<double> maxRange;

  /** Traverse tree */
  friend Action bestAction(Node *node);

  /** Rebuild tree */
  friend double rebuildTree(HOO *hoo, Node *node);
};


#endif // NODE_HH
