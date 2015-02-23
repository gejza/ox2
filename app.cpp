#include "app.h"
#include "mainframe.h"
#include <wx/splash.h>

IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{
	if ( !wxApp::OnInit() )
        return false;

	// make sure to call this first
	::wxInitAllImageHandlers();

    // Fill in the application information fields before creating wxConfig.
    SetVendorName(wxT("CanBee"));
    SetAppName(wxT("oxygine2d-editor"));
    SetAppDisplayName(wxT("Oxygine Scene editor"));

	wxConfigBase *pConfig = wxConfigBase::Get();
	pConfig->SetRecordDefaults();
	//Splash screen
	wxBitmap bitmap;
	if (bitmap.LoadFile("splash.png", wxBITMAP_TYPE_PNG))
	{
		wxSplashScreen* splash = new wxSplashScreen(bitmap,
			wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
			4000, NULL, wxID_ANY, wxDefaultPosition, wxDefaultSize,
			wxBORDER_SIMPLE|wxSTAY_ON_TOP);
	}
    wxYield();

	wxFrame* frame = new MainFrame(NULL,
                                 wxID_ANY,
                                 GetAppDisplayName(),
                                 wxDefaultPosition,
                                 wxSize(800, 600));

	/*
    SplashScreen * splash = new SplashScreen(bitmap, 8, 0, -1, wxNO_BORDER | wxFRAME_SHAPED);
	std::cout << "* Splash Screen created" << std::endl;
	*/

	sleep(3);
    frame->Show(true);

    return true;
}

int MyApp::OnExit()
{
    // clean up: Set() returns the active config object as Get() does, but unlike
    // Get() it doesn't try to create one if there is none (definitely not what
    // we want here!)
    delete wxConfigBase::Set((wxConfigBase *) NULL);

    return 0;
}


