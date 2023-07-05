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

int Node::getCantor(){
  return cantor_key;
}

Node* Node::createNewNode(point_ns::Point point){
  Node* newNode = new Node;

  newNode->point = point;
  newNode->left_child = NULL;
  newNode->right_child = NULL;
  newNode->setCantor(point);
  
  return newNode;
}

void Node::insertNodeData(coord_ns::Coord coord, double conf){
  //Update Avg Confidence
  avgConf = (detSum*(avgConf)+conf)/detSum+1;
  //Increment Detections Sum 
  detSum++;
  //Add coords to the points[20] array in a "circular buffer manner"
  points[getIdx()] = coord;
  //Update Density
  density = detSum/resolution;
}

//Calculates the average angle between the normal vectors of planes defined by 3 points
//and the origin vector (as reference).
double Node::getAvgSlope(){
  double avg_angle = 0.0;
  if (lastIdx>3 || !looped){
    int sum_set;
    if (!looped){
      sum_set = lastIdx/3;
    }else{
      sum_set = 6;
    }
    //reference ground plane vector
    double r[3] = {0, 1, 0};
    for (int i=0;i<sum_set;i++){
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


void Node::setCantor(point_ns::Point point){
  cantor_key= (((point.x + point.y + 1)*(point.x + point.y))/2) + point.y;
}

bool Node::coordExists(coord_ns::Coord coord, double accuracy){
  int it;
  if(!looped){
    it = 18;
  }else{
    it = lastIdx;
  }
  double x_coord = roundDecimal(coord.x, accuracy);
  double y_coord = roundDecimal(coord.y, accuracy);
  double z_coord = roundDecimal(coord.z, accuracy);
  for (int i=0;i<it;i++){
    if (roundDecimal(points[i].x,accuracy)==x_coord &&
        roundDecimal(points[i].y,accuracy)==y_coord &&
        roundDecimal(points[i].z,accuracy)==z_coord){
      return true;
    }
  }
  return false;
}

double roundDecimal(double num, double accuracy){
  double  intpart;
  double fractpart = modf (num, &intpart);
  fractpart  = roundf(fractpart * accuracy)/accuracy; // Round to 5 decimal places
  double rounded = intpart + fractpart;
  return rounded;
}