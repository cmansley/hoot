#include <iostream>
#include <vector>

using namespace std;

class Shape
{
public:
  Shape() {}
  ~Shape() {}

  void print() { one.x = 2; std::cout << one.y << one.x << std::endl; }

private:

  class Point
  {
  public:
    Point() : x(1), y(1) {}
    //  private:
    int x;
    int y;
  };

  Point one;
};

int main()
{

  Shape s;
  
  s.print();

  Shape::Point x;
  
  return 0;
}
