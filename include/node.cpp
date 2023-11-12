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
  past_points.push_back(coord);
  //if the queue gets bigger than the predefined size pop the last element
  if(past_points.size()>past_points_size){
    past_points.pop_front();
  }
  //Update Density
  density = detSum/resolution;
  //TODO implement predictions for future points

  point = pt;
}

void Node::calcAvgSpeed(){
  //calculate avg speed on the x axis
  //calculate avg speed on the y axis
  //calculate avg speed on the z axis
  coord_ns::Coord prev_coord;
  for (auto it = past_points.cbegin(); it != past_points.cend(); ++it){
    if (prev_coord.x !=-1){
      //u = (x-xprev)/(t-tprev)
      avg_speed[0] += (it->x-prev_coord.x)/(it->t_stamp-prev_coord.t_stamp);
      avg_speed[1] += (it->y-prev_coord.x)/(it->t_stamp-prev_coord.t_stamp);
      avg_speed[2] += (it->y-prev_coord.x)/(it->t_stamp-prev_coord.t_stamp);
    }
    prev_coord = *it;
  }
  avg_speed[0] /= past_points_size;
  avg_speed[1] /= past_points_size;
  avg_speed[2] /= past_points_size;
}

void Node::calcAvgHeading(){
  //TODO: implement
}

Time Node::returnLastTime(){
  Time time;
  time.sec = past_points.back().t_stamp;
  return time;
} 


void Node::setCantor(point_ns::Point point){
  cantor_key= (((point.x + point.y + 1)*(point.x + point.y))/2) + point.y;
}

bool Node::coordExists(coord_ns::Coord coord, double accuracy){

}