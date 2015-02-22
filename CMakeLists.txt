
cmake_minimum_required (VERSION 2.6)
project (SceneEditor)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} cmake)

message("----------- trying to find JsonCpp-------------")
find_package(JsonCpp)

if(JSONCPP_FOUND)
    message("INFO: we found LibJsonCpp on your pc.")
    message(JSONCPP_FOUND = ${JSONCPP_FOUND})
    message(JSONCPP_INCLUDE_DIR = ${JSONCPP_INCLUDE_DIR}) 
    message(JSONCPP_LIBRARY = ${JSONCPP_LIBRARY})
	include_directories(${JSONCPP_INCLUDE_DIR})
else(JSONCPP_FOUND)
    message("WARNING: we couldn't find LibJsonCpp on your pc. DLC is disabled.")
endif(JSONCPP_FOUND)

#set(LIBS ${JSONCPP_LIBRARY})

# add the executable
add_executable(jsonparser testjson.cpp)
target_link_libraries(jsonparser ${JSONCPP_LIBRARY})


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
		mainframe.cpp mainframe.h
		app.h app.cpp
		scene.cpp scene.h
		node.h node.cpp
		)
	target_link_libraries(SceneEditor ${wxWidgets_LIBRARIES} ${JSONCPP_LIBRARY})

else()
	MESSAGE("wxWidgets not found!")
endif()
