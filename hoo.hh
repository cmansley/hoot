/*
 * Code by Chris Mansley
 */

#ifndef HOO_HH
#define HOO_HH

#include "action.hh"

class HOO
{
public:
  /** Constructor */
  HOO();

  /** Destructor */
  ~HOO();

  /** Insert a selected action and value */
  Action insertAction(Action a, double q);

  /** Return current best action */
  Action bestAction();

private:
  /** HOO Tree */
  Node *tree;
  
  /** Total number of samples to date */
  int N;

  /** Traverse tree */
  friend Action bestAction(Node *node);
  
  /** Rebuild tree */
  friend double rebuildTree(HOO *hoo, Node *node);
};

#endif // HOO_HH
