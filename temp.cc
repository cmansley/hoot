#include <iostream>
#include <vector>

using namespace std;

class Shape
{
public:
  Shape() : x(1), y(1) { one = new Point(this); }
  ~Shape() {}

  void print() { one->print(); }

private:
  int x;
  int y;


private:

  class Point
  {
  public:
    Point(Shape *sh) : s(sh)  {}
    void print() { std::cout << s->x << s->y << std::endl; }
  private:
    Shape *s;
  };

  Point *one;
};

int main()
{

  Shape s;

  s.print();

  return 0;
}
