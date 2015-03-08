

add_executable(SceneEditor WIN32
		core.h core.cpp
		mainframe.cpp mainframe.h
		app.h app.cpp
		scene.cpp scene.h
		node.h node.cpp
		panels.h panels.cpp
		resources.h resources.cpp
		dialogs.h dialogs.cpp
		editor.rc
		prefs.h prefs.cpp
		)
target_link_libraries(SceneEditor ${wxWidgets_LIBRARIES} ${JSONCPP_LIBRARY})

install(TARGETS SceneEditor
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static)

