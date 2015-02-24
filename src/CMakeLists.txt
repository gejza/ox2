

add_executable(SceneEditor WIN32
		mainframe.cpp mainframe.h
		app.h app.cpp
		scene.cpp scene.h
		node.h node.cpp editor.rc
		)
target_link_libraries(SceneEditor ${wxWidgets_LIBRARIES} ${JSONCPP_LIBRARY})
