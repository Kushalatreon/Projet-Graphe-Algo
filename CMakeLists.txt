cmake_minimum_required(VERSION 3.9)
project(Graphes)

set(CMAKE_CXX_STANDARD 11)

add_executable(Graphes main.cpp Sources/Graphe.cpp Headers/Graphe.h Sources/GrapheOriente.cpp Headers/GrapheOriente.h Sources/GrapheNonOriente.cpp Headers/GrapheNonOriente.h Sources/GrapheValue.cpp Headers/GrapheValue.h Sources/GrapheNonValue.cpp Headers/GrapheNonValue.h)