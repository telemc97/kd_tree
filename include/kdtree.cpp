#include "kdtree.h"

using namespace kdtree_ns;

node_ns::Node* KdTree::insertRecursively(node_ns::Node* parent, point_ns::Point point, uint level, coord_ns::Coord coord, double conf){
  if (parent == NULL){
    parent = createNewNode(point); //only case that the parent in NULL is when we insert the first element aka root

  }
  //checks x coordinates
  if (level%2==0){
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


bool KdTree::insertPoint(point_ns::Point point, coord_ns::Coord coord, double conf){
  tree = insertRecursively(tree, point, 0, coord, conf);
  return true;
}


// Node* kdtree::insertNodeData(Node* node, Coord coord, double conf){
//   //Increment Detections Sum 
//   node->detSum++;
//   //Update Avg Confidence
//   if (node->detSum > 1){
//     node->avgConf = ((node->detSum-1)*(node->avgConf)+conf)/node->detSum;
//   }else{
//     node->avgConf = conf;
//   }
//   //Update Density
//   node->density = node->detSum/resolution;
  
//   node.

//   return node;
// }


// Takes the Coord and converts it to matrix index. It also updates the origin if the value is 
//negative or extends it if the value is greater than the matrix. The function returns a Point.
point_ns::Point KdTree::coordToPoint(coord_ns::Coord coord){
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


bool KdTree::isIn(point_ns::Point point){
  if (tree==NULL){
    return false;
  }
  return searchRecursively(tree, point, 0);
}


// Point* kdtree::getNearestNeighbors(uint number, uint radius){
  
// }