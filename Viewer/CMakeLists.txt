
# -----------  Viewer  -----------

#  PCL 
find_package(PCL 1.7 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
list(REMOVE_ITEM PCL_LIBRARIES "vtkproj4") 
list(APPEND LIBS ${LIBS} ${PCL_LIBRARIES})


include_directories("../")

add_executable(EagleViewer 
	main.cpp
	eagleviewer.cpp
	dialog.cpp
	)

target_link_libraries(EagleViewer ${ALL_LIBS}
	${LIBS}	
	${OpenCV_LIBS})

