/* === Oxygine Scene Editor =================================================== */
/*!	\file prefs.h
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

#ifndef __OXYGINE_SCENE_EDITOR_PREFS_H
#define __OXYGINE_SCENE_EDITOR_PREFS_H

#include "config.h"

#ifdef USE_PREFS
/* === H E A D E R S ======================================================= */

#include <wx/preferences.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/listbox.h>
#include <wx/artprov.h>
#include <wx/log.h>

#include "dialogs.h"
#include "core.h"
/* === M A C R O S ========================================================= */

/* === T Y P E D E F S ===================================================== */

/* === C L A S S E S & S T R U C T S ======================================= */

//namespace studio {
class PrefsPageTopicsPanel : public wxPanel
{
public:
    PrefsPageTopicsPanel(wxWindow *parent) : wxPanel(parent)
    {
        wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(new wxStaticText(this, wxID_ANY, "Search in these topics:"), wxSizerFlags().Border());
        wxListBox *box = new wxListBox(this, wxID_ANY);
        box->SetMinSize(wxSize(400, 300));
        sizer->Add(box, wxSizerFlags(1).Border().Expand());
        m_fulltext = new wxCheckBox(this, wxID_ANY, "Automatically build fulltext index");
        sizer->Add(m_fulltext, wxSizerFlags().Border());

        SetSizerAndFit(sizer);

        if ( wxPreferencesEditor::ShouldApplyChangesImmediately() )
        {
            m_fulltext->Connect(wxEVT_CHECKBOX,
                                wxCommandEventHandler(PrefsPageTopicsPanel::ChangedFulltext),
                                NULL, this);
        }
    }
   virtual bool TransferDataToWindow()
    {
        // This is the place where you can initialize values, e.g. from wxConfig.
        // For demonstration purposes, we just set hardcoded values.
        m_fulltext->SetValue(true);
        // TODO: handle the listbox
        return true;
    }

    virtual bool TransferDataFromWindow()
    {
        // Called on platforms with modal preferences dialog to save and apply
        // the changes.
        wxCommandEvent dummy;
        ChangedFulltext(dummy);
        // TODO: handle the listbox
        return true;
    }

private:
    void ChangedFulltext(wxCommandEvent& WXUNUSED(e))
    {
        // save new m_fulltext value and apply the change to the app
    }

    wxCheckBox *m_fulltext;
};

class PrefsPageGeneralPanel : public PrefsPageGeneralPanelBase
{
public:
    PrefsPageGeneralPanel(wxWindow *parent) : PrefsPageGeneralPanelBase(parent)
    {
        // On some platforms (OS X, GNOME), changes to preferences are applied
        // immediately rather than after the OK or Apply button is pressed.
        if ( wxPreferencesEditor::ShouldApplyChangesImmediately() )
        {
            m_splash_screen->Connect(wxEVT_CHECKBOX,
                                   wxCommandEventHandler(PrefsPageGeneralPanel::ChangedUseMarkdown),
                                   NULL, this);
        }
    }
    virtual bool TransferDataToWindow()
    {
        // This is the place where you can initialize values, e.g. from wxConfig.
        // For demonstration purposes, we just set hardcoded values.
        m_splash_screen->SetValue(cfg_show_splash.GetBool(true));
        return true;
    }

    virtual bool TransferDataFromWindow()
    {
        // Called on platforms with modal preferences dialog to save and apply
        // the changes.
        wxCommandEvent dummy;
        ChangedUseMarkdown(dummy);
        ChangedSpellcheck(dummy);
        return true;
    }

private:
    void ChangedUseMarkdown(wxCommandEvent& WXUNUSED(e))
    {
		wxLogDebug("Save config");
		cfg_show_splash = m_splash_screen->GetValue();
        // save new m_useMarkdown value and apply the change to the app
    }

    void ChangedSpellcheck(wxCommandEvent& WXUNUSED(e))
    {
        // save new m_spellcheck value and apply the change to the app
    }
};

class PrefsPageGeneral : public wxStockPreferencesPage
{
public:
    PrefsPageGeneral() : wxStockPreferencesPage(Kind_General) {}
    virtual wxWindow *CreateWindow(wxWindow *parent)
        { return new PrefsPageGeneralPanel(parent); }
};

class PrefsPageTopics : public wxPreferencesPage
{
public:
    virtual wxString GetName() const { return "Topics"; }
    virtual wxBitmap GetLargeIcon() const
        { return wxArtProvider::GetBitmap(wxART_HELP, wxART_TOOLBAR); }
    virtual wxWindow *CreateWindow(wxWindow *parent)
        { return new PrefsPageTopicsPanel(parent); }
};

//}; // END of namespace studio



#endif
/* === E N D =============================================================== */

#endif // __OXYGINE_SCENE_EDITOR_PREFS_H
