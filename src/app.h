#pragma once

#include <wx/defs.h>
#include <wx/app.h>
// -- application --
#ifndef wxOVERRIDE
#define wxOVERRIDE
#endif

class MyApp : public wxApp
{
public:
	virtual bool OnInit() wxOVERRIDE;
	virtual int OnExit() wxOVERRIDE;

	virtual void OnInitCmdLine(wxCmdLineParser& parser) wxOVERRIDE;
	virtual bool OnCmdLineParsed(wxCmdLineParser& parser) wxOVERRIDE;
private:
	wxString m_file2open;
};

DECLARE_APP(MyApp)


