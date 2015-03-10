/* === Oxygine Scene Editor =================================================== */
/*!	\file app.h
**	\brief Template Header
**
**	\legal
**	Copyright (c) 2015 Milan Dunghubel
**
**	This package is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License as
**	published by the Free Software Foundation; either version 2 of
**	the License, or (at your option) any later version.
**
**	This package is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
**	General Public License for more details.
**	\endlegal
*/
/* ========================================================================= */
#pragma once

/* === S T A R T =========================================================== */

#ifndef __OXYGINE_SCENE_EDITOR_APP_H
#define __OXYGINE_SCENE_EDITOR_APP_H

/* === H E A D E R S ======================================================= */
// For compilers that don't support precompilation, include "wx/wx.h"
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#	include "wx/wx.h"
#endif

#include <wx/app.h>
/* === M A C R O S ========================================================= */

/* === T Y P E D E F S ===================================================== */

/* === C L A S S E S & S T R U C T S ======================================= */
class wxDocManager;

namespace ox2 {
namespace editor {

class App : public wxApp
{
public:
	/** Initialize the application */
	virtual bool OnInit();
	virtual int OnExit();
	virtual void RecreateGUI() = 0;
	//bool SelectLanguage();

	//TextFrame* GetFrame() {
	//	return m_frame;
	//}
	//wxWindow *CreateChildFrame(wxView *view, bool isCanvas);
protected:
	wxDocManager* m_docs;
};

}; // END of namespace editor
}; // END of namespace ox2

/* === E N D =============================================================== */

#endif // __OXYGINE_SCENE_EDITOR_APP_H
