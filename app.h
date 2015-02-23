#pragma once

#include <wx/app.h>
// -- application --

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
	virtual int OnExit();

	virtual void OnInitCmdLine(wxCmdLineParser& parser);
	virtual bool OnCmdLineParsed(wxCmdLineParser& parser);
private:
	wxString m_file2open;
};

DECLARE_APP(MyApp)


