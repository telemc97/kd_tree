#include <iostream>
#include <vector>

namespace kdtree_ns {

struct Point {
  int x,y;
};

struct Node {
  Point point;
  Node* left_child;
  Node* right_child;
};

class kdtree {

  public:

  kdtree();

  bool insertPoint(Point point);

  bool isIn(Point point);

  private:

  Node* createNewNode (Point point);

  Node* insertRecursively(Node* parent, Point point, uint level);

  bool searchRecursively(Node* parent, Point point, uint level);

  Point* getNearestNeighbors(uint number, uint radius);

  Node* tree = NULL;
  float resolution;
  Point origin;

};

}