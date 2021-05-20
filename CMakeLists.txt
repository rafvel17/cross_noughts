cmake_minimum_required (VERSION 2.8.12)

set (CMAKE_GENERATOR_PLATFORM x64)
set (SOURCES framework.cpp fun.cpp Project_cross_noughts_kurs.cpp)
set (RESOURCES Project_cross_noughts_kurs.ico small.ico Project_cross_noughts_kurs.rc)
project (cross_noughts)
add_executable (cross_noughts WIN32 ${SOURCES} ${RESOURCES})