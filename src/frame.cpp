/* === Oxygine Scene Editor================================================= */
/*!	\file frame.cpp
**	\brief Template File
**
**	$Id: frame.cpp 1543 2008-02-01 09:37:47Z pabs $
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

#include "ox2/editor/frame.h"
#include "ox2/editor/sizerptpanel.h"
/*
** Insert headers here
*/

/* === M A C R O S ========================================================= */

/* === G L O B A L S ======================================================= */

/* === P R O C E D U R E S ================================================= */
ox2::editor::Frame::Frame(wxDocManager* docs,  wxFrame *parent, wxWindowID id, const wxString &title, const wxPoint& pos, const wxSize& size) : wxDocParentFrame(docs, parent, id, title, pos, size)
{
	m_mgr.SetManagedWindow(this);
}

ox2::editor::Frame::~Frame()
{
	m_mgr.UnInit();
}

ox2::editor::wxSizeReportCtrl* ox2::editor::Frame::CreateSizeReportCtrl(int width, int height)
{
	ox2::editor::wxSizeReportCtrl* ctrl = new ox2::editor::wxSizeReportCtrl(this, wxID_ANY,
                                   wxDefaultPosition,
                                   wxSize(width, height), &m_mgr);
    return ctrl;
}

/* === M E T H O D S ======================================================= */

/* === E N T R Y P O I N T ================================================= */


