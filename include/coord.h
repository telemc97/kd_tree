#ifndef _COORD_
#define _COORD_

namespace coord_ns{

struct Coord {
  double x,y,z;
  int sec, nsec;
  Coord(): x(0.0), y(0.0), z(0.0), sec(0), nsec(0) {}
};
}

#endif