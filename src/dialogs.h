///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 29 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __dialogs__
#define __dialogs__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class PrefsPageGeneralPanelBase
///////////////////////////////////////////////////////////////////////////////
class PrefsPageGeneralPanelBase : public wxPanel 
{
	private:
	
	protected:
		wxCheckBox* m_splash_screen;
		wxCheckBox* m_checkBox2;
		wxCheckBox* m_checkBox3;
	
	public:
		
		PrefsPageGeneralPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL );
		~PrefsPageGeneralPanelBase();
	
};

#endif //__dialogs__
