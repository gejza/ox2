
#include "resources.h"
#include <wx/imaglist.h>
#include <wx/icon.h>
#include <wx/xml/xml.h>
#include <wx/log.h>

Resource::Resource(const wxString& path, wxXmlNode* node)
{
	wxString file = node->GetAttribute("file");
	this->fn_.Assign(path, file);
	this->fn_.MakeAbsolute();
	id_ = node->GetAttribute("id", fn_.GetName());
	if (!fn_.FileExists()) {
		wxFileName fnabs(fn_);
		fnabs.MakeAbsolute();
		wxLogWarning(_("Resource file %s not exists."), fnabs.GetFullPath().c_str());
	}
}

Resources* Resources::Get()
{
	static Resources _res;
	return &_res;
}

void Resources::Load(wxXmlNode* node) {
	static int id = 0;
	//wxLogMessage("Node %s", node->GetName().c_str());

	if (node->GetName() == "image") {
		Resource item("../laser/data/" + _path, node);
		_items.push_back(item);
	}
	if (node->GetName() == "set") {
		_path = node->GetAttribute("path");
	}

	wxXmlNode *child = node->GetChildren();
	while (child) {
		this->Load(child);

		child = child->GetNext();
	}
}

Resource* Resources::Get(const wxString& id)
{
	for (std::vector<Resource>::iterator i = _items.begin(); i != _items.end(); i++) {
		if (i->GetId() == id) {
			return &(*i);
		}
	}
	wxLogWarning(_("Resource %s not found."), id.c_str());
	return NULL;
}

ResourceView::ResourceView(wxWindow *parent) {
	Create(parent);
}



void ResourceView::Create(wxWindow *parent) {
	wxListCtrl::Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);

	wxImageList* m_pImageList = new wxImageList(16, 16);
	wxIcon icon;
	icon.LoadFile(wxT("res/physics16.png"), wxBITMAP_TYPE_ANY);
	m_pImageList->Add(icon);
	SetImageList(m_pImageList, wxIMAGE_LIST_SMALL);


	// Add first column       
	wxListItem col0;
	col0.SetId(0);
	col0.SetText(_("Id"));
	col0.SetWidth(50);
	this->InsertColumn(0, col0);

	// Add second column
	wxListItem col1;
	col1.SetId(1);
	col1.SetText(_("Size"));
	col1.SetWidth(80);
	this->InsertColumn(1, col1);

	// Add thirs column     
	wxListItem col2;
	col2.SetId(2);
	col2.SetText(_("Path"));
	col2.SetWidth(180);
	this->InsertColumn(2, col2);

	
}

void ResourceView::Load(const wxString& fn)
{
	wxXmlDocument doc;
	if (!doc.Load(fn)) {
		wxLogWarning(_("Failed open %s"), fn.c_str());
		return;
	}

	Resources::Get()->Load(doc.GetRoot());

	for (int n = 0; n<Resources::Get()->GetCount(); n++)
	{
		wxListItem item;
		item.SetId(n);
		item.SetText(Resources::Get()->Get(n)->GetId());

		this->InsertItem(item);

		// set value in second column
		wxFileName fn = Resources::Get()->Get(n)->GetFileName();
		//fn.MakeAbsolute();
		this->SetItem(n, 1, Resources::Get()->Get(n)->GetFileName().GetHumanReadableSize());
		this->SetItem(n, 2, fn.GetFullPath());
	}
}

