#pragma once

#include <wx/app.h>
// -- application --

class MyApp : public wxApp
{
public:
    bool OnInit();
	int OnExit();
};

DECLARE_APP(MyApp)


