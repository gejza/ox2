/* === Oxygine Scene Editor================================================= */
/*!	\file editor_app.cpp
**	\brief Template File
**
**	$Id: editor_app.cpp 1543 2008-02-01 09:37:47Z pabs $
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

#include "ox2/editor/app.h"
/*
** Insert headers here
*/

#include <wx/docview.h>
#include <wx/config.h>

/* === M A C R O S ========================================================= */

/* === G L O B A L S ======================================================= */

/* === P R O C E D U R E S ================================================= */
bool ox2::editor::App::OnInit()
{
	if ( !wxApp::OnInit() )
		return false;

	// make sure to call this first
	wxInitAllImageHandlers();
	
	//// Create a document manager
	m_docs = new wxDocManager;

	return true;
}

int ox2::editor::App::OnExit()
{
	wxDocManager * const manager = wxDocManager::GetDocumentManager();
	manager->FileHistorySave(*wxConfig::Get());
	delete manager;

	return wxApp::OnExit();
}

/* === M E T H O D S ======================================================= */

/* === E N T R Y P O I N T ================================================= */


