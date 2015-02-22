#include "app.h"
#include "mainframe.h"

IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    wxFrame* frame = new MyFrame(NULL,
                                 wxID_ANY,
                                 wxT("wxAUI Sample Application"),
                                 wxDefaultPosition,
                                 wxSize(800, 600));
    frame->Show();

    return true;
}

