class HOO
{
  HOO();

  ~HOO();

  Action query();

private:

  class Node {
  public:
    Node *left;
    Node *right;

    double Bval;
    double sum;
    int numSamples;

    std::vector<double> minRange;
    std::vector<double> maxRange;
  };

  Node *tree;

};


left = new Node()
right = new Node()

spliter = depth % numDim

mid = (maxRange[splitter] - minRange[splitter]) / 2;

left.maxRange = right.maxRange = maxRange;
left.minRange = right.minRange = minRange;

left.maxRange[splitter] = mid;
right.minRange[splitter] = mid;
