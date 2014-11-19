project(DP_examples)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
set(VL_ROOT "C:/martinka/VisLib/install")
find_package(VL COMPONENTS VLCore VLGraphics VLVG VLVolume VLMolecule VLQt4 VLWin32 REQUIRED)
### Qt4
find_package(Qt4 REQUIRED)
# autogenerate all moc files
set( CMAKE_AUTOMOC TRUE )
add_definitions(${QT_DEFINITIONS})
set(QT_USE_QMAIN true)
SET(QT_USE_QTOPENGL TRUE)
include(${QT_USE_FILE})
include_directories(${VL_INCLUDE_DIRS})
# find ${OPENGL_LIBRARIES} to be used later
find_package(OpenGL REQUIRED)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${VL_LIBRARIES} ${OPENGL_LIBRARIES} ${QT_LIBRARIES}  ${QT_QTMAIN_LIBRARY})

