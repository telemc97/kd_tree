#ifndef _COORD_
#define _COORD_

namespace coord_ns{

struct Coord {
  double x,y,z;
  double t_stamp;
  Coord(): x(-1), y(-1), z(-1), t_stamp(-1) {};
};
}

#endif