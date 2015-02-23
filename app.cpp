#include "app.h"
#include "mainframe.h"
#include "SplashScreen.h"

IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{
	// make sure to call this first
	wxInitAllImageHandlers();

	if ( !wxApp::OnInit() )
        return false;

//Splash screen
    wxBitmap bitmap;
    bitmap.LoadFile( wxString("GD-Splashscreen.png"), wxBITMAP_TYPE_PNG );
    SplashScreen * splash = new SplashScreen(bitmap, 8, 0, -1, wxNO_BORDER | wxFRAME_SHAPED);
	std::cout << "* Splash Screen created" << std::endl;

    wxFrame* frame = new MainFrame(NULL,
                                 wxID_ANY,
                                 wxT("wxAUI Sample Application"),
                                 wxDefaultPosition,
                                 wxSize(800, 600));
	
	//while (!splash->timeUp) {
		sleep(5);
	//}
	splash->Destroy();
    frame->Show();

    return true;
}

