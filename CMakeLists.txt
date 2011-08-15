PROJECT(libredwgpp)

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

parser/objects/blockcontrol.cpp
parser/objects/dictionary.cpp
parser/objects/entity.cpp
parser/objects/face3d.cpp
parser/objects/layer.cpp
parser/objects/line.cpp
parser/objects/object.cpp
parser/objects/shapefile.cpp
parser/objects/undocumentedcontrol.cpp
parser/objects/vertex3d.cpp

parser/class.cpp
parser/dwgbuffer.cpp
parser/parser.cpp
parser/section.cpp
parser/version.cpp

parser/r2000/parser2000.cpp

parser/r2004/decoder2004_2.cpp
parser/r2004/parser2004.cpp
parser/r2004/section2004.cpp
parser/r2004/sectioninfo.cpp
parser/r2004/sectionmap.cpp
parser/r2004/sectionobjects.cpp

parser/sections/classes.cpp
parser/sections/objects.cpp

schema/colour.cpp
schema/face3d.cpp
)

######## LINKER ########

LINK_LIBRARIES(
boost_filesystem

core
)

######## LIBRARIES ########

ADD_LIBRARY(libredwgpp SHARED ${DWG_SRC})
