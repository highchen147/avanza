#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(qNet6000RootDataViewer)


add_subdirectory (cla)


#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED)

cmake_policy(SET CMP0042 NEW)



#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${ROOT_INCLUDE_DIRS}
                   )
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#

add_executable(qNet6000RootDataViewer viewer.cc ${sources} ${headers})
target_link_libraries(qNet6000RootDataViewer cla ${ROOT_LIBRARIES} )
