#pragma once

#include <wx/dcbuffer.h>
#include <wx/dcgraph.h>
#include <wx/graphics.h>
#include <wx/overlay.h>


#include <vector>

class wxXmlNode;
class wxTreeCtrl;
class wxTreeItemId;

class Node
{
public:
	static Node* create(wxXmlNode* node);
	virtual ~Node() {}
	virtual void Draw(wxDC& dc) = 0;
	virtual wxXmlNode* serialize() const = 0;
	virtual void tree(wxTreeCtrl* ctrl, const wxTreeItemId &parent);
	virtual const char* ClassName() const = 0;
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
		return "List";
	}
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
		return "Circle";
	}
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
		return "Image";
	}
private:
	wxPoint _pos;
	const wxBitmap _image;
};


