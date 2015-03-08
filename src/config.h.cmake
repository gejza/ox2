#ifndef CONFIG_H
#define CONFIG_H
 
#cmakedefine WITH_FOO
#cmakedefine WITH_BAR
 
#cmakedefine BAZ @BAZ@

#cmakedefine SCENEEDITOR_NAME "@SCENEEDITOR_NAME@"

#cmakedefine SCENEEDITOR_VERSION_MAJOR @SCENEEDITOR_VERSION_MAJOR@
#cmakedefine SCENEEDITOR_VERSION_MINOR @SCENEEDITOR_VERSION_MINOR@
#cmakedefine SCENEEDITOR_VERSION_PATCH @SCENEEDITOR_VERSION_PATCH@
#cmakedefine SCENEEDITOR_VERSION "@SCENEEDITOR_VERSION@"

#cmakedefine SCENEEDITOR_HOMEPAGE "@SCENEEDITOR_HOMEPAGE@"

#include <wx/version.h>
#if wxCHECK_VERSION(3, 0, 1)
#define USE_PREFS
#endif

#endif // CONFIG_H
