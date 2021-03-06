///////////////////////////////////////////////////////////////////////////////
// Name:        auidemo.cpp
// Purpose:     wxaui: wx advanced user interface - sample/test program
// Author:      Benjamin I. Williams
// Modified by:
// Created:     2005-10-03
// Copyright:   (C) Copyright 2005, Kirix Corporation, All Rights Reserved.
// Licence:     wxWindows Library Licence, Version 3.1
///////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "config.h"

#include "wx/app.h"
#include "wx/spinctrl.h"
#include "wx/artprov.h"
#include "wx/clipbrd.h"
#include "wx/image.h"
#include "wx/colordlg.h"
#include "wx/imaglist.h"
#include "wx/dataobj.h"

#include "wx/bmpbuttn.h"
#include "wx/menu.h"
#include "wx/toolbar.h"
#include "wx/statusbr.h"
#include "wx/msgdlg.h"
#include "wx/textdlg.h"
#include <wx/filehistory.h>
#include <wx/aboutdlg.h>

#include "logo.xpm"

#include "scene.h"
#include "mainframe.h"
#include "panels.h"
#include "resources.h"
#include "app.h"




wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_ERASE_BACKGROUND(MainFrame::OnEraseBackground)
    EVT_SIZE(MainFrame::OnSize)
    EVT_MENU(MainFrame::ID_CreateTree, MainFrame::OnCreateTree)
    EVT_MENU(MainFrame::ID_CreateGrid, MainFrame::OnCreateGrid)
    EVT_MENU(MainFrame::ID_CreateText, MainFrame::OnCreateText)
    EVT_MENU(MainFrame::ID_CreateSizeReport, MainFrame::OnCreateSizeReport)
    EVT_MENU(MainFrame::ID_CreateNotebook, MainFrame::OnCreateNotebook)
    EVT_MENU(MainFrame::ID_CreatePerspective, MainFrame::OnCreatePerspective)
    EVT_MENU(MainFrame::ID_CopyPerspectiveCode, MainFrame::OnCopyPerspectiveCode)
    EVT_MENU(ID_AllowFloating, MainFrame::OnManagerFlag)
    EVT_MENU(ID_TransparentHint, MainFrame::OnManagerFlag)
    EVT_MENU(ID_VenetianBlindsHint, MainFrame::OnManagerFlag)
    EVT_MENU(ID_RectangleHint, MainFrame::OnManagerFlag)
    EVT_MENU(ID_NoHint, MainFrame::OnManagerFlag)
    EVT_MENU(ID_HintFade, MainFrame::OnManagerFlag)
    EVT_MENU(ID_NoVenetianFade, MainFrame::OnManagerFlag)
    EVT_MENU(ID_TransparentDrag, MainFrame::OnManagerFlag)
    EVT_MENU(ID_LiveUpdate, MainFrame::OnManagerFlag)
    EVT_MENU(ID_AllowActivePane, MainFrame::OnManagerFlag)
    /*EVT_MENU(ID_NotebookTabFixedWidth, MainFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookNoCloseButton, MainFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookCloseButton, MainFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookCloseButtonAll, MainFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookCloseButtonActive, MainFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookAllowTabMove, MainFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookAllowTabExternalMove, MainFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookAllowTabSplit, MainFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookScrollButtons, MainFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookWindowList, MainFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookArtGloss, MainFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookArtSimple, MainFrame::OnNotebookFlag)*/
    EVT_MENU(ID_NotebookAlignTop,     MainFrame::OnTabAlignment)
    EVT_MENU(ID_NotebookAlignBottom,  MainFrame::OnTabAlignment)
    EVT_MENU(ID_NoGradient, MainFrame::OnGradient)
    EVT_MENU(ID_VerticalGradient, MainFrame::OnGradient)
    EVT_MENU(ID_HorizontalGradient, MainFrame::OnGradient)
    EVT_MENU(ID_AllowToolbarResizing, MainFrame::OnToolbarResizing)
    EVT_MENU(ID_Settings, MainFrame::OnSettings)
    EVT_MENU(ID_CustomizeToolbar, MainFrame::OnCustomizeToolbar)
    EVT_MENU(wxID_NEW, MainFrame::OnNew)
    EVT_MENU(wxID_OPEN, MainFrame::OnOpen)
	EVT_MENU_RANGE(wxID_FILE1, wxID_FILE9, MainFrame::OnRecentFile)
    EVT_MENU(wxID_EXIT, MainFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
    EVT_MENU(wxID_UNDO, MainFrame::OnUndo)
    EVT_MENU(wxID_REDO, MainFrame::OnRedo)
	EVT_MENU(wxID_PREFERENCES, MainFrame::OnPref)
    EVT_UPDATE_UI(ID_NotebookTabFixedWidth, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookNoCloseButton, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookCloseButton, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookCloseButtonAll, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookCloseButtonActive, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookAllowTabMove, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookAllowTabExternalMove, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookAllowTabSplit, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookScrollButtons, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookWindowList, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_AllowFloating, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_TransparentHint, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_VenetianBlindsHint, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_RectangleHint, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NoHint, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_HintFade, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NoVenetianFade, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_TransparentDrag, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_LiveUpdate, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NoGradient, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_VerticalGradient, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_HorizontalGradient, MainFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_AllowToolbarResizing, MainFrame::OnUpdateUI)
    EVT_MENU_RANGE(MainFrame::ID_FirstPerspective, MainFrame::ID_FirstPerspective+1000,
                   MainFrame::OnRestorePerspective)
    EVT_AUITOOLBAR_TOOL_DROPDOWN(ID_DropDownToolbarItem, MainFrame::OnDropDownToolbarItem)
    EVT_AUI_PANE_CLOSE(MainFrame::OnPaneClose)
    EVT_AUINOTEBOOK_ALLOW_DND(wxID_ANY, MainFrame::OnAllowNotebookDnD)
    EVT_AUINOTEBOOK_PAGE_CLOSE(wxID_ANY, MainFrame::OnNotebookPageClose)
    EVT_AUINOTEBOOK_PAGE_CLOSED(wxID_ANY, MainFrame::OnNotebookPageClosed)
	EVT_AUINOTEBOOK_PAGE_CHANGED(wxID_ANY, MainFrame::OnNotebookPageChanged)
    EVT_COMMAND_SCROLL_CHANGED(ID_Slider, MainFrame::OnSlider)
	EVT_TREE_SEL_CHANGED(CoreTraits::ID_TreeCtrl, MainFrame::OnTreeItemChanged)
wxEND_EVENT_TABLE()


MainFrame::MainFrame(wxWindow* parent,
                 wxWindowID id,
                 const wxString& title,
                 const wxPoint& pos,
                 const wxSize& size,
                 long style)
        : wxFrame(parent, id, title, pos, size, style)
{
	CoreTraits::get(this);

    // tell wxAuiManager to manage this frame
    m_mgr.SetManagedWindow(this);

    // set frame icon
    SetIcon(wxICON(logo));

    SetMenuBar(this->CreateMenuBar());

    CreateStatusBar();
	wxStatusBar * status = GetStatusBar();
	status->SetFieldsCount(StatusBarField_Count);
	int status_widths[StatusBarField_Count] = { -1, -1, -1 };
	status_widths[StatusBarField_Text] = -2;
	status_widths[StatusBarField_Zoom] = 50;
	status->SetStatusWidths(StatusBarField_Count, status_widths);
	wxRect rect;
	status->GetFieldRect(StatusBarField_Slider, rect);
	m_slider = new wxSlider(GetStatusBar(), ID_Slider, 100, 10, 200,
		                             rect.GetTopLeft(), rect.GetSize(),
									 /*wxSL_VALUE_LABEL|*/wxSL_AUTOTICKS | wxSL_HORIZONTAL);
	m_slider->SetTickFreq(20);
    GetStatusBar()->SetStatusText(_("Ready"), StatusBarField_Text);
    GetStatusBar()->SetStatusText(_("100%"), StatusBarField_Zoom);


    // min size for the frame itself isn't completely done.
    // see the end up wxAuiManager::Update() for the test
    // code. For now, just hard code a frame minimum size
    SetMinSize(wxSize(400,300));

	wxConfigBase *pConfig = wxConfigBase::Get();
	// restore frame position and size
  	int x = pConfig->Read(_T("/MainFrame/x"), 50),
      	y = pConfig->Read(_T("/MainFrame/y"), 50),
      	w = pConfig->Read(_T("/MainFrame/w"), 350),
      	h = pConfig->Read(_T("/MainFrame/h"), 200);
  	Move(x, y);
  	SetClientSize(w, h);




    // prepare a few custom overflow elements for the toolbars' overflow buttons

    wxAuiToolBarItemArray prepend_items;
    wxAuiToolBarItemArray append_items;
    wxAuiToolBarItem item;
    item.SetKind(wxITEM_SEPARATOR);
    append_items.Add(item);
    item.SetKind(wxITEM_NORMAL);
    item.SetId(ID_CustomizeToolbar);
    item.SetLabel(_("Customize..."));
    append_items.Add(item);


    // create some toolbars
    wxAuiToolBar* tb1 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                         wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW);
    tb1->SetToolBitmapSize(wxSize(48,48));
    tb1->AddTool(ID_SampleItem+1, wxT("Test"), wxArtProvider::GetBitmap(wxART_ERROR));
    tb1->AddSeparator();
    tb1->AddTool(ID_SampleItem+2, wxT("Test"), wxArtProvider::GetBitmap(wxART_QUESTION));
    tb1->AddTool(ID_SampleItem+3, wxT("Test"), wxArtProvider::GetBitmap(wxART_INFORMATION));
    tb1->AddTool(ID_SampleItem+4, wxT("Test"), wxArtProvider::GetBitmap(wxART_WARNING));
    tb1->AddTool(ID_SampleItem+5, wxT("Test"), wxArtProvider::GetBitmap(wxART_MISSING_IMAGE));
    tb1->SetCustomOverflowItems(prepend_items, append_items);
    tb1->Realize();


    wxAuiToolBar* tb2 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                         wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW | wxAUI_TB_HORIZONTAL);
    tb2->SetToolBitmapSize(wxSize(16,16));

    wxBitmap tb2_bmp1 = wxArtProvider::GetBitmap(wxART_QUESTION, wxART_OTHER, wxSize(16,16));
    tb2->AddTool(ID_SampleItem+6, wxT("Disabled"), tb2_bmp1);
    tb2->AddTool(ID_SampleItem+7, wxT("Test"), tb2_bmp1);
    tb2->AddTool(ID_SampleItem+8, wxT("Test"), tb2_bmp1);
    tb2->AddTool(ID_SampleItem+9, wxT("Test"), tb2_bmp1);
    tb2->AddSeparator();
    tb2->AddTool(ID_SampleItem+10, wxT("Test"), tb2_bmp1);
    tb2->AddTool(ID_SampleItem+11, wxT("Test"), tb2_bmp1);
    tb2->AddSeparator();
    tb2->AddTool(ID_SampleItem+12, wxT("Test"), tb2_bmp1);
    tb2->AddTool(ID_SampleItem+13, wxT("Test"), tb2_bmp1);
    tb2->AddTool(ID_SampleItem+14, wxT("Test"), tb2_bmp1);
    tb2->AddTool(ID_SampleItem+15, wxT("Test"), tb2_bmp1);
    tb2->SetCustomOverflowItems(prepend_items, append_items);
    tb2->EnableTool(ID_SampleItem+6, false);
    tb2->Realize();


    wxAuiToolBar* tb3 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                         wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW);
    tb3->SetToolBitmapSize(wxSize(16,16));
    wxBitmap tb3_bmp1 = wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16,16));
    tb3->AddTool(ID_SampleItem+16, wxT("Check 1"), tb3_bmp1, wxT("Check 1"), wxITEM_CHECK);
    tb3->AddTool(ID_SampleItem+17, wxT("Check 2"), tb3_bmp1, wxT("Check 2"), wxITEM_CHECK);
    tb3->AddTool(ID_SampleItem+18, wxT("Check 3"), tb3_bmp1, wxT("Check 3"), wxITEM_CHECK);
    tb3->AddTool(ID_SampleItem+19, wxT("Check 4"), tb3_bmp1, wxT("Check 4"), wxITEM_CHECK);
    tb3->AddSeparator();
    tb3->AddTool(ID_SampleItem+20, wxT("Radio 1"), tb3_bmp1, wxT("Radio 1"), wxITEM_RADIO);
    tb3->AddTool(ID_SampleItem+21, wxT("Radio 2"), tb3_bmp1, wxT("Radio 2"), wxITEM_RADIO);
    tb3->AddTool(ID_SampleItem+22, wxT("Radio 3"), tb3_bmp1, wxT("Radio 3"), wxITEM_RADIO);
    tb3->AddSeparator();
    tb3->AddTool(ID_SampleItem+23, wxT("Radio 1 (Group 2)"), tb3_bmp1, wxT("Radio 1 (Group 2)"), wxITEM_RADIO);
    tb3->AddTool(ID_SampleItem+24, wxT("Radio 2 (Group 2)"), tb3_bmp1, wxT("Radio 2 (Group 2)"), wxITEM_RADIO);
    tb3->AddTool(ID_SampleItem+25, wxT("Radio 3 (Group 2)"), tb3_bmp1, wxT("Radio 3 (Group 2)"), wxITEM_RADIO);
    tb3->SetCustomOverflowItems(prepend_items, append_items);
    tb3->Realize();


    wxAuiToolBar* tb4 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                         wxAUI_TB_DEFAULT_STYLE |
                                         wxAUI_TB_OVERFLOW |
                                         wxAUI_TB_TEXT |
                                         wxAUI_TB_HORZ_TEXT);
    tb4->SetToolBitmapSize(wxSize(16,16));
    wxBitmap tb4_bmp1 = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16));
    tb4->AddTool(ID_DropDownToolbarItem, wxT("Item 1"), tb4_bmp1);
    tb4->AddTool(ID_SampleItem+23, wxT("Item 2"), tb4_bmp1);
    tb4->AddTool(ID_SampleItem+24, wxT("Item 3"), tb4_bmp1);
    tb4->AddTool(ID_SampleItem+25, wxT("Item 4"), tb4_bmp1);
    tb4->AddSeparator();
    tb4->AddTool(ID_SampleItem+26, wxT("Item 5"), tb4_bmp1);
    tb4->AddTool(ID_SampleItem+27, wxT("Item 6"), tb4_bmp1);
    tb4->AddTool(ID_SampleItem+28, wxT("Item 7"), tb4_bmp1);
    tb4->AddTool(ID_SampleItem+29, wxT("Item 8"), tb4_bmp1);
    tb4->SetToolDropDown(ID_DropDownToolbarItem, true);
    tb4->SetCustomOverflowItems(prepend_items, append_items);
    wxChoice* choice = new wxChoice(tb4, ID_SampleItem+35);
    choice->AppendString(wxT("One choice"));
    choice->AppendString(wxT("Another choice"));
    tb4->AddControl(choice);
    tb4->Realize();


    wxAuiToolBar* tb5 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                         wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW | wxAUI_TB_VERTICAL);
    tb5->SetToolBitmapSize(wxSize(48,48));
    tb5->AddTool(ID_SampleItem+30, wxT("Test"), wxArtProvider::GetBitmap(wxART_ERROR));
    tb5->AddSeparator();
    tb5->AddTool(ID_SampleItem+31, wxT("Test"), wxArtProvider::GetBitmap(wxART_QUESTION));
    tb5->AddTool(ID_SampleItem+32, wxT("Test"), wxArtProvider::GetBitmap(wxART_INFORMATION));
    tb5->AddTool(ID_SampleItem+33, wxT("Test"), wxArtProvider::GetBitmap(wxART_WARNING));
    tb5->AddTool(ID_SampleItem+34, wxT("Test"), wxArtProvider::GetBitmap(wxART_MISSING_IMAGE));
    tb5->SetCustomOverflowItems(prepend_items, append_items);
    tb5->Realize();

    // add a bunch of panes
    //m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
    //              Name(wxT("test1")).Caption(wxT("Pane Caption")).
    //              Top());

    //m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
    //              Name(wxT("test2")).Caption(wxT("Client Size Reporter")).
    //              Bottom().Position(1).
    //              CloseButton(true).MaximizeButton(true));

    //m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
    //              Name(wxT("test3")).Caption(wxT("Client Size Reporter")).
    //              Bottom().
    //              CloseButton(true).MaximizeButton(true));

    //m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
    //              Name(wxT("test4")).Caption(wxT("Pane Caption")).
    //              Left());

    //m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
    //              Name(wxT("test5")).Caption(wxT("No Close Button")).
    //              Right().CloseButton(false));



    //m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
    //              Name(wxT("test6")).Caption(wxT("Client Size Reporter")).
    //              Right().Row(1).
    //              CloseButton(true).MaximizeButton(true));

    //m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
    //              Name(wxT("test7")).Caption(wxT("Client Size Reporter")).
    //              Left().Layer(1).
    //              CloseButton(true).MaximizeButton(true));

    m_mgr.AddPane(CoreTraits::get(this)->GetTreeCtrl(), wxAuiPaneInfo().
                  Name(wxT("test8")).Caption(wxT("Tree Pane")).
                  Left().Layer(1).Position(1).
                  CloseButton(true).MinimizeButton(true));
    m_mgr.AddPane(CoreTraits::get(this)->GetPropGrid(), wxAuiPaneInfo().
                  Name(wxT("properties")).Caption(_("Properties")).
				  Left().Layer(1).Position(2).
				  CloseButton(true).MinimizeButton(true));

	ResourceView* res = new ResourceView(this);
	m_mgr.AddPane(res, wxAuiPaneInfo().
		Name(wxT("resources")).Caption(wxT("Resources")).
		Right().Row(1).
		CloseButton(true).MaximizeButton(true));

	res->Load("../laser/data/resources.xml");
    //m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
    //              Name(wxT("test9")).Caption(wxT("Min Size 200x100")).
    //              BestSize(wxSize(200,100)).MinSize(wxSize(200,100)).
    //              Bottom().Layer(1).
    //              CloseButton(true).MaximizeButton(true));

    wxWindow* wnd10 = CreateTextCtrl(wxT("This pane will prompt the user before hiding."));

    // Give this pane an icon, too, just for testing.
    int iconSize = m_mgr.GetArtProvider()->GetMetric(wxAUI_DOCKART_CAPTION_SIZE);

    // Make it even to use 16 pixel icons with default 17 caption height.
    iconSize &= ~1;

    m_mgr.AddPane(wnd10, wxAuiPaneInfo().
                  Name(wxT("test10")).Caption(wxT("Text Pane with Hide Prompt")).
                  Bottom().Layer(1).Position(1).
                  Icon(wxArtProvider::GetBitmap(wxART_WARNING,
                                                wxART_OTHER,
                                                wxSize(iconSize, iconSize))));

    m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
                  Name(wxT("test11")).Caption(wxT("Fixed Pane")).
                  Bottom().Layer(1).Position(2).Fixed());


    m_mgr.AddPane(new SettingsPanel(this,this), wxAuiPaneInfo().
                  Name(wxT("settings")).Caption(wxT("Dock Manager Settings")).
                  Dockable(false).Float().Hide());

    // create some center panes
    m_mgr.AddPane(CoreTraits::get(this)->GetNotebook(), wxAuiPaneInfo().Name(wxT("notebook_content")).
                  CenterPane().PaneBorder(false));

    // add the toolbars to the manager
    m_mgr.AddPane(tb1, wxAuiPaneInfo().
                  Name(wxT("tb1")).Caption(wxT("Big Toolbar")).
                  ToolbarPane().Top());

    m_mgr.AddPane(tb2, wxAuiPaneInfo().
                  Name(wxT("tb2")).Caption(wxT("Toolbar 2 (Horizontal)")).
                  ToolbarPane().Top().Row(1));

    m_mgr.AddPane(tb3, wxAuiPaneInfo().
                  Name(wxT("tb3")).Caption(wxT("Toolbar 3")).
                  ToolbarPane().Top().Row(1).Position(1));

    m_mgr.AddPane(tb4, wxAuiPaneInfo().
                  Name(wxT("tb4")).Caption(wxT("Sample Bookmark Toolbar")).
                  ToolbarPane().Top().Row(2));

    m_mgr.AddPane(tb5, wxAuiPaneInfo().
                  Name(wxT("tb5")).Caption(wxT("Sample Vertical Toolbar")).
                  ToolbarPane().Left().
                  GripperTop());

    m_mgr.AddPane(new wxButton(this, wxID_ANY, _("Test Button")),
                  wxAuiPaneInfo().Name(wxT("tb6")).
                  ToolbarPane().Top().Row(2).Position(1).
                  LeftDockable(false).RightDockable(false));

    // make some default perspectives

    wxString perspective_all = m_mgr.SavePerspective();

    int i, count;
    wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
    for (i = 0, count = all_panes.GetCount(); i < count; ++i)
        if (!all_panes.Item(i).IsToolbar())
            all_panes.Item(i).Hide();
    m_mgr.GetPane(wxT("tb1")).Hide();
    m_mgr.GetPane(wxT("tb6")).Hide();
    m_mgr.GetPane(wxT("test8")).Show().Left().Layer(0).Row(0).Position(0);
    m_mgr.GetPane(wxT("test10")).Show().Bottom().Layer(0).Row(0).Position(0);
    m_mgr.GetPane(wxT("notebook_content")).Show();
    wxString perspective_default = m_mgr.SavePerspective();

    m_perspectives.Add(perspective_default);
    m_perspectives.Add(perspective_all);


   Scene* scene = new Scene(CoreTraits::get(this)->GetNotebook(), this);
   
   //ctrl->AddPage(scene, wxT("Canvas"), false, page_bmp);
   CoreTraits::get(this)->GetNotebook()->AddPage(scene, wxT("New scene"), true);
   CoreTraits::get(this)->GetNotebook()->SetPageToolTip(0, "Welcome to wxAUI (this is a page tooltip)");

   CoreTraits::get(this)->GetNotebook()->Thaw();
   


	mFileHistory = new wxFileHistory(10);
	mFileHistory->UseMenu(m_recent_menu);
	mFileHistory->AddFilesToMenu(m_recent_menu);
	
	pConfig->SetPath(_T("/History"));
	mFileHistory->Load(*pConfig);

    // "commit" all changes made to wxAuiManager
    m_mgr.Update();
	CoreTraits::get(this)->SetActiveScene(scene);
	UpdateControls();

	m_mgr.LoadPerspective(pConfig->Read(_T("/MainFrame/Perspective"), perspective_default));
}


