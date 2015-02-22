#include "node.h"
#include <wx/xml/xml.h>
#include <sstream>
#include <wx/treectrl.h>
#include <wx/propgrid/propgrid.h>
#include "mainframe.h"

class HP_t
{
public:
	HP_t(wxXmlNode *node) : _node(node) {}
	wxXmlNode* operator->() {
		return _node;
	}
	wxString get_str(const wxString& att) {
		return _node->GetAttribute(att);
	}
	int get_int(const wxString& att) {
		return wxAtoi(this->get_str(att));
	}
	/*template<class T>
	T get(const wxString& att) {
		wxString val = _node->GetAttribute(att);
		std::istringstream convert(val.c_str());
		T ret;
		convert >> ret;
		return ret;
	}*/
private:
	wxXmlNode* _node;
};

Node* Node::create(wxXmlNode* node2)
{
	HP_t node(node2);
	if (node->GetName() == "circle") {
		return new NodeCircle(node.get_int("x"), node.get_int("y"), node.get_int("radius"));
	}
	if (node->GetName() == "image") {
		return new NodeImage(wxPoint(node.get_int("x"), node.get_int("y")), node.get_str("res"));
	}
	return new NodeList();
}


void Node::select(bool selected) {
	_selected = selected;
	if (_selected && _tree_id.IsOk()) {
		CoreTraits::get()->GetTreeCtrl()->SelectItem(_tree_id, true);

		wxPropertyGrid* pg = CoreTraits::get()->GetPropGrid();
		pg->Clear();
		pg->Append(new wxStringProperty("Name", wxPG_LABEL, wxString(this->ClassName())));
		// One way to add category (similar to how other properties are added)
		/*_prop_grid->Append(new wxPropertyCategory("Main"));
		// All these are added to "Main" category
		_prop_grid->Append(new wxIntProperty("Age", wxPG_LABEL, 25));
		_prop_grid->Append(new wxIntProperty("Height", wxPG_LABEL, 180));
		_prop_grid->Append(new wxIntProperty("Weight"));
		// Another one
		_prop_grid->Append(new wxPropertyCategory("Attributes"));
		// All these are added to "Attributes" category
		_prop_grid->Append(new wxIntProperty("Intelligence"));
		_prop_grid->Append(new wxIntProperty("Agility"));
		_prop_grid->Append(new wxIntProperty("Strength"));
	*/
	}

}
void Node::tree(wxTreeCtrl* ctrl, const wxTreeItemId &parent)
{
	_tree_id = ctrl->AppendItem(parent, this->ClassName(), -1, -1, new TreeNodePtr(this));
}

void NodeList::tree(wxTreeCtrl* ctrl, const wxTreeItemId &parent)
{
	_tree_id = ctrl->AddRoot("Scene", -1, -1,  new TreeNodePtr(this));
	for (list_type::iterator i=_child.begin();i != _child.end();++i) {
		(*i)->tree(ctrl, _tree_id);
	}

}


void NodeList::Draw(wxDC& dc)
{
	for (list_type::iterator i=_child.begin();i != _child.end();++i) {
		(*i)->Draw(dc);
	}
}

Node* NodeList::find(int x, int y) {
	for (list_type::reverse_iterator i=_child.rbegin();i != _child.rend();++i) {
		Node* n = (*i)->find(x,y);
		if (n) {
			return n;
		}
	}
	return NULL;
}

void NodeList::Add(Node* child)
{
	_child.push_back(child);
}

class NG_t
{
public:
	NG_t(const wxString& name) : _node(0) {
		_node=new wxXmlNode(wxXML_ELEMENT_NODE,name);
	}
	NG_t(wxXmlNode *node) : _node(node) {}
	~NG_t() {
		if (_node) {
			delete _node;
		}
		_node = 0;
	}
	wxXmlNode* release() {
		wxXmlNode* ret = _node;
		_node = 0;
		return ret;
	}
	wxXmlNode* operator->() {
		return _node;
	}
private:
	wxXmlNode* _node;
};

wxXmlNode* NodeList::serialize() const
{
	NG_t node(wxT("list"));
	//wxXmlNode *node=new wxXmlNode(wxXML_ELEMENT_NODE,wxT("list"));
	for (list_type::const_iterator i=_child.begin();i != _child.end();++i) {
		node->AddChild((*i)->serialize());
	}
	return node.release();
}

void NodeList::load(wxXmlNode* node)
{
	wxXmlNode *child = node->GetChildren();
	while (child) {
		this->Add(Node::create(child));
		child = child->GetNext();
	}
}

NodeCircle::NodeCircle(int x, int y, int r) :
	_x(x), _y(y), _r(r)
{
}

void NodeCircle::Draw(wxDC& dc)
{
    dc.SetPen( *wxRED_PEN );
    dc.SetBrush( *wxGREEN_BRUSH );

    dc.DrawCircle(_x, _y, _r);
}

int distance(const wxPoint& a, const wxPoint& b)
{
	float w = a.x - b.x;
	float h = a.y - b.y;
	return sqrtf(w*w+h*h);
}

Node* NodeCircle::find(int x, int y) {
	return (distance(wxPoint(x,y),wxPoint(_x,_y)) <= _r) ? this : NULL;
}


wxXmlNode* NodeCircle::serialize() const
{
	wxXmlNode *node=new wxXmlNode(wxXML_ELEMENT_NODE,wxT("circle"));
	node->AddAttribute("x", wxString::Format(wxT("%i"),_x));
	node->AddAttribute("y", wxString::Format(wxT("%i"),_y));
	node->AddAttribute("radius", wxString::Format(wxT("%i"),_r));
	return node;
}


NodeImage::NodeImage(const wxPoint& pos, const wxBitmap& image) :
	_pos(pos), _image(image)
{
}

#include "resources.h"

NodeImage::NodeImage(const wxPoint& pos, const wxString& id) :
	_pos(pos)
{
	Resource* res = Resources::Get()->Get(id);
	if (res) {
		wxString fn = res->GetFileName().GetFullPath();
		if (!_image.LoadFile(fn, wxBITMAP_TYPE_ANY)) {
			wxLogWarning(_("Failed load image from file %s"), fn.c_str());

		}
	}
}

void NodeImage::Draw(wxDC& dc)
{
	if (_image.IsOk()) {
		dc.DrawBitmap(_image, _pos, true);
	}
	if (_selected) {
		dc.SetPen( wxPen( wxColor(255,0,0), 3));
		dc.SetBrush(*wxTRANSPARENT_BRUSH);
		dc.DrawRectangle(_pos, _image.GetSize());
	}
}

Node* NodeImage::find(int x, int y) {
	wxPoint r = _pos + _image.GetSize();
	return (x >= _pos.x && y >= _pos.y && x <= r.x && y <= r.y)
		? this : NULL;
}

wxXmlNode* NodeImage::serialize() const
{
	wxXmlNode *node=new wxXmlNode(wxXML_ELEMENT_NODE,wxT("image"));
	node->AddAttribute("x", wxString::Format(wxT("%i"),_pos.x));
	node->AddAttribute("y", wxString::Format(wxT("%i"),_pos.y));
	return node;
}


