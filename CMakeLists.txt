
cmake_minimum_required (VERSION 2.6)
project (SceneEditor)

find_package(wxWidgets COMPONENTS core base adv aui ribbon propgrid html xml)
if(wxWidgets_FOUND)
	include(${wxWidgets_USE_FILE})
	# ./png2wx.pl -C src/gen/editor_images.cpp -H src/gen/editor_images.hpp -M IMAGES_HPP data/images/black_tiles.png
	add_definitions(-D_EDITOR=1)
	IF(WIN32)
	ELSE(WIN32)
		add_definitions(-D_LINUX=1)
	ENDIF(WIN32)
	add_executable(SceneEditor WIN32
		auidemo.cpp 
		mycanvas.h mycanvas.cpp app.h app.cpp
		mainframe.h
		)
	target_link_libraries(SceneEditor ${wxWidgets_LIBRARIES})

else()
	MESSAGE("wxWidgets not found!")
endif()
