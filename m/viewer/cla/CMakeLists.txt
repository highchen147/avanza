
file(GLOB cla_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
file(GLOB cla_headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#

add_library(cla ${cla_sources} ${cla_headers})
target_include_directories (cla PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
