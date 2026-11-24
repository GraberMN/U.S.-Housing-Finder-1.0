cmake_minimum_required(VERSION 4.4)
project(U_S__Housing_Finder_1_0)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(U_S__Housing_Finder_1_0
        src/Listing.cpp
        src/Listing.h
        src/HashMap.cpp
        src/HashMap.h)

# More files to add above in the near future:
# - src/main.cpp
# - set header file
# - set source file