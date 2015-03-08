#pragma once

#include <wx/dcbuffer.h>
#include <wx/dcgraph.h>
#include <wx/graphics.h>
#include <wx/overlay.h>
#include <wx/treebase.h>
#include <wx/treectrl.h>
#include <wx/memory.h>
#include <wx/log.h>

#include <vector>

class wxXmlNode;
class wxTreeCtrl;
class wxTreeItemId;

class Node
{
public:
	static Node* create(wxXmlNode* node);
	Node() : _selected(false) {}
	virtual ~Node() {}
	virtual void Draw(wxDC& dc) = 0;
	virtual wxXmlNode* serialize() const = 0;
	virtual void tree(wxTreeCtrl* ctrl, const wxTreeItemId &parent);
	virtual const char* ClassName() const = 0;
	virtual Node* find(int x, int y) = 0;
	virtual void select(bool selected);
	virtual void move(const wxPoint& pos) {}
protected:
	wxTreeItemId _tree_id;
	bool _selected;

	friend class TreeNodePtr;
};


class TreeNodePtr : public wxTreeItemData
{
public:
	TreeNodePtr(Node* node) : _node(node) {
		wxLogTrace(wxTRACE_ResAlloc,"Create %s", _node->ClassName());
	}
	~TreeNodePtr() {
		_node->_tree_id = 0;
		wxLogTrace(wxTRACE_ResAlloc,"Destroy %s", _node->ClassName());
	}
	Node* get() {
		return _node;
	}
private:
	Node* _node;
};


class NodeList : public Node
{
public:
	virtual void Draw(wxDC& dc);
	void Add(Node* child);
	virtual wxXmlNode* serialize() const;
	virtual void load(wxXmlNode* node);
	virtual void tree(wxTreeCtrl* ctrl, const wxTreeItemId &parent);
	virtual const char* ClassName() const {
		return "list";
	}
	virtual Node* find(int x, int y);
protected:
	typedef std::vector<Node*> list_type;
	list_type _child;
};

class NodeCircle : public Node
{
public:
	NodeCircle(int x, int y, int r);
	virtual void Draw(wxDC& dc);
	virtual wxXmlNode* serialize() const;
	//virtual void load(wxXmlNode* node);
	virtual const char* ClassName() const {
		return "circle";
	}
	virtual Node* find(int x, int y);
private:
	int _x;
	int _y;
	int _r;
};

class NodeImage : public Node
{
public:
	NodeImage(const wxPoint& pos, const wxBitmap& image);
	NodeImage(const wxPoint& pos, const wxString& path);
	virtual void Draw(wxDC& dc);
	virtual wxXmlNode* serialize() const;
	//virtual void load(wxXmlNode* node);
	virtual const char* ClassName() const {
		return "image";
	}
	virtual Node* find(int x, int y);
	virtual void move(const wxPoint& pos) {
		_pos = pos;
	}
private:
	wxPoint _pos;
	wxBitmap _image;
};


