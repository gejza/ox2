#include "node.h"

void NodeList::Draw(wxDC& dc)
{
	for (list_type::iterator i=_child.begin();i != _child.end();++i) {
		(*i)->Draw(dc);
	}
}

void NodeList::Add(Node* child)
{
	_child.push_back(child);
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

NodeImage::NodeImage(const wxPoint& pos, const wxBitmap& image) :
	_pos(pos), _image(image)
{
}

NodeImage::NodeImage(const wxPoint& pos, const wxString& path) :
	_pos(pos), _image(path, wxBITMAP_TYPE_ANY)
{
}

void NodeImage::Draw(wxDC& dc)
{
	dc.DrawBitmap(_image, _pos, true);
}


