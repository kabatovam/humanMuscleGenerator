project(MuscleGenerator)
cmake_minimum_required(VERSION 2.8.11)
#set(CMAKE_PREFIX_PATH "/Users/andrea/Developer/Qt5/5.2.1/clang_64")

# Install destinations
set( CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/_install CACHE PATH "Installation Destination" FORCE)
SET( INSTALL_DES ./ CACHE PATH "Where to install to." )

# some .ui files
#  SET( SAMPLE_UIS
#       mainWindow.ui
#  )



# Qt library
find_package(Qt5Core)
#find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
set(CMAKE_AUTOMOC ON)
include_directories(${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")



### OpenGL
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)




### Qt4
#find_package(Qt5 REQUIRED)
# autogenerate all moc files
#set( CMAKE_AUTOMOC TRUE )
#add_definitions(${QT_DEFINITIONS})
#set(QT_USE_QMAIN true)
#SET(QT_USE_QTOPENGL TRUE)
#include(${QT_USE_FILE})




INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
 # this will run uic on .ui files:
 # QT4_WRAP_UI( SAMPLE_UI_HDRS ${SAMPLE_UIS} )
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
qt5_use_modules(MuscleGenerator Widgets OpenGL)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${QT5Widgets_LIBRARIES} ${QT_LIBRARIES})



### install

INSTALL(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${INSTALL_DES} COMPONENT Runtime )
