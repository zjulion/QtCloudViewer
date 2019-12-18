cmake_minimum_required(VERSION 3.0.0)
project(QtCloudViewer)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})


#  PCL 
find_package(PCL 1.7 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
list(REMOVE_ITEM PCL_LIBRARIES "vtkproj4") 
list(APPEND LIBS ${LIBS} ${PCL_LIBRARIES})

# Qt5
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Widgets REQUIRED) 
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Xml REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
 
add_subdirectory(QGLViewer)

set(ALL_LIBS 
	QGLViewer
	Qt5::Widgets
	Qt5::Gui
	Qt5::Core
	Qt5::OpenGL
	Qt5::Xml
	${OPENGL_LIBRARIES}
	)

IF(UNIX)
	list(APPEND LIBS ${LIBS} 
		GL 
		${OPENGL_glu_LIBRARY}
		${GLUT_LIBRARY})

ENDIF(UNIX)

add_subdirectory(Viewer)


 