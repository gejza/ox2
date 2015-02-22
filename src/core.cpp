///////////////////////////////////////////////////////////////////////////////
// Name:        auidemo.cpp
// Purpose:     wxaui: wx advanced user interface - sample/test program
// Author:      Benjamin I. Williams
// Modified by:
// Created:     2005-10-03
// Copyright:   (C) Copyright 2005, Kirix Corporation, All Rights Reserved.
// Licence:     wxWindows Library Licence, Version 3.1
///////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "core.h"
#include "scene.h"
#include "mainframe.h"

#include <wx/treectrl.h>

CoreTraits* CoreTraits::_this = NULL;

CoreTraits* CoreTraits::get(MainFrame* main)
{
	if (_this == NULL) {
		wxASSERT(main != NULL);
		_this = new CoreTraits(main);
	}
	return _this;
}

CoreTraits::CoreTraits(MainFrame* main)
	: _main(main), _tree_ctrl(0), _prop_grid(0), _tabs(0), _current(0) {
	_this = this;
}

void CoreTraits::SetActiveScene(Scene* scene)
{
	_current = scene;
	if (_current) {
		_current->UpdateTree(this->GetTreeCtrl());
	}
}

const char* CfgGeneric::ID = "Generic";

wxTreeCtrl* CoreTraits::GetTreeCtrl()
{
	if (!_tree_ctrl) {
		wxASSERT(_main != NULL);
		_tree_ctrl = new wxTreeCtrl(_main, ID_TreeCtrl,
			wxPoint(0, 0), wxSize(160, 250),
			wxTR_DEFAULT_STYLE | wxNO_BORDER);

		wxImageList* imglist = new wxImageList(16, 16, true, 2);
		imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16, 16)));
		imglist->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16)));
		_tree_ctrl->AssignImageList(imglist);
	}
	return _tree_ctrl;
}

wxPropertyGrid* CoreTraits::GetPropGrid()
{
	if (!_prop_grid) {
		// Construct wxPropertyGrid control
		wxASSERT(_main != NULL);
		_prop_grid = new wxPropertyGrid(
			_main, // parent
			wxID_ANY, // id
			wxDefaultPosition, // position
			wxSize(150, 250), // size
			// Here are just some of the supported window styles
			wxPG_AUTO_SORT | // Automatic sorting after items added
			wxPG_SPLITTER_AUTO_CENTER | // Automatically center splitter until user manually adjusts it
			// Default style
			wxPG_DEFAULT_STYLE | wxNO_BORDER | wxWANTS_CHARS);
		// Window style flags are at premium, so some less often needed ones are
		// available as extra window styles (wxPG_EX_xxx) which must be set using
		// SetExtraStyle member function. wxPG_EX_HELP_AS_TOOLTIPS, for instance,
		// allows displaying help strings as tool tips.
		_prop_grid->SetExtraStyle(wxPG_EX_HELP_AS_TOOLTIPS);
	}
	return _prop_grid;
}

wxAuiNotebook* CoreTraits::GetNotebook()
{
	if (!_tabs) {
		long m_notebook_style;
		// set up default notebook style
		m_notebook_style = wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_TAB_EXTERNAL_MOVE | wxNO_BORDER;
		long m_notebook_theme = 0;

		wxASSERT(_main != NULL);
		// create the notebook off-window to avoid flicker
		wxSize client_size = _main->GetClientSize();

		_tabs = new wxAuiNotebook(_main, wxID_ANY,
			wxPoint(client_size.x, client_size.y),
			wxSize(430, 200),
			m_notebook_style);
		_tabs->Freeze();

		wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));
	}
	return _tabs;
}
