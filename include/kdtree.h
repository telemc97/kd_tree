#ifndef _KDTREE_
#define _KDTREE_

#include <iostream>
#include <vector>
#include <unordered_map>
#include "point.h"
#include "coord.h"
#include "node.h"

namespace kdtree_ns {

class KdTree {
  // --------------------------------Public Members-----------------------------------------
  public:

  KdTree();

  bool insertPoint(coord_ns::Coord coord, double conf, int id, std::string cls);

  point_ns::Point coordToIndex(coord_ns::Coord coord);

  bool isIn(point_ns::Point point);

  // --------------------------------Private Members----------------------------------------
  private:

  bool newPoint(point_ns::Point point);

  inline int getCantor(point_ns::Point point);

  node_ns::Node* insertNodeData(node_ns::Node* node, coord_ns::Coord coord, double conf);

  node_ns::Node* createNewNode(point_ns::Point point);

  node_ns::Node* insertRecursively(node_ns::Node* parent, point_ns::Point point, uint level, coord_ns::Coord coord, double conf);

  bool searchRecursively(node_ns::Node* parent, point_ns::Point point, uint level);

  point_ns::Point* getNearestNeighbors(uint number, uint radius);

  node_ns::Node* tree = NULL;
  float resolution;
  point_ns::Point origin;
  point_ns::Point maxPoint;

  std::unordered_map<int, node_ns::Node*> tree_map;
};
}

#endif