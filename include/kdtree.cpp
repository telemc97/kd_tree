#include <kdtree.h>

using namespace kdtree_ns;

Node* kdtree::createNewNode(Point point){

  Node* newNode = new Node;

  newNode->point = point;
  newNode->left_child = NULL;
  newNode->right_child = NULL;
  
  return newNode;
}

Node* kdtree::insertRecursively(Node* parent, Point point, uint level){
  if (parent == NULL){
    parent = createNewNode(point); //only case that the parent in NULL is when we insert the first element aka root
  }
  //checks x coordinates
  if (level%2==0){
    if (point.x < parent->point.x){
      parent->left_child  = insertRecursively(parent->left_child, point, level+1);
    }else{
      parent->right_child = insertRecursively(parent->right_child, point, level +1);
    }
  }else if (level%2==1){ //checks y coordinates
    if (point.y < parent->point.y){
      parent->left_child = insertRecursively(parent->left_child, point, level+1);
    }else{
      parent->right_child = insertRecursively(parent->right_child, point, level+1);
    }
  }
  return parent;
}

bool kdtree::insertPoint(Point point){
  tree = insertRecursively(tree, point, 0);
  return true;
}

bool kdtree::searchRecursively(Node* parent, Point point, uint level){
  if (parent->point.x==point.x && parent->point.y==point.y){
    return true;
  }
  if (level%2==0){
    if(parent->point.x > point.x){
      return searchRecursively(parent->left_child, point, level+1);
    }else if(level%2==1){
      return searchRecursively(parent->right_child, point, level+1);
    }
  }
}

bool kdtree::isIn(Point point){
  if (tree==NULL){
    return false;
  }
  return searchRecursively(tree, point, 0);
}

Point* kdtree::getNearestNeighbors(uint number, uint radius){
  
}