/* === Oxygine Scene Editor =================================================== */
/*!	\file frame.h
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

#ifndef __OXYGINE_SCENE_EDITOR_FRAME_H
#define __OXYGINE_SCENE_EDITOR_FRAME_H

/* === H E A D E R S ======================================================= */
#include <wx/docview.h>
#include <wx/aui/framemanager.h>

/* === M A C R O S ========================================================= */

/* === T Y P E D E F S ===================================================== */

/* === C L A S S E S & S T R U C T S ======================================= */

class wxDocManager;

namespace ox2 {
namespace editor {

class wxSizeReportCtrl;

class Frame : public wxDocParentFrame
{
public:
	Frame(wxDocManager* docs,  wxFrame *parent, wxWindowID id, const wxString &title, const wxPoint& pos, const wxSize& size);
	virtual ~Frame();
protected:
	ox2::editor::wxSizeReportCtrl* CreateSizeReportCtrl(int width = 80, int height = 80);

	wxAuiManager m_mgr;
};

}; // END of namespace editor
}; // END of namespace studio

/* === E N D =============================================================== */

#endif // __OXYGINE_SCENE_EDITOR_FRAME_H
