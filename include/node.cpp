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

Node::Node(point_ns::Point pt, coord_ns::Coord coord){
  this->point = pt;
  this->left_child = NULL;
  this->right_child = NULL;
  this->setCantor(pt);
  this->updateNodeData(coord);
}

point_ns::Point Node::getPoint(){
  return point;
}

int Node::getCantor(){
  return cantor_key;
}

void Node::updateNodeData(coord_ns::Coord coord){

  //Update Avg Confidence
  average_confidence = (detections_sum*(average_confidence)+coord.conf)/detections_sum+1;
  //Increment Detections Sum 
  detections_sum++;
  //Add coords to the points[20] array in a "circular buffer manner"
  past_points[coord.id].push_back(coord);
  //if the queue gets bigger than the predefined size pop the last element
  if(past_points.size()>past_points_size){
    past_points[coord.id].pop_front();
  }
  //Update Density
  detections_density = detections_sum/resolution;
  //TODO implement predictions for future points
}

void Node::calcAvgSpeed(int id){
  //calculate avg speed on the x axis
  //calculate avg speed on the y axis
  //calculate avg speed on the z axis
  coord_ns::Coord prev_coord;
  for (auto it = past_points[id].cbegin(); it != past_points[id].cend(); ++it){
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

void Node::calcAvgHeading(int id){
  //TODO: implement
  coord_ns::Coord prev_coord;
  for (auto it = past_points[id].cbegin(); it != past_points[id].cend(); ++it){
    if (prev_coord.x != -1){
      avg_heading[0] += it->x - prev_coord.x;
      avg_heading[1] += it->y - prev_coord.y;
      avg_heading[2] += it->z - prev_coord.z;
    }
    prev_coord = *it;
  }
  avg_heading[0] /= past_points_size;
  avg_heading[1] /= past_points_size;
  avg_heading[2] /= past_points_size;
}

Time Node::returnLastTime(int id){
  Time time;
  time.sec = past_points[id].back().t_stamp;
  return time;
} 


void Node::setCantor(point_ns::Point point){
  cantor_key= (((point.x + point.y + 1)*(point.x + point.y))/2) + point.y;
}

bool Node::coordExists(coord_ns::Coord coord, double accuracy){

}