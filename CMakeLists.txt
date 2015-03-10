
cmake_minimum_required (VERSION 2.6)
project (SceneEditor)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}/cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})




option(WITH_TESTS "Enable building of unit tests" ON)
option(WITH_GUI_TESTS "Enable building of GUI tests" OFF)
option(WITH_LTO "Enable Link Time Optimization (LTO)" OFF)
option(WITH_LANGUAGES "Enable gettext" ON)
option(WITH_GENDOX "Generate doxygen" OFF)
option(WITH_CTAGS "Generate ctags" OFF)

IF(WITH_LANGUAGES)
include(cmake/GettextTranslate.cmake)
ENDIF(WITH_LANGUAGES)

set(wxWidgets_USE_DEBUG, FALSE)
set(wxWidgets_USE_UNICODE, TRUE)

set(SCENEEDITOR_NAME "Oxygine Scene Editor")
set(SCENEEDITOR_VERSION_MAJOR "1")
set(SCENEEDITOR_VERSION_MINOR "9")
set(SCENEEDITOR_VERSION_PATCH "85")
set(SCENEEDITOR_VERSION_SHORT "${SCENEEDITOR_VERSION_MAJOR}.${SCENEEDITOR_VERSION_MINOR}.${SCENEEDITOR_VERSION_PATCH}")
set(SCENEEDITOR_VERSION "${SCENEEDITOR_VERSION_SHORT} alpha 6")
set(SCENEEDITOR_HOMEPAGE "https://bitbucket.org/GejzaX/oxygine-scene-editor")

if(APPLE AND "${CMAKE_INSTALL_PREFIX}" STREQUAL "/usr/local")
	set(CMAKE_INSTALL_PREFIX "/Applications")	
endif()

if(MINGW)
  set(BIN_INSTALL_DIR    ".")
  set(PLUGIN_INSTALL_DIR ".")
  set(DATA_INSTALL_DIR   "share")
elseif(APPLE)
  set(BIN_INSTALL_DIR    ".")
  set(PLUGIN_INSTALL_DIR ".")
  set(DATA_INSTALL_DIR   "${PROGNAME}.app/Contents/Resources")
else()
  include(GNUInstallDirs)
  set(BIN_INSTALL_DIR    "${CMAKE_INSTALL_BINDIR}")
  set(PLUGIN_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/sceneeditor")
  set(DATA_INSTALL_DIR   "${CMAKE_INSTALL_DATAROOTDIR}/sceneeditor")
endif()

if(WITH_TESTS)
  enable_testing()
endif(WITH_TESTS)



find_package(wxWidgets COMPONENTS core base adv aui ribbon propgrid html xml)
if(wxWidgets_FOUND)
	include(${wxWidgets_USE_FILE})
	# ./png2wx.pl -C src/gen/editor_images.cpp -H src/gen/editor_images.hpp -M IMAGES_HPP data/images/black_tiles.png
	add_definitions(-D_EDITOR=1)
	IF(WIN32)
	ELSE(WIN32)
		add_definitions(-D_LINUX=1)
	ENDIF(WIN32)
else()
	MESSAGE("wxWidgets not found!")
endif()

if(NOT (${CMAKE_VERSION} VERSION_LESS 2.8.3))
  set(PRINT_SUMMARY ON)
  include(FeatureSummary)
endif()

set(LOCALEDIR "share/locale")

CONFIGURE_FILE( ${CMAKE_SOURCE_DIR}/src/config.h.cmake ${CMAKE_SOURCE_DIR}/src/config.h )

include_directories(include)

add_library(ox2editor STATIC 
	src/frame.cpp include/ox2/editor/frame.h
	src/sizerptpanel.cpp include/ox2/editor/sizerptpanel.h
	src/editor_app.cpp include/ox2/editor/app.h)
target_link_libraries(ox2editor ${wxWidgets_LIBRARIES})
	
#install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"        
#         DESTINATION include)

add_subdirectory(src)
IF(WITH_LANGUAGES)
add_subdirectory(po)
ENDIF(WITH_LANGUAGES)

IF(WITH_GENDOX)
	# add a target to generate API documentation with Doxygen
	find_package(Doxygen)
	if(DOXYGEN_FOUND)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(doc
	${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
	else(DOXYGEN_FOUND)
		MESSAGE("Doxygen not found!")
	endif(DOXYGEN_FOUND)
ENDIF(WITH_GENDOX)

# Generate tag files
IF(WITH_CTAGS)
IF(UNIX)
set_source_files_properties(tags PROPERTIES GENERATED true)
add_custom_target(tags
	#COMMAND ctags -R --sort=1 --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++ -f tags ${CMAKE_CURRENT_SOURCE_DIR}/src
	COMMAND ctags -R --c++-kinds=+p --fields=+iaS --extra=+q -f tags ${CMAKE_CURRENT_SOURCE_DIR}/src
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

#COMMAND ln -sf ${CMAKE_CURRENT_BINARY_DIR}/tags ${CMAKE_BINARY_DIR}

find_program(CTAGS_PATH ctags)
if(CTAGS_PATH)
	message(STATUS "Found ctags: ${CTAGS_PATH}")
	add_dependencies(SceneEditor tags)
endif(CTAGS_PATH)
ENDIF(UNIX)
ENDIF(WITH_CTAGS)


if(PRINT_SUMMARY)
  feature_summary(WHAT ALL)
endif()

INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Oxygine Scene Editor")
SET(CPACK_PACKAGE_VENDOR "Milan Dunghubel")
SET(CPACK_PACKAGE_CONTACT "Milan Dunghubel <milan.dunghubel@gmail.com>")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
SET(CPACK_PACKAGE_VERSION_MAJOR ${SCENEEDITOR_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${SCENEEDITOR_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${SCENEEDITOR_VERSION_PATCH})
#SET(CPACK_PACKAGE_INSTALL_DIRECTORY "${SCENEEDITOR_NAME} ${SCENEEDITOR_VERSION_SHORT}")
IF(WIN32 AND NOT UNIX)
  SET(CPACK_GENERATOR "NSIS")
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
  SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}\\\\res\\\\InstallIcon.bmp")
  SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
  SET(CPACK_NSIS_DISPLAY_NAME "${SCENEEDITOR_NAME} ${SCENEEDITOR_VERSION_SHORT}")
  #SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
  #SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
  SET(CPACK_NSIS_CONTACT "milan.dunghubel@gmail.com")
  SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
  SET(CPACK_GENERATOR "DEB")
  SET(CPACK_STRIP_FILES "bin/SceneEditor")
  SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)
SET(CPACK_PACKAGE_EXECUTABLES "MyExecutable" "My Executable")



#SET(CPACK_DEBIAN_PACKAGE_NAME  )
SET(CPACK_DEBIAN_PACKAGE_VERSION ${SCENEEDITOR_VERSION_SHORT})
#SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE  )
#SET(CPACK_DEBIAN_PACKAGE_DEPENDS  )
#SET(CPACK_DEBIAN_PACKAGE_MAINTAINER  )
#SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Milan Dunghubel") #required
#SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION  )
#SET(CPACK_DEBIAN_PACKAGE_SECTION  )
#SET(CPACK_DEBIAN_PACKAGE_PRIORITY  )
SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE ${SCENEEDITOR_HOMEPAGE})
SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS OFF)
SET(CPACK_DEBIAN_PACKAGE_DEBUG  OFF)
 
INCLUDE(CPack)

