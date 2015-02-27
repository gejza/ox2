#include "app.h"
#include "mainframe.h"
#include <wx/splash.h>
#include <wx/cmdline.h>
#include <wx/docview.h>
#include "scene.h"

IMPLEMENT_APP(MyApp)



// The drawing document (model) class itself
class DrawingDocument : public wxDocument
{
public:
	DrawingDocument() : wxDocument() { }

	DocumentOstream& SaveObject(DocumentOstream& stream) wxOVERRIDE;
	DocumentIstream& LoadObject(DocumentIstream& stream) wxOVERRIDE;

	Scene scene;

private:

	void DoUpdate();

	//DoodleSegments m_doodleSegments;

	wxDECLARE_DYNAMIC_CLASS(DrawingDocument);
};

// The view using MyCanvas to show its contents
class DrawingView : public wxView
{
public:
	DrawingView() : wxView() {}

	virtual bool OnCreate(wxDocument *doc, long flags) wxOVERRIDE;
	virtual void OnDraw(wxDC *dc) wxOVERRIDE;
	virtual void OnUpdate(wxView *sender, wxObject *hint = NULL) wxOVERRIDE;
	virtual bool OnClose(bool deleteWindow = true) wxOVERRIDE;

	DrawingDocument* GetDocument();

private:
	void OnCut(wxCommandEvent& event);

	//MyCanvas *m_canvas;

	wxDECLARE_EVENT_TABLE();
	wxDECLARE_DYNAMIC_CLASS(DrawingView);
};

// ----------------------------------------------------------------------------
// DrawingDocument implementation
// ----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC_CLASS(DrawingDocument, wxDocument)

DocumentOstream& DrawingDocument::SaveObject(DocumentOstream& ostream)
{
#if wxUSE_STD_IOSTREAM
	DocumentOstream& stream = ostream;
#else
	wxTextOutputStream stream(ostream);
#endif

	scene.Save(stream);

	//wxDocument::SaveObject(ostream);

	/*const wxInt32 count = m_doodleSegments.size();
	stream << count << '\n';

	for (int n = 0; n < count; n++)
	{
		m_doodleSegments[n].SaveObject(ostream);
		stream << '\n';
	}*/

	return ostream;
}

DocumentIstream& DrawingDocument::LoadObject(DocumentIstream& istream)
{
#if wxUSE_STD_IOSTREAM
	DocumentIstream& stream = istream;
#else
	wxTextInputStream stream(istream);
#endif

	scene.Load(stream);

	/*wxDocument::LoadObject(istream);

	wxInt32 count = 0;
	stream >> count;
	if (count < 0)
	{
		wxLogWarning("Drawing document corrupted: invalid segments count.");
#if wxUSE_STD_IOSTREAM
		istream.clear(std::ios::badbit);
#else
		istream.Reset(wxSTREAM_READ_ERROR);
#endif
		return istream;
	}

	/*for (int n = 0; n < count; n++)
	{
		DoodleSegment segment;
		segment.LoadObject(istream);
		m_doodleSegments.push_back(segment);
	}*/

	return istream;
}

void DrawingDocument::DoUpdate()
{
	Modify(true);
	UpdateAllViews();
}

// ----------------------------------------------------------------------------
// DrawingView implementation
// ----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC_CLASS(DrawingView, wxView)

wxBEGIN_EVENT_TABLE(DrawingView, wxView)
EVT_MENU(wxID_CUT, DrawingView::OnCut)
wxEND_EVENT_TABLE()

