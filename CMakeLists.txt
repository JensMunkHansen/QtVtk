###########
# Project #
###########
cmake_minimum_required(VERSION 3.4)
project(QtVtk)

# Add path for custom modules
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# include(deploy_qt_windows)

#######################
# Folder organisation #
#######################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Indicate that previous configuration exists
set(CONFIGURED TRUE)

###########
# Targets #
###########
add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(resources)
