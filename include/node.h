//Each node contains the past detections of a single object (same ID).

#ifndef _NODE_
#define _NODE_

#include <iostream>
#include <vector>
#include <deque>
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
  Node(): point(), left_child(NULL), right_child(NULL) {} 

  void insertNodeData(point_ns::Point pt, coord_ns::Coord coord, float conf, int id, std::string cls );

  Node* createNewNode(point_ns::Point point);
  
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

  void calcAvgSpeed();
  std::vector<double> avg_speed;

  void calcAvgHeading();
  std::vector<double> avg_heading;

  std::deque<coord_ns::Coord> past_points;
  int past_points_size;

  std::deque<coord_ns::Coord> future_points;
  int future_points_size;

  Time returnLastTime();

  int resolution;

  //Confidence of the node is calculated as the average confidence of its detections.
  float confidence;
  int detSum;
  int density;
  int id;
  
  std::string class_name;

};

}

#endif