MainFrame::~MainFrame()
{
	wxConfigBase *pConfig = wxConfigBase::Get();
  	if ( pConfig == NULL )
    	return;

	pConfig->SetPath(_T("/History"));
	mFileHistory->Save(*pConfig);

  // save the frame position
  int x, y, w, h;
  GetClientSize(&w, &h);
  GetPosition(&x, &y);
  pConfig->Write(_T("/MainFrame/x"), (long) x);
  pConfig->Write(_T("/MainFrame/y"), (long) y);
  pConfig->Write(_T("/MainFrame/w"), (long) w);
  pConfig->Write(_T("/MainFrame/h"), (long) h);

  wxString s = m_mgr.SavePerspective();
  pConfig->Write(_T("/MainFrame/Perspective"), s);

    m_mgr.UnInit();
}

wxMenuBar* MainFrame::CreateMenuBar()
{

	// create menu
	wxMenuBar* mb = new wxMenuBar;

	wxMenu* file_menu = new wxMenu;
	file_menu->Append(wxID_NEW);
	file_menu->Append(wxID_OPEN);
	m_recent_menu = new wxMenu;
	file_menu->AppendSubMenu(m_recent_menu, _T("Open Recent"));
	file_menu->AppendSeparator();
	file_menu->Append(wxID_SAVE);
	file_menu->Append(wxID_SAVEAS);
	file_menu->AppendSeparator();
	file_menu->Append(wxID_EXIT);


	wxMenu* edit_menu = new wxMenu;
	/*m_undo = */edit_menu->Append(wxID_UNDO);
	/*m_redo = */edit_menu->Append(wxID_REDO);
	edit_menu->AppendSeparator();
	edit_menu->Append(wxID_PREFERENCES);
	CoreTraits::get()->GetCmds()->SetEditMenu(edit_menu);

	wxMenu* view_menu = new wxMenu;
	view_menu->AppendSeparator();
	view_menu->Append(ID_CreateText, _("Create Text Control"));
	view_menu->Append(ID_CreateTree, _("Create Tree"));
	view_menu->Append(ID_CreateGrid, _("Create Grid"));
	view_menu->Append(ID_CreateNotebook, _("Create Notebook"));
	view_menu->Append(ID_CreateSizeReport, _("Create Size Reporter"));
	view_menu->AppendSeparator();
	view_menu->Append(ID_GridContent, _("Use a Grid for the Content Pane"));
	view_menu->Append(ID_TextContent, _("Use a Text Control for the Content Pane"));
	view_menu->Append(ID_HTMLContent, _("Use an HTML Control for the Content Pane"));
	view_menu->Append(ID_TreeContent, _("Use a Tree Control for the Content Pane"));
	view_menu->Append(ID_NotebookContent, _("Use a wxAuiNotebook control for the Content Pane"));
	view_menu->Append(ID_SizeReportContent, _("Use a Size Reporter for the Content Pane"));

	wxMenu* options_menu = new wxMenu;
	options_menu->AppendRadioItem(ID_TransparentHint, _("Transparent Hint"));
	options_menu->AppendRadioItem(ID_VenetianBlindsHint, _("Venetian Blinds Hint"));
	options_menu->AppendRadioItem(ID_RectangleHint, _("Rectangle Hint"));
	options_menu->AppendRadioItem(ID_NoHint, _("No Hint"));
	options_menu->AppendSeparator();
	options_menu->AppendCheckItem(ID_HintFade, _("Hint Fade-in"));
	options_menu->AppendCheckItem(ID_AllowFloating, _("Allow Floating"));
	options_menu->AppendCheckItem(ID_NoVenetianFade, _("Disable Venetian Blinds Hint Fade-in"));
	options_menu->AppendCheckItem(ID_TransparentDrag, _("Transparent Drag"));
	options_menu->AppendCheckItem(ID_AllowActivePane, _("Allow Active Pane"));
	options_menu->AppendCheckItem(ID_LiveUpdate, _("Live Resize Update"));
	options_menu->AppendSeparator();
	options_menu->AppendRadioItem(ID_NoGradient, _("No Caption Gradient"));
	options_menu->AppendRadioItem(ID_VerticalGradient, _("Vertical Caption Gradient"));
	options_menu->AppendRadioItem(ID_HorizontalGradient, _("Horizontal Caption Gradient"));
	options_menu->AppendSeparator();
	options_menu->AppendCheckItem(ID_AllowToolbarResizing, _("Allow Toolbar Resizing"));
	options_menu->AppendSeparator();
	options_menu->Append(ID_Settings, _("Settings Pane"));

	wxMenu* notebook_menu = new wxMenu;
	notebook_menu->AppendRadioItem(ID_NotebookArtGloss, _("Glossy Theme (Default)"));
	notebook_menu->AppendRadioItem(ID_NotebookArtSimple, _("Simple Theme"));
	notebook_menu->AppendSeparator();
	notebook_menu->AppendRadioItem(ID_NotebookNoCloseButton, _("No Close Button"));
	notebook_menu->AppendRadioItem(ID_NotebookCloseButton, _("Close Button at Right"));
	notebook_menu->AppendRadioItem(ID_NotebookCloseButtonAll, _("Close Button on All Tabs"));
	notebook_menu->AppendRadioItem(ID_NotebookCloseButtonActive, _("Close Button on Active Tab"));
	notebook_menu->AppendSeparator();
	notebook_menu->AppendRadioItem(ID_NotebookAlignTop, _("Tab Top Alignment"));
	notebook_menu->AppendRadioItem(ID_NotebookAlignBottom, _("Tab Bottom Alignment"));
	notebook_menu->AppendSeparator();
	notebook_menu->AppendCheckItem(ID_NotebookAllowTabMove, _("Allow Tab Move"));
	notebook_menu->AppendCheckItem(ID_NotebookAllowTabExternalMove, _("Allow External Tab Move"));
	notebook_menu->AppendCheckItem(ID_NotebookAllowTabSplit, _("Allow Notebook Split"));
	notebook_menu->AppendCheckItem(ID_NotebookScrollButtons, _("Scroll Buttons Visible"));
	notebook_menu->AppendCheckItem(ID_NotebookWindowList, _("Window List Button Visible"));
	notebook_menu->AppendCheckItem(ID_NotebookTabFixedWidth, _("Fixed-width Tabs"));

	m_perspectives_menu = new wxMenu;
	m_perspectives_menu->Append(ID_CreatePerspective, _("Create Perspective"));
	m_perspectives_menu->Append(ID_CopyPerspectiveCode, _("Copy Perspective Data To Clipboard"));
	m_perspectives_menu->AppendSeparator();
	m_perspectives_menu->Append(ID_FirstPerspective + 0, _("Default Startup"));
	m_perspectives_menu->Append(ID_FirstPerspective + 1, _("All Panes"));

	wxMenu* help_menu = new wxMenu;
	help_menu->Append(wxID_ABOUT);

	mb->Append(file_menu, _("&File"));
	mb->Append(edit_menu, _("&Edit"));
	mb->Append(view_menu, _("&View"));
	mb->Append(m_perspectives_menu, _("&Perspectives"));
	mb->Append(options_menu, _("&Options"));
	mb->Append(notebook_menu, _("&Notebook"));
	mb->Append(help_menu, _("&Help"));

	return mb;
}

