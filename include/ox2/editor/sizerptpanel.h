/* === Oxygine Scene Editor =================================================== */
/*!	\file sizerptpanel.h
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

#ifndef __OXYGINE_SCENE_EDITOR_SIZERPTPANEL_H
#define __OXYGINE_SCENE_EDITOR_SIZERPTPANEL_H

/* === H E A D E R S ======================================================= */
#include <wx/control.h>

/* === M A C R O S ========================================================= */

/* === T Y P E D E F S ===================================================== */

/* === C L A S S E S & S T R U C T S ======================================= */
class wxAuiManager;

namespace ox2 {
namespace editor {

	// -- wxSizeReportCtrl --
	// (a utility control that always reports it's client size)

	class wxSizeReportCtrl : public wxControl
	{
	public:

		wxSizeReportCtrl(wxWindow* parent, wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			wxAuiManager* mgr = NULL);

	private:

		void OnPaint(wxPaintEvent& WXUNUSED(evt));

		void OnEraseBackground(wxEraseEvent& WXUNUSED(evt));

		void OnSize(wxSizeEvent& WXUNUSED(evt));
	private:

		wxAuiManager* m_mgr;

		wxDECLARE_EVENT_TABLE();
	};

}; // END of namespace editor
}; // END of namespace ox2

/* === E N D =============================================================== */

#endif // __OXYGINE_SCENE_EDITOR_SIZERPTPANEL_H


