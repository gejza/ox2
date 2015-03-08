#pragma once

#include <wx/app.h>
#include "prefs.h"
// -- application --

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
	virtual int OnExit();

	virtual void OnInitCmdLine(wxCmdLineParser& parser);
	virtual bool OnCmdLineParsed(wxCmdLineParser& parser);

	void ShowPreferencesEditor(wxWindow* parent);
	void DismissPreferencesEditor();
private:
	wxString m_file2open;
#ifdef USE_PREFS
	wxScopedPtr<wxPreferencesEditor> m_prefEditor;
#endif
};

DECLARE_APP(MyApp)