wxAuiDockArt* MainFrame::GetDockArt()
{
    return m_mgr.GetArtProvider();
}

void MainFrame::DoUpdate()
{
    m_mgr.Update();
}

void MainFrame::OnEraseBackground(wxEraseEvent& event)
{
    event.Skip();
}

void MainFrame::OnSize(wxSizeEvent& event)
{
    //event.Skip();
	wxStatusBar * status = GetStatusBar();
	if (status) {
		wxRect rect;
		status->GetFieldRect(StatusBarField_Slider, rect);
		rect.SetWidth(rect.GetWidth() - 5);
		m_slider->SetPosition(rect.GetTopLeft());
		m_slider->SetSize(rect.GetSize());
	}
}

void MainFrame::OnSettings(wxCommandEvent& WXUNUSED(evt))
{
    // show the settings pane, and float it
    wxAuiPaneInfo& floating_pane = m_mgr.GetPane(wxT("settings")).Float().Show();

    if (floating_pane.floating_pos == wxDefaultPosition)
        floating_pane.FloatingPosition(GetStartPosition());

    m_mgr.Update();
}

void MainFrame::OnCustomizeToolbar(wxCommandEvent& WXUNUSED(evt))
{
    wxMessageBox(_("Customize Toolbar clicked"));
}

void MainFrame::OnGradient(wxCommandEvent& event)
{
    int gradient = 0;

    switch (event.GetId())
    {
        case ID_NoGradient:         gradient = wxAUI_GRADIENT_NONE; break;
        case ID_VerticalGradient:   gradient = wxAUI_GRADIENT_VERTICAL; break;
        case ID_HorizontalGradient: gradient = wxAUI_GRADIENT_HORIZONTAL; break;
    }

    m_mgr.GetArtProvider()->SetMetric(wxAUI_DOCKART_GRADIENT_TYPE, gradient);
    m_mgr.Update();
}

