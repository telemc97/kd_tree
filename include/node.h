//Each node contains the past detections of a single object (same ID).

#ifndef _NODE_
#define _NODE_

#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include "point.h"
#include "coord.h"

namespace node_ns {

struct Time{
  int sec, nsec;
  Time(): sec(-1), nsec(-1) {}; 
};

class Node {
  // --------------------------------Public Members-----------------------------------------
  public:
  Node(point_ns::Point pt, coord_ns::Coord coord): point(), left_child(NULL), right_child(NULL) {} 

  void updateNodeData(coord_ns::Coord coord);

  Node* createNewNode(point_ns::Point pt, coord_ns::Coord coord);
  
  inline int getCantor();

  bool coordExists(coord_ns::Coord coord, double accuracy);

  inline point_ns::Point getPoint();

  Node* left_child;
  Node* right_child;

  // --------------------------------Private Members----------------------------------------
  private:
  int cantor_key;

  point_ns::Point point;

  inline void setCantor(point_ns::Point point);

  void calcAvgSpeed(int id);
  std::vector<double> avg_speed;

  void calcAvgHeading(int id);
  std::vector<double> avg_heading;

  std::unordered_map<int, std::deque<coord_ns::Coord>> past_points;
  int past_points_size;

  std::unordered_map<int, std::deque<coord_ns::Coord>> future_points;
  int future_points_size;

  Time returnLastTime(int id);

  int resolution;

  //Confidence of the node is calculated as the average confidence of its detections.
  float average_confidence;
  int detections_sum;
  int detections_density;
  
  std::string class_name;

};

}

#endif