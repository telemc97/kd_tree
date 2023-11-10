/* TODO : replace unordered_map with a big array*/

#include "kdtree.h"

using namespace kdtree_ns;

node_ns::Node* KdTree::insertRecursively(node_ns::Node* parent, point_ns::Point point, uint level, coord_ns::Coord coord, double conf){
  if (parent == NULL){
    parent = createNewNode(point); //only case that the parent in NULL is when we insert the first element aka root
    tree_map[parent->getCantor()] = parent;
  }
  if (level%2==0){ //checks x coordinates
    if (point.x < parent->getPoint().x){
      parent->left_child  = insertRecursively(parent->left_child, point, level+1, coord, conf);
    }else{
      parent->right_child = insertRecursively(parent->right_child, point, level +1, coord, conf);
    }
  }else if (level%2==1){ //checks y coordinates
    if (point.y < parent->getPoint().y){
      parent->left_child = insertRecursively(parent->left_child, point, level+1, coord, conf);
    }else{
      parent->right_child = insertRecursively(parent->right_child, point, level+1, coord, conf);
    }
  }
  return parent;
}


bool KdTree::insertPoint(coord_ns::Coord coord, double conf, int id, std::string cls){
  point_ns::Point point = coordToIndex(coord);
  if (tree_map[getCantor(point)]==NULL){
    tree = insertRecursively(tree, point, 0, coord, conf);
  }else{
    tree_map[getCantor(coordToIndex(coord))]->insertNodeData(point, coord, conf, id, cls);
  }
  return true;
}

//Recieves the Coord and converts it to matrix index. It also updates the origin if the value is 
//negative or extends it if the value is greater than the matrix. The function returns a Point.
point_ns::Point KdTree::coordToIndex(coord_ns::Coord coord){
  point_ns::Point point;
  if (coord.x/resolution<0){
    point.x = 0;
    origin.x = -(coord.x/resolution);
  }else{
    point.x = coord.x/resolution;
  }
  if (coord.y/resolution<0){
    point.y = 0;
    origin.y = -(coord.y/resolution);
  }else{
    point.y = coord.y/resolution;
  }
  if (point.x>maxPoint.x){
    maxPoint.x = point.x;
  }
  if (point.y>maxPoint.y){
    maxPoint.y = point.y;
  }
  return point;
}

bool KdTree::searchRecursively(node_ns::Node* parent, point_ns::Point point, uint level){
  if (parent->getPoint().x==point.x && parent->getPoint().y==point.y){
    return true;
  }
  if (level%2==0){
    if(parent->getPoint().x > point.x){
      return searchRecursively(parent->left_child, point, level+1);
    }else if(level%2==1){
      return searchRecursively(parent->right_child, point, level+1);
    }
  }
}

int KdTree::getCantor(point_ns::Point point){
  return (((point.x + point.y + 1)*(point.x + point.y))/2) + point.y;
}

bool KdTree::isIn(point_ns::Point point){
  if (tree==NULL){
    return false;
  }
  return searchRecursively(tree, point, 0);
}