void MainFrame::OnToolbarResizing(wxCommandEvent& WXUNUSED(evt))
{
    wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
    const size_t count = all_panes.GetCount();
    for (size_t i = 0; i < count; ++i)
    {
        wxAuiToolBar* toolbar = wxDynamicCast(all_panes[i].window, wxAuiToolBar);
        if (toolbar)
        {
            all_panes[i].Resizable(!all_panes[i].IsResizable());
        }
    }

    m_mgr.Update();
}

void MainFrame::OnManagerFlag(wxCommandEvent& event)
{
    unsigned int flag = 0;

#if !defined(__WXMSW__) && !defined(__WXMAC__) && !defined(__WXGTK__)
    if (event.GetId() == ID_TransparentDrag ||
        event.GetId() == ID_TransparentHint ||
        event.GetId() == ID_HintFade)
    {
        wxMessageBox(wxT("This option is presently only available on wxGTK, wxMSW and wxMac"));
        return;
    }
#endif

    int id = event.GetId();

    if (id == ID_TransparentHint ||
        id == ID_VenetianBlindsHint ||
        id == ID_RectangleHint ||
        id == ID_NoHint)
    {
        unsigned int flags = m_mgr.GetFlags();
        flags &= ~wxAUI_MGR_TRANSPARENT_HINT;
        flags &= ~wxAUI_MGR_VENETIAN_BLINDS_HINT;
        flags &= ~wxAUI_MGR_RECTANGLE_HINT;
        m_mgr.SetFlags(flags);
    }

    switch (id)
    {
        case ID_AllowFloating: flag = wxAUI_MGR_ALLOW_FLOATING; break;
        case ID_TransparentDrag: flag = wxAUI_MGR_TRANSPARENT_DRAG; break;
        case ID_HintFade: flag = wxAUI_MGR_HINT_FADE; break;
        case ID_NoVenetianFade: flag = wxAUI_MGR_NO_VENETIAN_BLINDS_FADE; break;
        case ID_AllowActivePane: flag = wxAUI_MGR_ALLOW_ACTIVE_PANE; break;
        case ID_TransparentHint: flag = wxAUI_MGR_TRANSPARENT_HINT; break;
        case ID_VenetianBlindsHint: flag = wxAUI_MGR_VENETIAN_BLINDS_HINT; break;
        case ID_RectangleHint: flag = wxAUI_MGR_RECTANGLE_HINT; break;
        case ID_LiveUpdate: flag = wxAUI_MGR_LIVE_RESIZE; break;
    }

    if (flag)
    {
        m_mgr.SetFlags(m_mgr.GetFlags() ^ flag);
    }

    m_mgr.Update();
}


