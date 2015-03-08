#include "app.h"
#include "mainframe.h"
#include "panels.h"
#include <wx/splash.h>
#include <wx/cmdline.h>
#include <wx/stdpaths.h>
#include <wx/artprov.h>

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

wxLocale* locale;
long language;
 
void initLanguageSupport()
{
    language =  wxLANGUAGE_DEFAULT;
 
    // fake functions, use proper implementation
    //if( userWantsAnotherLanguageThanDefault() )
    //    language = getUsersFavoriteLanguage();
 	language = wxLANGUAGE_CZECH;

    // load language if possible, fall back to english otherwise
    if(wxLocale::IsAvailable(language))
    {
        locale = new wxLocale( language );
 
        #ifdef __WXGTK__
        // add locale search paths
        locale->AddCatalogLookupPathPrefix(wxT("/usr"));
        locale->AddCatalogLookupPathPrefix(wxT("/usr/local"));
        locale->AddCatalogLookupPathPrefix(wxT("/home/gejza/usr"));
        wxStandardPaths* paths = (wxStandardPaths*) &wxStandardPaths::Get();
        wxString prefix = paths->GetInstallPrefix();
		std::cerr << "prefix is " << prefix << std::endl;
        locale->AddCatalogLookupPathPrefix( prefix );
        #endif
 
        locale->AddCatalog(wxT("SceneEditor"));
 
        if(! locale->IsOk() )
        {
            std::cerr << "selected language is wrong" << std::endl;
            delete locale;
            locale = new wxLocale( wxLANGUAGE_ENGLISH );
            language = wxLANGUAGE_ENGLISH;
        }
    }
    else
    {
        std::cout << "The selected language is not supported by your system."
                  << "Try installing support for this language." << std::endl;
        locale = new wxLocale( wxLANGUAGE_ENGLISH );
        language = wxLANGUAGE_ENGLISH;
    }
 
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

	initLanguageSupport();
	wxLog::AddTraceMask(wxTRACE_ResAlloc);

	//cfg_show_splash = true;

	if (cfg_show_splash.GetBool(true)) {
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
	}

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




void MyApp::ShowPreferencesEditor(wxWindow* parent)
{
#ifdef USE_PREFS
    if ( !m_prefEditor )
    {
        m_prefEditor.reset(new wxPreferencesEditor);
        m_prefEditor->AddPage(new PrefsPageGeneral());
        m_prefEditor->AddPage(new PrefsPageTopics());
    }

    m_prefEditor->Show(parent);
#endif
}

void MyApp::DismissPreferencesEditor()
{
#ifdef USE_PREFS
	if ( m_prefEditor )
		m_prefEditor->Dismiss();
#endif
}
