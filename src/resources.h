#pragma once

#include <vector>
#include <wx/listctrl.h>
#include <wx/filename.h>

class wxXmlNode;

class Resource
{
public:
	//Resource(const wxString& name, const wxString& path) 
	//	: name_(name), fn_(path, name) {}
	Resource(const wxString& path, wxXmlNode* node);
	const wxString& GetId() const {
		return id_;
	}
	const wxFileName& GetFileName() const {
		return fn_;
	}
private:
	wxString id_;
	wxFileName fn_;
};

class Resources
{
public:
	void Load(wxXmlNode* node);
	int GetCount() const {
		return (int)_items.size();
	}
	Resource* Get(int n) {
		return &_items[n];
	}
	Resource* Get(const wxString& id);
	static Resources* Get();
private:
	Resources() {}

	std::vector<Resource> _items;
	wxString _path;
};

class ResourceView : public wxListCtrl
{
public:
	ResourceView(wxWindow *parent);
	void Create(wxWindow *parent);
	void Load(const wxString& fn);
private:

};