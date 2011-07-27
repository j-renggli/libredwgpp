PROJECT(libredwg2)

cmake_minimum_required(VERSION 2.6)

######## SETUP ########

SET(CMAKE_VERBOSE_MAKEFILE 0)
SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -O -ansi -pedantic -g -pg -DDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3 -ansi -pedantic -g -pg")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin)

######## SOURCE CODE ########

INCLUDE_DIRECTORIES(. ..)

SET(DWG_SRC
errorcodes.cpp

file/archive.cpp

parser/decoder2004_2.cpp
parser/dwgbuffer.cpp
parser/parser.cpp
parser/parser2004.cpp
)

######## LINKER ########

LINK_LIBRARIES(
boost_filesystem

core
)

######## LIBRARIES ########

ADD_LIBRARY(libredwg2 SHARED ${DWG_SRC})

SET(TESTING_SRC
test.cpp
)

LINK_LIBRARIES(
libredwg2
)

ADD_EXECUTABLE(testing ${TESTING_SRC})