/*void MainFrame::OnNotebookFlag(wxCommandEvent& event)
{
    int id = event.GetId();

    if (id == ID_NotebookNoCloseButton ||
        id == ID_NotebookCloseButton ||
        id == ID_NotebookCloseButtonAll ||
        id == ID_NotebookCloseButtonActive)
    {
        m_notebook_style &= ~(wxAUI_NB_CLOSE_BUTTON |
                              wxAUI_NB_CLOSE_ON_ACTIVE_TAB |
                              wxAUI_NB_CLOSE_ON_ALL_TABS);

        switch (id)
        {
            case ID_NotebookNoCloseButton: break;
            case ID_NotebookCloseButton: m_notebook_style |= wxAUI_NB_CLOSE_BUTTON; break;
            case ID_NotebookCloseButtonAll: m_notebook_style |= wxAUI_NB_CLOSE_ON_ALL_TABS; break;
            case ID_NotebookCloseButtonActive: m_notebook_style |= wxAUI_NB_CLOSE_ON_ACTIVE_TAB; break;
        }
    }

    if (id == ID_NotebookAllowTabMove)
    {
        m_notebook_style ^= wxAUI_NB_TAB_MOVE;
    }
    if (id == ID_NotebookAllowTabExternalMove)
    {
        m_notebook_style ^= wxAUI_NB_TAB_EXTERNAL_MOVE;
    }
     else if (id == ID_NotebookAllowTabSplit)
    {
        m_notebook_style ^= wxAUI_NB_TAB_SPLIT;
    }
     else if (id == ID_NotebookWindowList)
    {
        m_notebook_style ^= wxAUI_NB_WINDOWLIST_BUTTON;
    }
     else if (id == ID_NotebookScrollButtons)
    {
        m_notebook_style ^= wxAUI_NB_SCROLL_BUTTONS;
    }
     else if (id == ID_NotebookTabFixedWidth)
    {
        m_notebook_style ^= wxAUI_NB_TAB_FIXED_WIDTH;
    }


    size_t i, count;
    wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
    for (i = 0, count = all_panes.GetCount(); i < count; ++i)
    {
        wxAuiPaneInfo& pane = all_panes.Item(i);
        if (pane.window->IsKindOf(CLASSINFO(wxAuiNotebook)))
        {
            wxAuiNotebook* nb = (wxAuiNotebook*)pane.window;

            if (id == ID_NotebookArtGloss)
            {
                nb->SetArtProvider(new wxAuiDefaultTabArt);
                m_notebook_theme = 0;
            }
             else if (id == ID_NotebookArtSimple)
            {
                nb->SetArtProvider(new wxAuiSimpleTabArt);
                m_notebook_theme = 1;
            }


            nb->SetWindowStyleFlag(m_notebook_style);
            nb->Refresh();
        }
    }


}*/


