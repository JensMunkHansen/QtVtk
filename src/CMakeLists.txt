###########
# Project #
###########

if(NOT CONFIGURED)
        cmake_minimum_required(VERSION 3.4)
        project(QtVtk)
        set(PROJECT_SOURCE_DIR ../)
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
        link_directories(${PROJECT_SOURCE_DIR})
        # Indicate that previous configuration exists
        set(CONFIGURED TRUE)
endif(NOT CONFIGURED)

#########################
# External Dependencies #
#########################

find_package(Qt5 COMPONENTS Quick Widgets Qml QuickControls2 OpenGL REQUIRED)

if (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# VTK Libraries
set(VTK_DIR $ENV{VTK_DIR})
find_package(VTK 8.2 REQUIRED NO_MODULE)
include(${VTK_USE_FILE})

# Headers directories
include_directories(${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/src
)

# Generated headers directories
include_directories(${CMAKE_CURRENT_BINARY_DIR})

###########
# Targets #
###########

# Sources
set (SOURCES
  main.cpp
  CanvasHandler.cpp
  CommandModel.cpp
  CommandModelAdd.cpp
  CommandModelTranslate.cpp
  Model.cpp
  ProcessingEngine.cpp
  QVTKFramebufferObjectItem.cpp
  QVTKFramebufferObjectRenderer.cpp
)

# The usual location for the installed qml sources
set(QTVTK_QML_DIR "${Qt5Core_DIR}/../../../qml")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)

# Qt Resources
qt5_add_resources(RESOURCES qml.qrc)

# Build executable
if (WIN32)
  add_executable(QtVtk WIN32 ${HEADERS} ${SOURCES} ${RESOURCES})
else()
  add_executable(QtVtk ${HEADERS} ${SOURCES} ${RESOURCES})
endif()

# Link to libraries
target_link_libraries(QtVtk Qt5::Quick Qt5::Widgets Qt5::Qml Qt5::QuickControls2 ${VTK_LIBRARIES} ${SYSTEM_LIBS})

if (WIN32)
  find_program(TOOL_WINDEPLOYQT NAMES windeployqt PATHS "${Qt5Core_DIR}/../../../bin")
  find_program(TOOL_QTENV2 NAMES qtenv2.bat PATHS "${Qt5Core_DIR}/../../../bin")

  if (1)
    add_custom_command(TARGET QtVtk POST_BUILD
      DEPENDS ${TOOL_WINDEPLOYQT} ${TOOL_QTENV2}
      COMMAND ${TOOL_QTENV2}
      COMMAND ${TOOL_WINDEPLOYQT} $<TARGET_FILE:QtVtk> $<$<CONFIG:Release>:--release>$<$<NOT:$<CONFIG:Release>>:--debug>
      WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
  else()
    windeployqt(QtVtk ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
  endif()

  set(VTK_RUNTIME_DEPENDENCIES
    vtkCommonColor-8.2.dll
    vtkCommonCore-8.2.dll
    vtkCommonComputationalGeometry-8.2.dll
    vtkCommonCore-8.2.dll
    vtkCommonDataModel-8.2.dll
    vtkCommonExecutionModel-8.2.dll
    vtkCommonMath-8.2.dll
    vtkCommonMisc-8.2.dll
    vtkCommonSystem-8.2.dll
    vtkCommonTransforms-8.2.dll
    vtkDICOMParser-8.2.dll
    vtkFiltersCore-8.2.dll
    vtkFiltersExtraction-8.2.dll
    vtkFiltersGeneral-8.2.dll
    vtkFiltersGeometry-8.2.dll
    vtkFiltersHybrid-8.2.dll
    vtkFiltersModeling-8.2.dll
    vtkFiltersSources-8.2.dll
    vtkFiltersStatistics-8.2.dll
    vtkfreetype-8.2.dll
    vtkglew-8.2.dll
    vtkGUISupportQt-8.2.dll
    vtkInteractionImage-8.2.dll
    vtkImagingCore-8.2.dll
    vtkImagingColor-8.2.dll
    vtkImagingGeneral-8.2.dll
    vtkImagingFourier-8.2.dll
    vtkImagingHybrid-8.2.dll
    vtkImagingSources-8.2.dll
    vtkInteractionStyle-8.2.dll
    vtkInteractionWidgets-8.2.dll
    vtkIOCore-8.2.dll
    vtkIOImage-8.2.dll
    vtkIOGeometry-8.2.dll
    vtkjpeg-8.2.dll
    vtkmetaio-8.2.dll
    vtkpng-8.2.dll
    vtkRenderingCore-8.2.dll
    vtkRenderingFreeType-8.2.dll
    vtkRenderingOpenGL2-8.2.dll
    vtkRenderingAnnotation-8.2.dll
    vtkRenderingGL2PSOpenGL2-8.2.dll
    vtkdoubleconversion-8.2.dll
    vtkgl2ps-8.2.dll
    vtksys-8.2.dll
    vtklzma-8.2.dll
    vtklz4-8.2.dll
    vtktiff-8.2.dll
    vtkzlib-8.2.dll
  )
  set(VTK_RUNTIME_LIBRARIES)
  set(VTK_RUNTIME_LIBRARIES_DEBUG)

  foreach(DLL ${VTK_RUNTIME_DEPENDENCIES})
    set(FOUND_DLL "FOUND_DLL-NOTFOUND")
    find_file(FOUND_DLL
      ${DLL}
      PATHS "${VTK_DIR}/bin/Release"
      NO_DEFAULT_PATH)
    if (FOUND_DLL)
      list(APPEND VTK_RUNTIME_LIBRARIES ${FOUND_DLL})
    endif()
  endforeach(DLL)

  foreach(DLL ${VTK_RUNTIME_DEPENDENCIES})
    set(FOUND_DLL "FOUND_DLL-NOTFOUND")
    find_file(FOUND_DLL
      ${DLL}
      PATHS "${VTK_DIR}/bin/Debug"
      NO_DEFAULT_PATH)
    if (FOUND_DLL)
      list(APPEND VTK_RUNTIME_LIBRARIES_DEBUG ${FOUND_DLL})
    endif()
  endforeach(DLL)

  foreach(DLL ${VTK_RUNTIME_LIBRARIES})
    add_custom_command(TARGET QtVtk POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E
      $<$<NOT:$<CONFIG:Release>>:echo>
      $<$<NOT:$<CONFIG:Release>>:"omitted">
      copy_if_different "${DLL}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION:MRUSViewer>")
  endforeach(DLL)

  # Consider using
  # string(REPLACE "Release" "Debug" VTK_RUNTIME_DEPENDENCIES "${VTK_RUNTIME_DEPENDENCIES}")


  foreach(DLL ${VTK_RUNTIME_LIBRARIES_DEBUG})
    add_custom_command(TARGET QtVtk POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E
      $<$<CONFIG:Release>:echo>
      $<$<CONFIG:Release>:"omitted">
      copy_if_different "${DLL}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION:MRUSViewer>")
  endforeach(DLL)
endif()