// What to do when a view is created. Creates actual
// windows for displaying the view.
bool DrawingView::OnCreate(wxDocument *doc, long flags)
{
	if (!wxView::OnCreate(doc, flags))
		return false;

	MyApp& app = wxGetApp();
	wxAuiNotebook* nb = CoreTraits::get()->GetNotebook();

	dynamic_cast<DrawingDocument*>(doc)->scene.Create(nb, CoreTraits::get()->GetMainFrame());
	//ctrl->AddPage(scene, wxT("Canvas"), false, page_bmp);
	CoreTraits::get()->GetNotebook()->AddPage(&(dynamic_cast<DrawingDocument*>(doc)->scene), wxT("New scene"), true);
	CoreTraits::get()->GetNotebook()->SetPageToolTip(0, "Welcome to wxAUI (this is a page tooltip)");

	//CoreTraits::get()->GetNotebook()->Thaw();
	/*
		// create a new window and canvas inside it
		wxFrame* frame = app.CreateChildFrame(this, true);
		wxASSERT(frame == GetFrame());
		m_canvas = new MyCanvas(this);
		frame->Show();
*/

	return true;
}

// Sneakily gets used for default print/preview as well as drawing on the
// screen.
void DrawingView::OnDraw(wxDC *dc)
{
	dc->SetPen(*wxBLACK_PEN);

	// simply draw all lines of all segments
	/*const DoodleSegments& segments = GetDocument()->GetSegments();
	for (DoodleSegments::const_iterator i = segments.begin();
		i != segments.end();
		++i)
	{
		const DoodleLines& lines = i->GetLines();
		for (DoodleLines::const_iterator j = lines.begin();
			j != lines.end();
			++j)
		{
			const DoodleLine& line = *j;

			dc->DrawLine(line.x1, line.y1, line.x2, line.y2);
		}
	}*/
}

DrawingDocument* DrawingView::GetDocument()
{
	return wxStaticCast(wxView::GetDocument(), DrawingDocument);
}

void DrawingView::OnUpdate(wxView* sender, wxObject* hint)
{
	wxView::OnUpdate(sender, hint);
	//if (m_canvas)
	//	m_canvas->Refresh();
}

// Clean up windows used for displaying the view.
bool DrawingView::OnClose(bool deleteWindow)
{
	if (!wxView::OnClose(deleteWindow))
		return false;

	Activate(false);

		if (deleteWindow)
		{
			GetFrame()->Destroy();
			SetFrame(NULL);
		}

	return true;
}

void DrawingView::OnCut(wxCommandEvent& WXUNUSED(event))
{
	DrawingDocument * const doc = GetDocument();

	//doc->GetCommandProcessor()->Submit(new DrawingRemoveSegmentCommand(doc));
}

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

	//// Create a document manager
	wxDocManager *docManager = new wxDocManager;

	//// Create a template relating drawing documents to their views
	new wxDocTemplate(docManager, "Drawing", "*.xml", "", "xml",
		"Drawing Doc", "Drawing View",
		CLASSINFO(DrawingDocument), CLASSINFO(DrawingView));
#if defined( __WXMAC__ )  && wxOSX_USE_CARBON
	wxFileName::MacRegisterDefaultTypeAndCreator("drw", 'WXMB', 'WXMA');
#endif
#if 0
	if (m_mode == Mode_Single)
	{
		// If we've only got one window, we only get to edit one document at a
		// time. Therefore no text editing, just doodling.
		docManager->SetMaxDocsOpen(1);
	}
	else // multiple documents mode: allow documents of different types
	{
		// Create a template relating text documents to their views
		new wxDocTemplate(docManager, "Text", "*.txt;*.text", "", "txt;text",
			"Text Doc", "Text View",
			CLASSINFO(TextEditDocument), CLASSINFO(TextEditView));
#if defined( __WXMAC__ ) && wxOSX_USE_CARBON
		wxFileName::MacRegisterDefaultTypeAndCreator("txt", 'TEXT', 'WXMA');
#endif
		// Create a template relating image documents to their views
		new wxDocTemplate(docManager, "Image", "*.png;*.jpg", "", "png;jpg",
			"Image Doc", "Image View",
			CLASSINFO(ImageDocument), CLASSINFO(ImageView));
	}
#endif

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

	docManager->CreateDocument("test/scene.xml", wxDOC_SILENT);
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


