#pragma once

#include <wx/dcbuffer.h>
#include <wx/dcgraph.h>
#include <wx/graphics.h>
#include <wx/overlay.h>

#include <vector>

class Node
{
public:
	virtual ~Node() {}
	virtual void Draw(wxDC& dc) = 0;
};

class NodeList : public Node
{
public:
	virtual void Draw(wxDC& dc);
	void Add(Node* child);
protected:
	typedef std::vector<Node*> list_type;
	list_type _child;
};

class NodeCircle : public Node
{
public:
	NodeCircle(int x, int y, int r);
	virtual void Draw(wxDC& dc);
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
private:
	wxPoint _pos;
	const wxBitmap _image;
};


