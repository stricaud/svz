cmake_minimum_required(VERSION 2.8)
project(picture-maker)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

add_subdirectory(src)