void MainFrame::OnUpdateUI(wxUpdateUIEvent& event)
{
    unsigned int flags = m_mgr.GetFlags();

    switch (event.GetId())
    {
        case ID_NoGradient:
            event.Check(m_mgr.GetArtProvider()->GetMetric(wxAUI_DOCKART_GRADIENT_TYPE) == wxAUI_GRADIENT_NONE);
            break;
        case ID_VerticalGradient:
            event.Check(m_mgr.GetArtProvider()->GetMetric(wxAUI_DOCKART_GRADIENT_TYPE) == wxAUI_GRADIENT_VERTICAL);
            break;
        case ID_HorizontalGradient:
            event.Check(m_mgr.GetArtProvider()->GetMetric(wxAUI_DOCKART_GRADIENT_TYPE) == wxAUI_GRADIENT_HORIZONTAL);
            break;
        case ID_AllowToolbarResizing:
        {
            wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
            const size_t count = all_panes.GetCount();
            for (size_t i = 0; i < count; ++i)
            {
                wxAuiToolBar* toolbar = wxDynamicCast(all_panes[i].window, wxAuiToolBar);
                if (toolbar)
                {
                    event.Check(all_panes[i].IsResizable());
                    break;
                }
            }
            break;
        }
        case ID_AllowFloating:
            event.Check((flags & wxAUI_MGR_ALLOW_FLOATING) != 0);
            break;
        case ID_TransparentDrag:
            event.Check((flags & wxAUI_MGR_TRANSPARENT_DRAG) != 0);
            break;
        case ID_TransparentHint:
            event.Check((flags & wxAUI_MGR_TRANSPARENT_HINT) != 0);
            break;
        case ID_LiveUpdate:
            event.Check((flags & wxAUI_MGR_LIVE_RESIZE) != 0);
            break;
        case ID_VenetianBlindsHint:
            event.Check((flags & wxAUI_MGR_VENETIAN_BLINDS_HINT) != 0);
            break;
        case ID_RectangleHint:
            event.Check((flags & wxAUI_MGR_RECTANGLE_HINT) != 0);
            break;
        case ID_NoHint:
            event.Check(((wxAUI_MGR_TRANSPARENT_HINT |
                          wxAUI_MGR_VENETIAN_BLINDS_HINT |
                          wxAUI_MGR_RECTANGLE_HINT) & flags) == 0);
            break;
        case ID_HintFade:
            event.Check((flags & wxAUI_MGR_HINT_FADE) != 0);
            break;
        case ID_NoVenetianFade:
            event.Check((flags & wxAUI_MGR_NO_VENETIAN_BLINDS_FADE) != 0);
            break;

        /*case ID_NotebookNoCloseButton:
            event.Check((m_notebook_style & (wxAUI_NB_CLOSE_BUTTON|wxAUI_NB_CLOSE_ON_ALL_TABS|wxAUI_NB_CLOSE_ON_ACTIVE_TAB)) != 0);
            break;
        case ID_NotebookCloseButton:
            event.Check((m_notebook_style & wxAUI_NB_CLOSE_BUTTON) != 0);
            break;
        case ID_NotebookCloseButtonAll:
            event.Check((m_notebook_style & wxAUI_NB_CLOSE_ON_ALL_TABS) != 0);
            break;
        case ID_NotebookCloseButtonActive:
            event.Check((m_notebook_style & wxAUI_NB_CLOSE_ON_ACTIVE_TAB) != 0);
            break;
        case ID_NotebookAllowTabSplit:
            event.Check((m_notebook_style & wxAUI_NB_TAB_SPLIT) != 0);
            break;
        case ID_NotebookAllowTabMove:
            event.Check((m_notebook_style & wxAUI_NB_TAB_MOVE) != 0);
            break;
        case ID_NotebookAllowTabExternalMove:
            event.Check((m_notebook_style & wxAUI_NB_TAB_EXTERNAL_MOVE) != 0);
            break;
        case ID_NotebookScrollButtons:
            event.Check((m_notebook_style & wxAUI_NB_SCROLL_BUTTONS) != 0);
            break;
        case ID_NotebookWindowList:
            event.Check((m_notebook_style & wxAUI_NB_WINDOWLIST_BUTTON) != 0);
            break;
        case ID_NotebookTabFixedWidth:
            event.Check((m_notebook_style & wxAUI_NB_TAB_FIXED_WIDTH) != 0);
            break;
        case ID_NotebookArtGloss:
            event.Check(m_notebook_style == 0);
            break;
        case ID_NotebookArtSimple:
            event.Check(m_notebook_style == 1);
            break;
		*/
    }
}

void MainFrame::OnPaneClose(wxAuiManagerEvent& evt)
{
    if (evt.pane->name == wxT("test10"))
    {
        int res = wxMessageBox(wxT("Are you sure you want to close/hide this pane?"),
                               wxT("wxAUI"),
                               wxYES_NO,
                               this);
        if (res != wxYES)
            evt.Veto();
    }
}

void MainFrame::OnCreatePerspective(wxCommandEvent& WXUNUSED(event))
{
    wxTextEntryDialog dlg(this, wxT("Enter a name for the new perspective:"),
                          wxT("wxAUI Test"));

    dlg.SetValue(wxString::Format(wxT("Perspective %u"), unsigned(m_perspectives.GetCount() + 1)));
    if (dlg.ShowModal() != wxID_OK)
        return;

    if (m_perspectives.GetCount() == 0)
    {
        m_perspectives_menu->AppendSeparator();
    }

    m_perspectives_menu->Append(ID_FirstPerspective + m_perspectives.GetCount(), dlg.GetValue());
    m_perspectives.Add(m_mgr.SavePerspective());
}

void MainFrame::OnCopyPerspectiveCode(wxCommandEvent& WXUNUSED(evt))
{
    wxString s = m_mgr.SavePerspective();

#if wxUSE_CLIPBOARD
    if (wxTheClipboard->Open())
    {
        wxTheClipboard->SetData(new wxTextDataObject(s));
        wxTheClipboard->Close();
    }
#endif
}

void MainFrame::OnRestorePerspective(wxCommandEvent& evt)
{
    m_mgr.LoadPerspective(m_perspectives.Item(evt.GetId() - ID_FirstPerspective));
}

void MainFrame::OnNotebookPageClose(wxAuiNotebookEvent& evt)
{
    wxAuiNotebook* ctrl = (wxAuiNotebook*)evt.GetEventObject();
    if (ctrl->GetPage(evt.GetSelection())->IsKindOf(CLASSINFO(wxHtmlWindow)))
    {
        int res = wxMessageBox(wxT("Are you sure you want to close/hide this notebook page?"),
                       wxT("wxAUI"),
                       wxYES_NO,
                       this);
        if (res != wxYES)
            evt.Veto();
    }
}

void MainFrame::OnNotebookPageClosed(wxAuiNotebookEvent& evt)
{
    wxAuiNotebook* ctrl = (wxAuiNotebook*)evt.GetEventObject();

    // selection should always be a valid index
    wxASSERT_MSG( ctrl->GetSelection() < (int)ctrl->GetPageCount(),
                  wxString::Format("Invalid selection %d, only %d pages left",
                                   ctrl->GetSelection(),
                                   (int)ctrl->GetPageCount()) );

    evt.Skip();
}

void MainFrame::OnNotebookPageChanged(wxAuiNotebookEvent& evt)
{
    wxAuiNotebook* ctrl = (wxAuiNotebook*)evt.GetEventObject();
	wxWindow* sel = ctrl->GetCurrentPage();
	Scene* s = dynamic_cast<Scene*>(sel);
	if (s) {
		CoreTraits::get(this)->SetActiveScene(s);
	}
}

void MainFrame::OnAllowNotebookDnD(wxAuiNotebookEvent& evt)
{
    // for the purpose of this test application, explicitly
    // allow all noteboko drag and drop events
    evt.Allow();
}

wxPoint MainFrame::GetStartPosition()
{
    static int x = 0;
    x += 20;
    wxPoint pt = ClientToScreen(wxPoint(0,0));
    return wxPoint(pt.x + x, pt.y + x);
}

void MainFrame::OnCreateTree(wxCommandEvent& WXUNUSED(event))
{
	/*
    m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
                  Caption(wxT("Tree Control")).
                  Float().FloatingPosition(GetStartPosition()).
                  FloatingSize(wxSize(150,300)));
    */
	m_mgr.GetPane(CoreTraits::get(this)->GetTreeCtrl()).Show();
	m_mgr.Update();
}

void MainFrame::OnCreateGrid(wxCommandEvent& WXUNUSED(event))
{
	m_mgr.GetPane(CoreTraits::get(this)->GetPropGrid()).Show();
    m_mgr.Update();
}

void MainFrame::OnCreateNotebook(wxCommandEvent& WXUNUSED(event))
{
	m_mgr.GetPane(CoreTraits::get(this)->GetNotebook()).Show();
    //m_mgr.AddPane(, wxAuiPaneInfo().
     //             Caption(wxT("Notebook")).
     //             Float().FloatingPosition(GetStartPosition()).
                  //FloatingSize(300,200).
       //           CloseButton(true).MaximizeButton(true));
    m_mgr.Update();
}

