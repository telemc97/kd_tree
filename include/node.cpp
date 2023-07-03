#include "node.h"
#include <math.h>

using namespace node_ns;

point_ns::Point Node::getPoint(){
  return point;
}

int Node::getIdx(){
  int idx;
  if (lastIdx<17){
    idx = ++lastIdx;
  }else if(lastIdx==17){
    idx = 0;
    looped = true;
  }
  return idx;
}

Node* Node::createNewNode(point_ns::Point point){
  Node* newNode = new Node;

  newNode->point = point;
  newNode->left_child = NULL;
  newNode->right_child = NULL;
  
  return newNode;
}

Node* Node::insertNodeData(Node* node, coord_ns::Coord coord, double conf){
  //Update Avg Confidence
  node->avgConf = (node->detSum*(node->avgConf)+conf)/node->detSum+1;
  //Increment Detections Sum 
  node->detSum++;
  //Add coords to the points[20] array in a "circular buffer manner"
  node->points[getIdx()] = coord;
  //Update Density
  node->density = node->detSum/resolution;
}

double Node::getAvgSlope(){
  double avg_angle = 0.0;
  if (lastIdx>3 || !looped){
    int sum_set;
    if (!looped){
      sum_set = lastIdx/3;
    }else{
      sum_set = 6;
    }
    double det_sum =0;
    //reference ground plane vector
    double r[3] = {0, 1, 0};
    for (int i=0;i<det_sum;i++){
      double pq[3] = {points[i*3+0].x-points[i*3+1].x, points[i*3+0].y-points[i*3+1].y, points[i*3+0].z-points[i*3+1].z};
      double pr[3] = {points[i*3+0].x-points[i*3+2].x, points[i*3+0].y-points[i*3+2].y, points[i*3+0].z-points[i*3+2].z};
      //cross product
      double n[3] = {pq[1]*pr[2] - pq[2]*pr[1], pq[2]*pr[0] - pq[0]*pr[2], pq[0]*pr[1] - pq[1]*pr[0]};
      //magnitude
      double magnitude = sqrt(pow(n[0],2) + pow(n[1],2) + pow(n[2],2));
      n[0] = n[0]/magnitude; 
      n[1] = n[1]/magnitude; 
      n[2] = n[2]/magnitude;
      double dot_product = n[0]*r[0] + n[1]*r[1] + n[2]*r[2];
      double angle = acos(dot_product);
      avg_angle = (i*avg_angle + angle)/(i+1);
    }
  }
  return avg_angle;
}