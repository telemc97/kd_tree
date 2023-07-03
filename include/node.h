#include <iostream>
#include <vector>
#include "point.h"
#include "coord.h"

namespace node_ns {

class Node {
  public:
  Node(): point(), detSum(0), points(), avgConf(0.0), density(0.0), left_child(NULL), right_child(NULL) {} 

  Node* insertNodeData(Node* node, coord_ns::Coord coord, double conf);

  Node* createNewNode(point_ns::Point point);

  double getAvgSlope();

  inline point_ns::Point getPoint();

  Node* left_child;
  Node* right_child;

  private:

  point_ns::Point point;

  int detSum;

  coord_ns::Coord points[18];
  int lastIdx = 0;
  bool looped = false;
  inline int getIdx();

  int resolution;

  double avgConf;
  double density;
};
}