#include "node.h"
#include <math.h>

using namespace node_ns;

static double roundDecimal(double num, double accuracy){
  double  intpart;
  double fractpart = modf (num, &intpart);
  fractpart  = roundf(fractpart * accuracy)/accuracy; // Round to 5 decimal places
  double rounded = intpart + fractpart;
  return rounded;
}

point_ns::Point Node::getPoint(){
  return point;
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

void Node::insertNodeData(point_ns::Point pt, coord_ns::Coord coord, float conf, int id, std::string cls ){

  //Update Avg Confidence
  confidence = (detSum*(confidence)+conf)/detSum+1;
  //Increment Detections Sum 
  detSum++;
  //Add coords to the points[20] array in a "circular buffer manner"
  past_points.push(coord);
  //if the queue gets bigger than the predefined size pop the last element
  if(past_points.size()>past_points_size){
    past_points.pop();
  }
  //Update Density
  density = detSum/resolution;
  //TODO implement predictions for future points

  point = pt;
}

Time Node::returnLastTime(){
  Time time;
  time.sec = past_points.back().sec;
  time.nsec = past_points.back().nsec;
  return time;
} 


void Node::setCantor(point_ns::Point point){
  cantor_key= (((point.x + point.y + 1)*(point.x + point.y))/2) + point.y;
}

bool Node::coordExists(coord_ns::Coord coord, double accuracy){

}