#ifndef _POINT_
#define _POINT_

namespace point_ns{

struct Point {
  int x,y;
  int sec,nsec;
  Point(): x(-1), y(-1), sec(-1), nsec(-1) {}
};
}

#endif