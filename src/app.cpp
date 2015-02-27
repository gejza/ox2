#include "app.h"
#include "mainframe.h"
#include <wx/splash.h>
#include <wx/cmdline.h>

IMPLEMENT_APP(MyApp)

void MyApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    wxApp::OnInitCmdLine(parser);
	parser.AddParam("File to open", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL);
//    parser.AddSwitch("v", "verbose",
//                     "run in MDI mode: multiple documents, single window");
//    parser.AddSwitch("", "sdi",
//                     "run in SDI mode: multiple documents, multiple windows");
//    parser.AddSwitch("", "single",
 //                    "run in single document mode");
}

bool MyApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
	if ( !wxApp::OnCmdLineParsed(parser))
		return false;

	if ( parser.GetParamCount() )
		m_file2open = parser.GetParam(0);
  //  int numModeOptions = 0;
   // if ( parser.Found("verbose") )
   // {
        //m_mode = Mode_SDI;
        //numModeOptions++;
    //}
	return true;
}

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
	if (bitmap.LoadFile("res/splash.png", wxBITMAP_TYPE_PNG))
	{
		wxSplashScreen* splash = new wxSplashScreen(bitmap,
			wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
			4000, NULL, wxID_ANY, wxDefaultPosition, wxDefaultSize,
			wxBORDER_SIMPLE|wxSTAY_ON_TOP);
	}
    wxYield();

	wxLogVerbose("Verbose logging enabled!");
	MainFrame* frame = new MainFrame(NULL,
                                 wxID_ANY,
                                 GetAppDisplayName(),
                                 wxDefaultPosition,
                                 wxSize(800, 600));

	/*
    SplashScreen * splash = new SplashScreen(bitmap, 8, 0, -1, wxNO_BORDER | wxFRAME_SHAPED);
	std::cout << "* Splash Screen created" << std::endl;
	*/

	//sleep(3);
    frame->Show(true);

	if (m_file2open != "") {
		frame->OpenFile(m_file2open);
	}
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


