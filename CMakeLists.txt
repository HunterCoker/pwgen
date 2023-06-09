cmake_minimum_required(VERSION 3.25)
project(pwgen)

set(CMAKE_CXX_STANDARD 17)

add_executable(pwgen main.cpp pwgen.cpp pwgen.h)