void MainFrame::OnCreateText(wxCommandEvent& WXUNUSED(event))
{
    m_mgr.AddPane(CreateTextCtrl(), wxAuiPaneInfo().
                  Caption(wxT("Text Control")).
                  Float().FloatingPosition(GetStartPosition()));
    m_mgr.Update();
}

void MainFrame::OnCreateSizeReport(wxCommandEvent& WXUNUSED(event))
{
    m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
                  Caption(wxT("Client Size Reporter")).
                  Float().FloatingPosition(GetStartPosition()).
                  CloseButton(true).MaximizeButton(true));
    m_mgr.Update();
}

void MainFrame::OnDropDownToolbarItem(wxAuiToolBarEvent& evt)
{
    if (evt.IsDropDownClicked())
    {
        wxAuiToolBar* tb = static_cast<wxAuiToolBar*>(evt.GetEventObject());

        tb->SetToolSticky(evt.GetId(), true);

        // create the popup menu
        wxMenu menuPopup;

        wxBitmap bmp = wxArtProvider::GetBitmap(wxART_QUESTION, wxART_OTHER, wxSize(16,16));

        wxMenuItem* m1 =  new wxMenuItem(&menuPopup, 10001, _("Drop Down Item 1"));
        m1->SetBitmap(bmp);
        menuPopup.Append(m1);

        wxMenuItem* m2 =  new wxMenuItem(&menuPopup, 10002, _("Drop Down Item 2"));
        m2->SetBitmap(bmp);
        menuPopup.Append(m2);

        wxMenuItem* m3 =  new wxMenuItem(&menuPopup, 10003, _("Drop Down Item 3"));
        m3->SetBitmap(bmp);
        menuPopup.Append(m3);

        wxMenuItem* m4 =  new wxMenuItem(&menuPopup, 10004, _("Drop Down Item 4"));
        m4->SetBitmap(bmp);
        menuPopup.Append(m4);

        // line up our menu with the button
        wxRect rect = tb->GetToolRect(evt.GetId());
        wxPoint pt = tb->ClientToScreen(rect.GetBottomLeft());
        pt = ScreenToClient(pt);


        PopupMenu(&menuPopup, pt);


        // make sure the button is "un-stuck"
        tb->SetToolSticky(evt.GetId(), false);
    }
}


void MainFrame::OnTabAlignment(wxCommandEvent &evt)
{
    size_t i, count;
    wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
    for (i = 0, count = all_panes.GetCount(); i < count; ++i)
    {
        wxAuiPaneInfo& pane = all_panes.Item(i);
        if (pane.window->IsKindOf(CLASSINFO(wxAuiNotebook)))
        {
            wxAuiNotebook* nb = (wxAuiNotebook*)pane.window;

            long style = nb->GetWindowStyleFlag();
            style &= ~(wxAUI_NB_TOP | wxAUI_NB_BOTTOM);
            if (evt.GetId() == ID_NotebookAlignTop)
                style |= wxAUI_NB_TOP;
            else if (evt.GetId() == ID_NotebookAlignBottom)
                style |= wxAUI_NB_BOTTOM;
            nb->SetWindowStyleFlag(style);

            nb->Refresh();
        }
    }
}

void MainFrame::OnNew(wxCommandEvent& WXUNUSED(event))
{
	wxAuiNotebook* ctrl = CoreTraits::get(this)->GetNotebook();
   Scene* scene = new Scene(ctrl, this);
   
   ctrl->AddPage(scene, wxT("Canvas"), true);
   ctrl->SetPageToolTip(0, "Welcome to wxAUI (this is a page tooltip)");
	CoreTraits::get(this)->SetActiveScene(scene);
   //ctrl->Thaw();
   //return ctrl;
}

void MainFrame::OpenFile(const wxString& path) {

	wxAuiNotebook* ctrl = CoreTraits::get(this)->GetNotebook();
	Scene* scene = new Scene(ctrl, this);
	scene->Load(path);
	ctrl->AddPage(scene, wxFileNameFromPath(path), true);
   	ctrl->SetPageToolTip(0, "Welcome to wxAUI (this is a page tooltip)");
	CoreTraits::get(this)->SetActiveScene(scene);
}

void MainFrame::OnOpen(wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog dlg(this, wxT("Open file"), wxEmptyString, wxEmptyString, wxT("Any file (*)|*"),
			                      wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);
	if (dlg.ShowModal() != wxID_OK) return;
	this->OpenFile(dlg.GetPath());
	mFileHistory->AddFileToHistory(dlg.GetPath());
   //ctrl->Thaw();
   //return ctrl;
}

void MainFrame::OnPref(wxCommandEvent& WXUNUSED(event))
{
	wxGetApp().ShowPreferencesEditor(this);
}


void MainFrame::OnRecentFile(wxCommandEvent& event)
{
	wxString fn(mFileHistory->GetHistoryFile(event.GetId() - wxID_FILE1));
	this->OpenFile(fn);
	//if (!f.empty())
	//	(void)m_docManager->CreateDocument(f, wxDOC_SILENT);
}

void MainFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
	wxGetApp().DismissPreferencesEditor();
    Close(true);
}

void MainFrame::UpdateControls()
{
	//m_undo->Enable(CoreTraits::get()->GetCmds()->CanUndo());
	//m_redo->Enable(CoreTraits::get()->GetCmds()->CanRedo());
}

void MainFrame::OnUndo(wxCommandEvent& WXUNUSED(event))
{
	CoreTraits::get()->GetCmds()->Undo();
}

void MainFrame::OnRedo(wxCommandEvent& WXUNUSED(event))
{
	CoreTraits::get()->GetCmds()->Redo();
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxAboutDialogInfo info;
	info.SetName(SCENEEDITOR_NAME);
	info.SetVersion(SCENEEDITOR_VERSION);
	//info.SetDescription(_("This program does something great."));
	info.SetCopyright(wxT("Copyright (C) 2015"));
	info.SetWebSite(SCENEEDITOR_HOMEPAGE);
	info.AddDeveloper("Milan Dunghubel");
	wxAboutBox(info);
    //wxMessageBox(_("wxAUI Demo\nAn advanced window management library for wxWidgets\n(c) Copyright 2005-2006, Kirix Corporation"), _("About wxAUI Demo"), wxOK, this);
}

wxTextCtrl* MainFrame::CreateTextCtrl(const wxString& ctrl_text)
{
    static int n = 0;

    wxString text;
    if ( !ctrl_text.empty() )
        text = ctrl_text;
    else
        text.Printf(wxT("This is text box %d"), ++n);

    return new wxTextCtrl(this,wxID_ANY, text,
                          wxPoint(0,0), wxSize(150,90),
                          wxNO_BORDER | wxTE_MULTILINE);
}



void MainFrame::OnTreeItemChanged(wxTreeEvent& event)
{
	//wxLogMessage("Changed");
	wxTreeItemData* d = CoreTraits::get(this)->GetTreeCtrl()->GetItemData(event.GetItem());
	TreeNodePtr* n = dynamic_cast<TreeNodePtr*>(d);
	if (n && CoreTraits::get()->GetScene()) {
		CoreTraits::get()->GetScene()->select(n->get());
	}
	//CoreTraits::Get()->GetCmds()->Sub();
}

wxSizeReportCtrl* MainFrame::CreateSizeReportCtrl(int width, int height)
{
    wxSizeReportCtrl* ctrl = new wxSizeReportCtrl(this, wxID_ANY,
                                   wxDefaultPosition,
                                   wxSize(width, height), &m_mgr);
    return ctrl;
}

