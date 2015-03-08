///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 29 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dialogs.h"

///////////////////////////////////////////////////////////////////////////

PrefsPageGeneralPanelBase::PrefsPageGeneralPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_splash_screen = new wxCheckBox( this, wxID_ANY, _("Show Splash Screen"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_splash_screen, 0, wxALL, 5 );
	
	m_checkBox2 = new wxCheckBox( this, wxID_ANY, _("Check spelling"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_checkBox2, 0, wxALL, 5 );
	
	m_checkBox3 = new wxCheckBox( this, wxID_ANY, _("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_checkBox3, 0, wxALL, 5 );
	
	this->SetSizer( bSizer3 );
	this->Layout();
}

PrefsPageGeneralPanelBase::~PrefsPageGeneralPanelBase()
{
}
