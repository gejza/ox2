#pragma once

#include <stddef.h>
#include <wx/defs.h>
#include <wx/cmdproc.h>

class Scene;
class MainFrame;
class wxTreeCtrl;
class wxPropertyGrid;
class wxAuiNotebook;

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
		ID_TreeCtrl = wxID_HIGHEST + 1,
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

#include <iostream>
#include <wx/config.h>

template<class Traits, class T>
class ConfigValue_t
{
public:
	ConfigValue_t(const char* name) 
		: _name(wxString::Format("/%s/%s", Traits::ID, name)) {}
	const ConfigValue_t<Traits, T>& operator = (const T& value) {
		wxConfigBase* pConfig = wxConfigBase::Get();
		do {
			std::cout << "write to conf " << _name << " val " << value << std::endl;
		} while (0);
		pConfig->Write(_name, value);
		return *this;
	}
	bool GetBool(bool def) {
		wxConfigBase* pConfig = wxConfigBase::Get();
		do {
			std::cout << "read conf " << _name << std::endl;
		} while (0);
		return pConfig->ReadBool(_name, def);
	}
private:
	wxString _name;
};


struct CfgGeneric
{
	static const char* ID;
};


static ConfigValue_t<CfgGeneric, bool> cfg_show_splash("ShowSplash");

