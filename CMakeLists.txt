cmake_minimum_required(VERSION 2.8)

project( Threshould_HSV_cv )

#The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)
 
# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/HSVConfig.h.in"
#  "${PROJECT_BINARY_DIR}/HSVConfig.h"
#  )
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

find_package( OpenCV REQUIRED )
add_executable( hsvthresh hsvthresh.cpp )
target_link_libraries( hsvthresh ${OpenCV_LIBS} )

# add the install targets
install (TARGETS hsvthresh DESTINATION /home/nithin/dev/scripts)
#install (FILES "${PROJECT_BINARY_DIR}/HSVConfig.h"        
#         DESTINATION include)
