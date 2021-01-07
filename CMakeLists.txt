cmake_minimum_required(VERSION 3.17)
project(City)

set(CMAKE_CXX_STANDARD 14)

add_executable(City City.cpp Graph.cpp Graph.h Edge.h AddedFunctionality.h User.cpp User.h Usermass.cpp Usermass.h)