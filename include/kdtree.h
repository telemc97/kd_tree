#include <iostream>
#include <vector>
#include "point.h"
#include "coord.h"
#include "node.h"

namespace kdtree_ns {

class KdTree {

  public:

  KdTree();

  bool insertPoint(point_ns::Point point, coord_ns::Coord coord, double conf);

  point_ns::Point coordToPoint(coord_ns::Coord coord);

  bool isIn(point_ns::Point point);

  private:

  node_ns::Node* insertNodeData(node_ns::Node* node, coord_ns::Coord coord, double conf);

  node_ns::Node* createNewNode(point_ns::Point point);

  node_ns::Node* insertRecursively(node_ns::Node* parent, point_ns::Point point, uint level, coord_ns::Coord coord, double conf);

  bool searchRecursively(node_ns::Node* parent, point_ns::Point point, uint level);

  point_ns::Point* getNearestNeighbors(uint number, uint radius);

  node_ns::Node* tree = NULL;
  float resolution;
  point_ns::Point origin;
  point_ns::Point maxPoint;
};

}