/*wxHtmlWindow* MainFrame::CreateHTMLCtrl(wxWindow* parent)
{
    if (!parent)
        parent = this;

    wxHtmlWindow* ctrl = new wxHtmlWindow(parent, wxID_ANY,
                                   wxDefaultPosition,
                                   wxSize(400,300));
    ctrl->SetPage(GetIntroText());
    return ctrl;
}*/


/*wxAuiNotebook* MainFrame::CreateNotebook()
{
   // create the notebook off-window to avoid flicker
   wxSize client_size = GetClientSize();

   ctrl = new wxAuiNotebook(this, wxID_ANY,
                                    wxPoint(client_size.x, client_size.y),
                                    wxSize(430,200),
                                    m_notebook_style);
   ctrl->Freeze();

   wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16));

   /*ctrl->AddPage(CreateHTMLCtrl(ctrl), wxT("Welcome to wxAUI") , false, page_bmp);
   ctrl->SetPageToolTip(0, "Welcome to wxAUI (this is a page tooltip)");

   wxPanel *panel = new wxPanel( ctrl, wxID_ANY );
   wxFlexGridSizer *flex = new wxFlexGridSizer( 4, 2, 0, 0 );
   flex->AddGrowableRow( 0 );
   flex->AddGrowableRow( 3 );
   flex->AddGrowableCol( 1 );
   flex->Add( 5,5 );   flex->Add( 5,5 );
   flex->Add( new wxStaticText( panel, -1, wxT("wxTextCtrl:") ), 0, wxALL|wxALIGN_CENTRE, 5 );
   flex->Add( new wxTextCtrl( panel, -1, wxT(""), wxDefaultPosition, wxSize(100,-1)),
                1, wxALL|wxALIGN_CENTRE, 5 );
   flex->Add( new wxStaticText( panel, -1, wxT("wxSpinCtrl:") ), 0, wxALL|wxALIGN_CENTRE, 5 );
   flex->Add( new wxSpinCtrl( panel, -1, wxT("5"), wxDefaultPosition, wxSize(100,-1),
                wxSP_ARROW_KEYS, 5, 50, 5 ), 0, wxALL|wxALIGN_CENTRE, 5 );
   flex->Add( 5,5 );   flex->Add( 5,5 );
   panel->SetSizer( flex );
   ctrl->AddPage( panel, wxT("wxPanel"), false, page_bmp );
	*/
   /*
   ctrl->AddPage( new wxTextCtrl( ctrl, wxID_ANY, wxT("Some text"),
                wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxNO_BORDER) , wxT("wxTextCtrl 1"), false, page_bmp );

   ctrl->AddPage( new wxTextCtrl( ctrl, wxID_ANY, wxT("Some more text"),
                wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxNO_BORDER) , wxT("wxTextCtrl 2") );

   ctrl->AddPage( new wxTextCtrl( ctrl, wxID_ANY, wxT("Some more text"),
                wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxNO_BORDER) , wxT("wxTextCtrl 3") );

   ctrl->AddPage( new wxTextCtrl( ctrl, wxID_ANY, wxT("Some more text"),
                wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxNO_BORDER) , wxT("wxTextCtrl 4") );

   ctrl->AddPage( new wxTextCtrl( ctrl, wxID_ANY, wxT("Some more text"),
                wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxNO_BORDER) , wxT("wxTextCtrl 5") );

   ctrl->AddPage( new wxTextCtrl( ctrl, wxID_ANY, wxT("Some more text"),
                wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxNO_BORDER) , wxT("wxTextCtrl 6") );

   ctrl->AddPage( new wxTextCtrl( ctrl, wxID_ANY, wxT("Some more text"),
                wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxNO_BORDER) , wxT("wxTextCtrl 7 (longer title)") );
   ctrl->SetPageToolTip(ctrl->GetPageCount()-1,
                        "wxTextCtrl 7: and the tooltip message can be even longer!");

   ctrl->AddPage( new wxTextCtrl( ctrl, wxID_ANY, wxT("Some more text"),
                wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxNO_BORDER) , wxT("wxTextCtrl 8") );
	*/

void MainFrame::OnSlider(wxScrollEvent& event)
{
    wxASSERT_MSG( event.GetInt() == m_slider->GetValue(),
                  wxT("slider value should be the same") );

	int zoom = event.GetInt();
    GetStatusBar()->SetStatusText(wxString::Format(_("%d%%"), zoom), StatusBarField_Zoom);
	CoreTraits::get()->GetScene()->SetZoom(zoom / 100.f);

}


wxString MainFrame::GetIntroText()
{
    const char* text =
        "<html><body>"
        "<h3>Welcome to wxAUI</h3>"
        "<br/><b>Overview</b><br/>"
        "<p>wxAUI is an Advanced User Interface library for the wxWidgets toolkit "
        "that allows developers to create high-quality, cross-platform user "
        "interfaces quickly and easily.</p>"
        "<p><b>Features</b></p>"
        "<p>With wxAUI, developers can create application frameworks with:</p>"
        "<ul>"
        "<li>Native, dockable floating frames</li>"
        "<li>Perspective saving and loading</li>"
        "<li>Native toolbars incorporating real-time, &quot;spring-loaded&quot; dragging</li>"
        "<li>Customizable floating/docking behaviour</li>"
        "<li>Completely customizable look-and-feel</li>"
        "<li>Optional transparent window effects (while dragging or docking)</li>"
        "<li>Splittable notebook control</li>"
        "</ul>"
        "<p><b>What's new in 0.9.4?</b></p>"
        "<p>wxAUI 0.9.4, which is bundled with wxWidgets, adds the following features:"
        "<ul>"
        "<li>New wxAuiToolBar class, a toolbar control which integrates more "
        "cleanly with wxAuiFrameManager.</li>"
        "<li>Lots of bug fixes</li>"
        "</ul>"
        "<p><b>What's new in 0.9.3?</b></p>"
        "<p>wxAUI 0.9.3, which is now bundled with wxWidgets, adds the following features:"
        "<ul>"
        "<li>New wxAuiNotebook class, a dynamic splittable notebook control</li>"
        "<li>New wxAuiMDI* classes, a tab-based MDI and drop-in replacement for classic MDI</li>"
        "<li>Maximize/Restore buttons implemented</li>"
        "<li>Better hinting with wxGTK</li>"
        "<li>Class rename.  'wxAui' is now the standard class prefix for all wxAUI classes</li>"
        "<li>Lots of bug fixes</li>"
        "</ul>"
        "<p><b>What's new in 0.9.2?</b></p>"
        "<p>The following features/fixes have been added since the last version of wxAUI:</p>"
        "<ul>"
        "<li>Support for wxMac</li>"
        "<li>Updates for wxWidgets 2.6.3</li>"
        "<li>Fix to pass more unused events through</li>"
        "<li>Fix to allow floating windows to receive idle events</li>"
        "<li>Fix for minimizing/maximizing problem with transparent hint pane</li>"
        "<li>Fix to not paint empty hint rectangles</li>"
        "<li>Fix for 64-bit compilation</li>"
        "</ul>"
        "<p><b>What changed in 0.9.1?</b></p>"
        "<p>The following features/fixes were added in wxAUI 0.9.1:</p>"
        "<ul>"
        "<li>Support for MDI frames</li>"
        "<li>Gradient captions option</li>"
        "<li>Active/Inactive panes option</li>"
        "<li>Fix for screen artifacts/paint problems</li>"
        "<li>Fix for hiding/showing floated window problem</li>"
        "<li>Fix for floating pane sizing problem</li>"
        "<li>Fix for drop position problem when dragging around center pane margins</li>"
        "<li>LF-only text file formatting for source code</li>"
        "</ul>"
        "<p>See README.txt for more information.</p>"
        "</body></html>";

    return wxString::FromAscii(text);
}
