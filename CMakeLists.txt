cmake_minimum_required(VERSION 3.0.2)
project(kd_tree)

add_library(coord ${PROJECT_SOURCE_DIR}/include/coord.cpp ${PROJECT_SOURCE_DIR}/include/coord.h)
add_library(point ${PROJECT_SOURCE_DIR}/include/point.cpp ${PROJECT_SOURCE_DIR}/include/point.h)
add_library(node ${PROJECT_SOURCE_DIR}/include/node.cpp ${PROJECT_SOURCE_DIR}/include/node.h)
add_library(kdtree ${PROJECT_SOURCE_DIR}/include/kdtree.cpp ${PROJECT_SOURCE_DIR}/include/kdtree.h)