/* === Oxygine Scene Editor================================================= */
/*!	\file sizerptpanel.cpp
**	\brief Template File
**
**	$Id: sizerptpanel.cpp 1543 2008-02-01 09:37:47Z pabs $
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

/* === H E A D E R S ======================================================= */
#include "config.h"

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
/*
** Insert headers here
*/
#include <wx/control.h>
#include <wx/aui/aui.h>
#include <wx/dcclient.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "ox2/editor/sizerptpanel.h"


wxBEGIN_EVENT_TABLE(ox2::editor::wxSizeReportCtrl, wxControl)
EVT_PAINT(ox2::editor::wxSizeReportCtrl::OnPaint)
EVT_SIZE(ox2::editor::wxSizeReportCtrl::OnSize)
EVT_ERASE_BACKGROUND(ox2::editor::wxSizeReportCtrl::OnEraseBackground)
wxEND_EVENT_TABLE()
/* === M A C R O S ========================================================= */

/* === G L O B A L S ======================================================= */

/* === P R O C E D U R E S ================================================= */
ox2::editor::wxSizeReportCtrl::wxSizeReportCtrl(wxWindow* parent, wxWindowID id,
	const wxPoint& pos,
	const wxSize& size,
	wxAuiManager* mgr)
	: wxControl(parent, id, pos, size, wxNO_BORDER)
{
	m_mgr = mgr;
}


void ox2::editor::wxSizeReportCtrl::OnPaint(wxPaintEvent& WXUNUSED(evt))
{
	wxPaintDC dc(this);
	wxSize size = GetClientSize();
	wxString s;
	int h, w, height;

	s.Printf(wxT("Size: %d x %d"), size.x, size.y);

	dc.SetFont(*wxNORMAL_FONT);
	dc.GetTextExtent(s, &w, &height);
	height += 3;
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.SetPen(*wxWHITE_PEN);
	dc.DrawRectangle(0, 0, size.x, size.y);
	dc.SetPen(*wxLIGHT_GREY_PEN);
	dc.DrawLine(0, 0, size.x, size.y);
	dc.DrawLine(0, size.y, size.x, 0);
	dc.DrawText(s, (size.x - w) / 2, ((size.y - (height * 5)) / 2));

	if (m_mgr)
	{
		wxAuiPaneInfo pi = m_mgr->GetPane(this);

		s.Printf(wxT("Layer: %d"), pi.dock_layer);
		dc.GetTextExtent(s, &w, &h);
		dc.DrawText(s, (size.x - w) / 2, ((size.y - (height * 5)) / 2) + (height * 1));

		s.Printf(wxT("Dock: %d Row: %d"), pi.dock_direction, pi.dock_row);
		dc.GetTextExtent(s, &w, &h);
		dc.DrawText(s, (size.x - w) / 2, ((size.y - (height * 5)) / 2) + (height * 2));

		s.Printf(wxT("Position: %d"), pi.dock_pos);
		dc.GetTextExtent(s, &w, &h);
		dc.DrawText(s, (size.x - w) / 2, ((size.y - (height * 5)) / 2) + (height * 3));

		s.Printf(wxT("Proportion: %d"), pi.dock_proportion);
		dc.GetTextExtent(s, &w, &h);
		dc.DrawText(s, (size.x - w) / 2, ((size.y - (height * 5)) / 2) + (height * 4));
	}
}

void ox2::editor::wxSizeReportCtrl::OnEraseBackground(wxEraseEvent& WXUNUSED(evt))
{
	// intentionally empty
}

void ox2::editor::wxSizeReportCtrl::OnSize(wxSizeEvent& WXUNUSED(evt))
{
	Refresh();
}
/* === M E T H O D S ======================================================= */

/* === E N T R Y P O I N T ================================================= */


