#pragma once

#include "wx/aui/aui.h"
#include "wx/grid.h"
#include "wx/treectrl.h"
#include "wx/wxhtml.h"
#include <wx/propgrid/propgrid.h>

#include <wx/cmdproc.h>

// -- frame --
class wxSizeReportCtrl;

class Scene;
class MainFrame;

class wxFileHistory;
class wxSlider;
class CoreTraits
{
public:
	static CoreTraits* get(MainFrame* main = NULL);
	wxTreeCtrl* GetTreeCtrl();
    wxPropertyGrid* GetPropGrid();
    wxAuiNotebook* GetNotebook();
	wxCommandProcessor* GetCmds() {
		return &_cmds;
	}
	void SetActiveScene(Scene* scene);
	Scene* GetScene() {
		return _current;
	}

	enum {
		ID_TreeCtrl = wxID_HIGHEST+1,
		ID_Max,
	};
private:
	CoreTraits(MainFrame* main);
	static CoreTraits* _this;
	MainFrame* _main;
	wxTreeCtrl* _tree_ctrl;
	wxPropertyGrid* _prop_grid;
	wxAuiNotebook* _tabs;
	Scene* _current;
	wxCommandProcessor _cmds;
};

class MainFrame : public wxFrame
{
    enum
    {
        ID_CreateTree = CoreTraits::ID_Max,
        ID_CreateGrid,
        ID_CreateText,
        ID_CreateHTML,
        ID_CreateNotebook,
        ID_CreateSizeReport,
        ID_GridContent,
        ID_TextContent,
        ID_TreeContent,
        ID_HTMLContent,
        ID_NotebookContent,
        ID_SizeReportContent,
        ID_CreatePerspective,
        ID_CopyPerspectiveCode,
        ID_AllowFloating,
        ID_AllowActivePane,
        ID_TransparentHint,
        ID_VenetianBlindsHint,
        ID_RectangleHint,
        ID_NoHint,
        ID_HintFade,
        ID_NoVenetianFade,
        ID_TransparentDrag,
        ID_NoGradient,
        ID_VerticalGradient,
        ID_HorizontalGradient,
        ID_LiveUpdate,
        ID_AllowToolbarResizing,
        ID_Settings,
        ID_CustomizeToolbar,
        ID_DropDownToolbarItem,
        ID_NotebookNoCloseButton,
        ID_NotebookCloseButton,
        ID_NotebookCloseButtonAll,
        ID_NotebookCloseButtonActive,
        ID_NotebookAllowTabMove,
        ID_NotebookAllowTabExternalMove,
        ID_NotebookAllowTabSplit,
        ID_NotebookWindowList,
        ID_NotebookScrollButtons,
        ID_NotebookTabFixedWidth,
        ID_NotebookArtGloss,
        ID_NotebookArtSimple,
        ID_NotebookAlignTop,
        ID_NotebookAlignBottom,
		ID_Slider,

        ID_SampleItem,

        ID_FirstPerspective = ID_CreatePerspective+1000
    };

public:
    MainFrame(wxWindow* parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER);

    ~MainFrame();

    wxAuiDockArt* GetDockArt();
    void DoUpdate();

	void OpenFile(const wxString& filename);
//private:
    wxTextCtrl* CreateTextCtrl(const wxString& text = wxEmptyString);
    wxSizeReportCtrl* CreateSizeReportCtrl(int width = 80, int height = 80);
    wxPoint GetStartPosition();
    //wxHtmlWindow* CreateHTMLCtrl(wxWindow* parent = NULL);

    wxString GetIntroText();

//private:

    void OnEraseBackground(wxEraseEvent& evt);
    void OnSize(wxSizeEvent& evt);

    void OnCreateTree(wxCommandEvent& evt);
    void OnCreateGrid(wxCommandEvent& evt);
    void OnCreateNotebook(wxCommandEvent& evt);
    void OnCreateText(wxCommandEvent& evt);
    void OnCreateSizeReport(wxCommandEvent& evt);
    void OnDropDownToolbarItem(wxAuiToolBarEvent& evt);
    void OnCreatePerspective(wxCommandEvent& evt);
    void OnCopyPerspectiveCode(wxCommandEvent& evt);
    void OnRestorePerspective(wxCommandEvent& evt);
    void OnSettings(wxCommandEvent& evt);
    void OnCustomizeToolbar(wxCommandEvent& evt);
    void OnAllowNotebookDnD(wxAuiNotebookEvent& evt);
    void OnNotebookPageClose(wxAuiNotebookEvent& evt);
    void OnNotebookPageClosed(wxAuiNotebookEvent& evt);
    void OnNotebookPageChanged(wxAuiNotebookEvent& evt);
    void OnNew(wxCommandEvent& evt);
    void OnOpen(wxCommandEvent& evt);
    void OnExit(wxCommandEvent& evt);
    void OnAbout(wxCommandEvent& evt);
    void OnRedo(wxCommandEvent& evt);
    void OnUndo(wxCommandEvent& evt);
    void OnTabAlignment(wxCommandEvent &evt);

    void OnGradient(wxCommandEvent& evt);
    void OnToolbarResizing(wxCommandEvent& evt);
    void OnManagerFlag(wxCommandEvent& evt);
    //void OnNotebookFlag(wxCommandEvent& evt);
    void OnUpdateUI(wxUpdateUIEvent& evt);

    void OnPaneClose(wxAuiManagerEvent& evt);
	void OnTreeItemChanged(wxTreeEvent& event);

	void UpdateControls();
	void OnSlider(wxScrollEvent& event);
private:

    wxAuiManager m_mgr;
	wxFileHistory* mFileHistory;
    wxArrayString m_perspectives;
    wxMenu* m_perspectives_menu;
    long m_notebook_theme;
	wxSlider* m_slider;
	wxMenuItem* m_undo;
	wxMenuItem* m_redo;
    wxDECLARE_EVENT_TABLE();
};


