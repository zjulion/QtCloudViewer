project(QGLViewer)

 


file(GLOB srcs 
	qglviewer.h 
	  camera.h 
	  manipulatedFrame.h 
	  manipulatedCameraFrame.h 
	  frame.h 
	  constraint.h 
	  keyFrameInterpolator.h 
	  mouseGrabber.h 
	  quaternion.h 
	  vec.h 
	  domUtils.h 
	  config.h
	  qglviewer.cpp 
	  camera.cpp 
	  manipulatedFrame.cpp 
	  manipulatedCameraFrame.cpp 
	  frame.cpp 
	  saveSnapshot.cpp 
	  constraint.cpp 
	  keyFrameInterpolator.cpp 
	  mouseGrabber.cpp 
	  quaternion.cpp 
	  vec.cpp)

add_definitions(-DNO_VECTORIAL_RENDER)

IF(UNIX)
	add_library(${PROJECT_NAME} SHARED ${srcs})
ENDIF(UNIX)

IF(WIN32)
	add_library(${PROJECT_NAME} STATIC ${srcs})
ENDIF(WIN32)

target_link_libraries(${PROJECT_NAME}
	Qt5::Widgets
	Qt5::Gui
	Qt5::Core
	Qt5::OpenGL
	Qt5::Xml
	)
 