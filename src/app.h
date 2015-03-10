#pragma once

#include <wx/app.h>
#include "prefs.h"
// -- application --
#include <ox2/editor/app.h>

class MyApp : public ox2::editor::App
{
public:
    virtual bool OnInit();

	virtual void OnInitCmdLine(wxCmdLineParser& parser);
	virtual bool OnCmdLineParsed(wxCmdLineParser& parser);

	virtual void RecreateGUI();

	void ShowPreferencesEditor(wxWindow* parent);
	void DismissPreferencesEditor();
private:
	wxString m_file2open;
#ifdef USE_PREFS
	wxScopedPtr<wxPreferencesEditor> m_prefEditor;
#endif
};

DECLARE_APP(MyApp)


