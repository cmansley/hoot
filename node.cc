#include "node.hh"

Node::Node() : left(NULL), right(NULL), nsamples(0), Sflag(true) 
{ 
  Bval = std::numerical_limits<double>::infinity(); 
}
