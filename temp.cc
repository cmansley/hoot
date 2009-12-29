#include <iostream>
#include <vector>

using namespace std;

class Shape
{
public:
  Shape(int in) { i = in; cout << "Shape Constructor" << endl; }
  ~Shape() { cout << "Shape Destructor" << endl; }
  virtual std::vector<int> print(int i) = 0;
  int i;
};

class Circle : public Shape 
{
public:
  Circle() : Shape(1) { cout << "Circle Constructor" << endl; }
  ~Circle() { cout << "Circle Destructor" << endl; }
  std::vector<int> print(int i) { std::vector<int> v; v.push_back(i); return v; }
};

int main()
{
  Circle c;
  std::vector<int> a;

  a.push_back(3);
  a.push_back(2);

  a.back() = 0;

  cout << a.back() << endl;

  //a = c.print(1);

  //cout << "Main " << a[0] << " " << a.size() <<endl;
  
  return 0;
}
