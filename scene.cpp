/////////////////////////////////////////////////////////////////////////////
// Name:        samples/drawing/drawing.cpp
// Purpose:     shows and tests wxDC features
// Author:      Robert Roebling
// Modified by:
// Created:     04/01/98
// Copyright:   (c) Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "scene.h"
#include "mainframe.h"

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    File_Quit = wxID_EXIT,
    File_About = wxID_ABOUT,

    MenuShow_First = wxID_HIGHEST,
    File_ShowDefault = MenuShow_First,
    File_ShowText,
    File_ShowLines,
    File_ShowBrushes,
    File_ShowPolygons,
    File_ShowMask,
    File_ShowMaskStretch,
    File_ShowOps,
    File_ShowRegions,
    File_ShowCircles,
    File_ShowSplines,
#if wxUSE_GRAPHICS_CONTEXT
    File_ShowAlpha,
    File_ShowGraphics,
#endif
    File_ShowGradients,
    MenuShow_Last = File_ShowGradients,

    File_Clip,
#if wxUSE_GRAPHICS_CONTEXT
    File_GraphicContext,
#endif
    File_Buffer,
    File_Copy,
    File_Save,

    MenuOption_First,

    MapMode_Text = MenuOption_First,
    MapMode_Lometric,
    MapMode_Twips,
    MapMode_Points,
    MapMode_Metric,

    UserScale_StretchHoriz,
    UserScale_ShrinkHoriz,
    UserScale_StretchVertic,
    UserScale_ShrinkVertic,
};
// ----------------------------------------------------------------------------
// Scene
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them.
wxBEGIN_EVENT_TABLE(Scene, wxScrolledWindow)
    EVT_PAINT  (Scene::OnPaint)
    EVT_MOTION (Scene::OnMouseMove)
    EVT_LEFT_DOWN (Scene::OnMouseDown)
    EVT_LEFT_UP (Scene::OnMouseUp)
wxEND_EVENT_TABLE()

#include "smile.xpm"

Scene::Scene(wxWindow *parent, MyFrame* owner)
: wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 300),
                           wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
{
    m_owner = owner;
    m_show = File_ShowDefault;
    m_smile_bmp = wxBitmap(smile_xpm);
    m_std_icon = wxArtProvider::GetIcon(wxART_INFORMATION);
    m_clip = false;
    m_rubberBand = false;
#if wxUSE_GRAPHICS_CONTEXT
    m_useContext = false;
#endif
    m_useBuffer = false;
}

void Scene::DrawTestBrushes(wxDC& dc)
{
    static const wxCoord WIDTH = 200;
    static const wxCoord HEIGHT = 80;

    wxCoord x = 10,
            y = 10;

    dc.SetBrush(*wxGREEN_BRUSH);
    dc.DrawRectangle(x, y, WIDTH, HEIGHT);
    dc.DrawText(wxT("Solid green"), x + 10, y + 10);

    y += HEIGHT;
    dc.SetBrush(wxBrush(*wxRED, wxBRUSHSTYLE_CROSSDIAG_HATCH));
    dc.DrawRectangle(x, y, WIDTH, HEIGHT);
    dc.DrawText(wxT("Diagonally hatched red"), x + 10, y + 10);

    y += HEIGHT;
    dc.SetBrush(wxBrush(*wxBLUE, wxBRUSHSTYLE_CROSS_HATCH));
    dc.DrawRectangle(x, y, WIDTH, HEIGHT);
    dc.DrawText(wxT("Cross hatched blue"), x + 10, y + 10);

    y += HEIGHT;
    dc.SetBrush(wxBrush(*wxCYAN, wxBRUSHSTYLE_VERTICAL_HATCH));
    dc.DrawRectangle(x, y, WIDTH, HEIGHT);
    dc.DrawText(wxT("Vertically hatched cyan"), x + 10, y + 10);

    y += HEIGHT;
    dc.SetBrush(wxBrush(*wxBLACK, wxBRUSHSTYLE_HORIZONTAL_HATCH));
    dc.DrawRectangle(x, y, WIDTH, HEIGHT);
    dc.DrawText(wxT("Horizontally hatched black"), x + 10, y + 10);

}

void Scene::DrawTestPoly(wxDC& dc)
{
    wxBrush brushHatch(*wxRED, wxBRUSHSTYLE_FDIAGONAL_HATCH);
    dc.SetBrush(brushHatch);

    wxPoint star[5];
    star[0] = wxPoint(100, 60);
    star[1] = wxPoint(60, 150);
    star[2] = wxPoint(160, 100);
    star[3] = wxPoint(40, 100);
    star[4] = wxPoint(140, 150);

    dc.DrawText(wxT("You should see two (irregular) stars below, the left one ")
                wxT("hatched"), 10, 10);
    dc.DrawText(wxT("except for the central region and the right ")
                wxT("one entirely hatched"), 10, 30);
    dc.DrawText(wxT("The third star only has a hatched outline"), 10, 50);

    dc.DrawPolygon(WXSIZEOF(star), star, 0, 30);
    dc.DrawPolygon(WXSIZEOF(star), star, 160, 30, wxWINDING_RULE);

    wxPoint star2[10];
    star2[0] = wxPoint(0, 100);
    star2[1] = wxPoint(-59, -81);
    star2[2] = wxPoint(95, 31);
    star2[3] = wxPoint(-95, 31);
    star2[4] = wxPoint(59, -81);
    star2[5] = wxPoint(0, 80);
    star2[6] = wxPoint(-47, -64);
    star2[7] = wxPoint(76, 24);
    star2[8] = wxPoint(-76, 24);
    star2[9] = wxPoint(47, -64);
    int count[2] = {5, 5};

    dc.DrawPolyPolygon(WXSIZEOF(count), count, star2, 450, 150);
}

void Scene::DrawTestLines( int x, int y, int width, wxDC &dc )
{
    dc.SetPen( wxPen( *wxBLACK, width ) );
    dc.SetBrush( *wxRED_BRUSH );
    dc.DrawText(wxString::Format(wxT("Testing lines of width %d"), width), x + 10, y - 10);
    dc.DrawRectangle( x+10, y+10, 100, 190 );

    dc.DrawText(wxT("Solid/dot/short dash/long dash/dot dash"), x + 150, y + 10);
    dc.SetPen( wxPen( *wxBLACK, width ) );
    dc.DrawLine( x+20, y+20, 100, y+20 );
    dc.SetPen( wxPen( *wxBLACK, width, wxPENSTYLE_DOT) );
    dc.DrawLine( x+20, y+30, 100, y+30 );
    dc.SetPen( wxPen( *wxBLACK, width, wxPENSTYLE_SHORT_DASH) );
    dc.DrawLine( x+20, y+40, 100, y+40 );
    dc.SetPen( wxPen( *wxBLACK, width, wxPENSTYLE_LONG_DASH) );
    dc.DrawLine( x+20, y+50, 100, y+50 );
    dc.SetPen( wxPen( *wxBLACK, width, wxPENSTYLE_DOT_DASH) );
    dc.DrawLine( x+20, y+60, 100, y+60 );

    dc.DrawText(wxT("Misc hatches"), x + 150, y + 70);
    dc.SetPen( wxPen( *wxBLACK, width, wxPENSTYLE_BDIAGONAL_HATCH) );
    dc.DrawLine( x+20, y+70, 100, y+70 );
    dc.SetPen( wxPen( *wxBLACK, width, wxPENSTYLE_CROSSDIAG_HATCH) );
    dc.DrawLine( x+20, y+80, 100, y+80 );
    dc.SetPen( wxPen( *wxBLACK, width, wxPENSTYLE_FDIAGONAL_HATCH) );
    dc.DrawLine( x+20, y+90, 100, y+90 );
    dc.SetPen( wxPen( *wxBLACK, width, wxPENSTYLE_CROSS_HATCH) );
    dc.DrawLine( x+20, y+100, 100, y+100 );
    dc.SetPen( wxPen( *wxBLACK, width, wxPENSTYLE_HORIZONTAL_HATCH) );
    dc.DrawLine( x+20, y+110, 100, y+110 );
    dc.SetPen( wxPen( *wxBLACK, width, wxPENSTYLE_VERTICAL_HATCH) );
    dc.DrawLine( x+20, y+120, 100, y+120 );

    dc.DrawText(wxT("User dash"), x + 150, y + 140);
    wxPen ud( *wxBLACK, width, wxPENSTYLE_USER_DASH );
    wxDash dash1[6];
    dash1[0] = 8;  // Long dash  <---------+
    dash1[1] = 2;  // Short gap            |
    dash1[2] = 3;  // Short dash           |
    dash1[3] = 2;  // Short gap            |
    dash1[4] = 3;  // Short dash           |
    dash1[5] = 2;  // Short gap and repeat +
    ud.SetDashes( 6, dash1 );
    dc.SetPen( ud );
    dc.DrawLine( x+20, y+140, 100, y+140 );
    dash1[0] = 5;  // Make first dash shorter
    ud.SetDashes( 6, dash1 );
    dc.SetPen( ud );
    dc.DrawLine( x+20, y+150, 100, y+150 );
    dash1[2] = 5;  // Make second dash longer
    ud.SetDashes( 6, dash1 );
    dc.SetPen( ud );
    dc.DrawLine( x+20, y+160, 100, y+160 );
    dash1[4] = 5;  // Make third dash longer
    ud.SetDashes( 6, dash1 );
    dc.SetPen( ud );
    dc.DrawLine( x+20, y+170, 100, y+170 );
}

void Scene::DrawBackground(wxDC& dc)
{
	int inc = 20;
	int width;
	int height;
	dc.GetSize(&width, &height);
	for (int x = 0; x < width; x += inc) {
		for (int y = 0; y < height; y += inc) {
			if ((x + y) / inc % 2) {
				dc.SetPen(*wxWHITE_PEN);
				dc.SetBrush(*wxWHITE_BRUSH);
			}
			else {
				dc.SetPen(*wxLIGHT_GREY_PEN);
				dc.SetBrush(*wxLIGHT_GREY_BRUSH);
			}
			dc.DrawRectangle(x, y, inc, inc);
		}
	}
}

void Scene::DrawDefault(wxDC& dc)
{
    // Draw circle centered at the origin, then flood fill it with a different
    // color. Done with a wxMemoryDC because Blit (used by generic
    // wxDoFloodFill) from a window that is being painted gives unpredictable
    // results on wxGTK
    {
        wxImage img(21, 21, false);
        img.Clear(1);
        wxBitmap bmp(img);
        {
            wxMemoryDC mdc(bmp);
            mdc.SetBrush(dc.GetBrush());
            mdc.SetPen(dc.GetPen());
            mdc.DrawCircle(10, 10, 10);
            wxColour c;
            if (mdc.GetPixel(11, 11, &c))
            {
                mdc.SetBrush(wxColour(128, 128, 0));
                mdc.FloodFill(11, 11, c, wxFLOOD_SURFACE);
            }
        }
        bmp.SetMask(new wxMask(bmp, wxColour(1, 1, 1)));
        dc.DrawBitmap(bmp, -10, -10, true);
    }

    dc.DrawCheckMark(5, 80, 15, 15);
    dc.DrawCheckMark(25, 80, 30, 30);
    dc.DrawCheckMark(60, 80, 60, 60);

    // this is the test for "blitting bitmap into DC damages selected brush" bug
    wxCoord rectSize = m_std_icon.GetWidth() + 10;
    wxCoord x = 100;
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush( *wxGREEN_BRUSH );
    dc.DrawRectangle(x, 10, rectSize, rectSize);
    dc.DrawBitmap(m_std_icon, x + 5, 15, true);
    x += rectSize + 10;
    dc.DrawRectangle(x, 10, rectSize, rectSize);
    dc.DrawIcon(m_std_icon, x + 5, 15);
    x += rectSize + 10;
    dc.DrawRectangle(x, 10, rectSize, rectSize);

    // test for "transparent" bitmap drawing (it intersects with the last
    // rectangle above)
    //dc.SetBrush( *wxTRANSPARENT_BRUSH );

    if (m_smile_bmp.IsOk())
        dc.DrawBitmap(m_smile_bmp, x + rectSize - 20, rectSize - 10, true);

    dc.SetBrush( *wxBLACK_BRUSH );
    dc.DrawRectangle( 0, 160, 1000, 300 );

    // draw lines
    wxBitmap bitmap(20,70);
    wxMemoryDC memdc;
    memdc.SelectObject( bitmap );
    memdc.SetBrush( *wxBLACK_BRUSH );
    memdc.SetPen( *wxWHITE_PEN );
    memdc.DrawRectangle(0,0,20,70);
    memdc.DrawLine( 10,0,10,70 );

    // to the right
    wxPen pen = *wxRED_PEN;
    memdc.SetPen(pen);
    memdc.DrawLine( 10, 5,10, 5 );
    memdc.DrawLine( 10,10,11,10 );
    memdc.DrawLine( 10,15,12,15 );
    memdc.DrawLine( 10,20,13,20 );

/*
    memdc.SetPen(*wxRED_PEN);
    memdc.DrawLine( 12, 5,12, 5 );
    memdc.DrawLine( 12,10,13,10 );
    memdc.DrawLine( 12,15,14,15 );
    memdc.DrawLine( 12,20,15,20 );
*/

    // same to the left
    memdc.DrawLine( 10,25,10,25 );
    memdc.DrawLine( 10,30, 9,30 );
    memdc.DrawLine( 10,35, 8,35 );
    memdc.DrawLine( 10,40, 7,40 );

    // XOR draw lines
    dc.SetPen(*wxWHITE_PEN);
    memdc.SetLogicalFunction( wxINVERT );
    memdc.SetPen( *wxWHITE_PEN );
    memdc.DrawLine( 10,50,10,50 );
    memdc.DrawLine( 10,55,11,55 );
    memdc.DrawLine( 10,60,12,60 );
    memdc.DrawLine( 10,65,13,65 );

    memdc.DrawLine( 12,50,12,50 );
    memdc.DrawLine( 12,55,13,55 );
    memdc.DrawLine( 12,60,14,60 );
    memdc.DrawLine( 12,65,15,65 );

    memdc.SelectObject( wxNullBitmap );
    dc.DrawBitmap( bitmap, 10, 170 );
    wxImage image = bitmap.ConvertToImage();
    image.Rescale( 60,210 );
    bitmap = wxBitmap(image);
    dc.DrawBitmap( bitmap, 50, 170 );

    // test the rectangle outline drawing - there should be one pixel between
    // the rect and the lines
    dc.SetPen(*wxWHITE_PEN);
    dc.SetBrush( *wxTRANSPARENT_BRUSH );
    dc.DrawRectangle(150, 170, 49, 29);
    dc.DrawRectangle(200, 170, 49, 29);
    dc.SetPen(*wxWHITE_PEN);
    dc.DrawLine(250, 210, 250, 170);
    dc.DrawLine(260, 200, 150, 200);

    // test the rectangle filled drawing - there should be one pixel between
    // the rect and the lines
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush( *wxWHITE_BRUSH );
    dc.DrawRectangle(300, 170, 49, 29);
    dc.DrawRectangle(350, 170, 49, 29);
    dc.SetPen(*wxWHITE_PEN);
    dc.DrawLine(400, 170, 400, 210);
    dc.DrawLine(300, 200, 410, 200);

    // a few more tests of this kind
    dc.SetPen(*wxRED_PEN);
    dc.SetBrush( *wxWHITE_BRUSH );
    dc.DrawRectangle(300, 220, 1, 1);
    dc.DrawRectangle(310, 220, 2, 2);
    dc.DrawRectangle(320, 220, 3, 3);
    dc.DrawRectangle(330, 220, 4, 4);

    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush( *wxWHITE_BRUSH );
    dc.DrawRectangle(300, 230, 1, 1);
    dc.DrawRectangle(310, 230, 2, 2);
    dc.DrawRectangle(320, 230, 3, 3);
    dc.DrawRectangle(330, 230, 4, 4);

    // and now for filled rect with outline
    dc.SetPen(*wxRED_PEN);
    dc.SetBrush( *wxWHITE_BRUSH );
    dc.DrawRectangle(500, 170, 49, 29);
    dc.DrawRectangle(550, 170, 49, 29);
    dc.SetPen(*wxWHITE_PEN);
    dc.DrawLine(600, 170, 600, 210);
    dc.DrawLine(500, 200, 610, 200);

    // test the rectangle outline drawing - there should be one pixel between
    // the rect and the lines
    dc.SetPen(*wxWHITE_PEN);
    dc.SetBrush( *wxTRANSPARENT_BRUSH );
    dc.DrawRoundedRectangle(150, 270, 49, 29, 6);
    dc.DrawRoundedRectangle(200, 270, 49, 29, 6);
    dc.SetPen(*wxWHITE_PEN);
    dc.DrawLine(250, 270, 250, 310);
    dc.DrawLine(150, 300, 260, 300);

    // test the rectangle filled drawing - there should be one pixel between
    // the rect and the lines
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush( *wxWHITE_BRUSH );
    dc.DrawRoundedRectangle(300, 270, 49, 29, 6);
    dc.DrawRoundedRectangle(350, 270, 49, 29, 6);
    dc.SetPen(*wxWHITE_PEN);
    dc.DrawLine(400, 270, 400, 310);
    dc.DrawLine(300, 300, 410, 300);

    // Added by JACS to demonstrate bizarre behaviour.
    // With a size of 70, we get a missing red RHS,
    // and the height is too small, so we get yellow
    // showing. With a size of 40, it draws as expected:
    // it just shows a white rectangle with red outline.
    int totalWidth = 70;
    int totalHeight = 70;
    wxBitmap bitmap2(totalWidth, totalHeight);

    wxMemoryDC memdc2;
    memdc2.SelectObject(bitmap2);

    memdc2.SetBackground(*wxYELLOW_BRUSH);
    memdc2.Clear();

    // Now draw a white rectangle with red outline. It should
    // entirely eclipse the yellow background.
    memdc2.SetPen(*wxRED_PEN);
    memdc2.SetBrush(*wxWHITE_BRUSH);

    memdc2.DrawRectangle(0, 0, totalWidth, totalHeight);

    memdc2.SetPen(wxNullPen);
    memdc2.SetBrush(wxNullBrush);
    memdc2.SelectObject(wxNullBitmap);

    dc.DrawBitmap(bitmap2, 500, 270);

    // Repeat, but draw directly on dc
    // Draw a yellow rectangle filling the bitmap

    x = 600; int y = 270;
    dc.SetPen(*wxYELLOW_PEN);
    dc.SetBrush(*wxYELLOW_BRUSH);
    dc.DrawRectangle(x, y, totalWidth, totalHeight);

    // Now draw a white rectangle with red outline. It should
    // entirely eclipse the yellow background.
    dc.SetPen(*wxRED_PEN);
    dc.SetBrush(*wxWHITE_BRUSH);

    dc.DrawRectangle(x, y, totalWidth, totalHeight);
}

void Scene::DrawText(wxDC& dc)
{
    // set underlined font for testing
    dc.SetFont( wxFont(12, wxMODERN, wxNORMAL, wxNORMAL, true) );
    dc.DrawText( wxT("This is text"), 110, 10 );
    dc.DrawRotatedText( wxT("That is text"), 20, 10, -45 );

    // use wxSWISS_FONT and not wxNORMAL_FONT as the latter can't be rotated
    // under Win9x (it is not TrueType)
    dc.SetFont( *wxSWISS_FONT );

    wxString text;
    dc.SetBackgroundMode(wxTRANSPARENT);

    for ( int n = -180; n < 180; n += 30 )
    {
        text.Printf(wxT("     %d rotated text"), n);
        dc.DrawRotatedText(text , 400, 400, n);
    }

    dc.SetFont( wxFont( 18, wxSWISS, wxNORMAL, wxNORMAL ) );

    dc.DrawText( wxT("This is Swiss 18pt text."), 110, 40 );

    wxCoord length;
    wxCoord height;
    wxCoord descent;
    dc.GetTextExtent( wxT("This is Swiss 18pt text."), &length, &height, &descent );
    text.Printf( wxT("Dimensions are length %d, height %d, descent %d"), length, height, descent );
    dc.DrawText( text, 110, 80 );

    text.Printf( wxT("CharHeight() returns: %d"), dc.GetCharHeight() );
    dc.DrawText( text, 110, 120 );

    dc.DrawRectangle( 100, 40, 4, height );

    // test the logical function effect
    wxCoord y = 150;
    dc.SetLogicalFunction(wxINVERT);
    // text drawing should ignore logical function
    dc.DrawText( wxT("There should be a text below"), 110, 150 );
    dc.DrawRectangle( 110, y, 100, height );

    y += height;
    dc.DrawText( wxT("Visible text"), 110, y );
    dc.DrawRectangle( 110, y, 100, height );
    dc.DrawText( wxT("Visible text"), 110, y );
    dc.DrawRectangle( 110, y, 100, height );
    dc.SetLogicalFunction(wxCOPY);

    y += height;
    dc.DrawRectangle( 110, y, 100, height );
    dc.DrawText( wxT("Another visible text"), 110, y );

    y += height;
    dc.DrawText("And\nmore\ntext on\nmultiple\nlines", 110, y);
}

static const struct
{
    const wxChar *name;
    wxRasterOperationMode rop;
} rasterOperations[] =
{
    { wxT("wxAND"),          wxAND           },
    { wxT("wxAND_INVERT"),   wxAND_INVERT    },
    { wxT("wxAND_REVERSE"),  wxAND_REVERSE   },
    { wxT("wxCLEAR"),        wxCLEAR         },
    { wxT("wxCOPY"),         wxCOPY          },
    { wxT("wxEQUIV"),        wxEQUIV         },
    { wxT("wxINVERT"),       wxINVERT        },
    { wxT("wxNAND"),         wxNAND          },
    { wxT("wxNO_OP"),        wxNO_OP         },
    { wxT("wxOR"),           wxOR            },
    { wxT("wxOR_INVERT"),    wxOR_INVERT     },
    { wxT("wxOR_REVERSE"),   wxOR_REVERSE    },
    { wxT("wxSET"),          wxSET           },
    { wxT("wxSRC_INVERT"),   wxSRC_INVERT    },
    { wxT("wxXOR"),          wxXOR           },
};

#if wxUSE_GRAPHICS_CONTEXT
#ifdef __WXGTK20__
void Scene::DrawAlpha(wxDC& WXUNUSED(dummyDC))
#else
void Scene::DrawAlpha(wxDC& dc)
#endif
{
#ifdef __WXGTK__
    wxGCDC dc( this );
    PrepareDC( dc );
#endif

    wxDouble margin = 20 ;
    wxDouble width = 180 ;
    wxDouble radius = 30 ;

    dc.SetPen( wxPen( wxColour( 128, 0, 0 ), 12 ));
    dc.SetBrush(*wxRED_BRUSH);

    wxRect r(margin,margin+width*0.66,width,width) ;

    dc.DrawRoundedRectangle( r.x, r.y, r.width, r.width, radius ) ;

    dc.SetPen( wxPen( wxColour( 0, 0, 128 ), 12));
    dc.SetBrush(*wxBLUE_BRUSH);

    r.Offset( width * 0.8 , - width * 0.66 ) ;

    dc.DrawRoundedRectangle( r.x, r.y, r.width, r.width, radius ) ;

    dc.SetPen( wxPen( wxColour( 128, 128, 0 ), 12));
    dc.SetBrush( wxBrush( wxColour( 192, 192, 0)));

    r.Offset( width * 0.8 , width *0.5 ) ;

    dc.DrawRoundedRectangle( r.x, r.y, r.width, r.width, radius ) ;

    dc.SetPen( *wxTRANSPARENT_PEN ) ;
    dc.SetBrush( wxBrush( wxColour(255,255,128,128) ) );
    dc.DrawRoundedRectangle( 0 , margin + width / 2 , width * 3 , 100 , radius) ;

    dc.SetTextForeground( wxColour(255,255,0,128) );
    dc.SetFont( wxFont( 40, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL ) );
    dc.DrawText( wxT("Hello!"), 120, 80 );
}

#endif

#if wxUSE_GRAPHICS_CONTEXT

const int BASE  = 80.0;
const int BASE2 = BASE/2;
const int BASE4 = BASE/4;

static inline double DegToRad(double deg) { return (deg * M_PI) / 180.0; }


// modeled along Robin Dunn's GraphicsContext.py sample

void Scene::DrawGraphics(wxGraphicsContext* gc)
{
    wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    gc->SetFont(font,*wxBLACK);

    // make a path that contains a circle and some lines, centered at 0,0
    wxGraphicsPath path = gc->CreatePath() ;
    path.AddCircle( 0, 0, BASE2 );
    path.MoveToPoint(0, -BASE2);
    path.AddLineToPoint(0, BASE2);
    path.MoveToPoint(-BASE2, 0);
    path.AddLineToPoint(BASE2, 0);
    path.CloseSubpath();
    path.AddRectangle(-BASE4, -BASE4/2, BASE2, BASE4);

    // Now use that path to demonstrate various capbilites of the grpahics context
    gc->PushState(); // save current translation/scale/other state
    gc->Translate(60, 75); // reposition the context origin

    gc->SetPen(wxPen("navy"));
    gc->SetBrush(wxBrush("pink"));

    for( int i = 0 ; i < 3 ; ++i )
    {
        wxString label;
        switch( i )
        {
            case 0 :
                label = "StrokePath";
                break;
            case 1 :
                label = "FillPath";
                break;
            case 2 :
                label = "DrawPath";
                break;
        }
        wxDouble w, h;
        gc->GetTextExtent(label, &w, &h, NULL, NULL);
        gc->DrawText(label, -w/2, -BASE2-h-4);
        switch( i )
        {
            case 0 :
                gc->StrokePath(path);
                break;
            case 1 :
                gc->FillPath(path);
                break;
            case 2 :
                gc->DrawPath(path);
                break;
        }
        gc->Translate(2*BASE, 0);
    }

    gc->PopState(); // restore saved state
    gc->PushState(); // save it again
    gc->Translate(60, 200); // offset to the lower part of the window

    gc->DrawText("Scale", 0, -BASE2);
    gc->Translate(0, 20);

    gc->SetBrush(wxBrush(wxColour(178,  34,  34, 128)));// 128 == half transparent
    for( int i = 0 ; i < 8 ; ++i )
    {
        gc->Scale(1.08, 1.08); // increase scale by 8%
        gc->Translate(5,5);
        gc->DrawPath(path);
    }

    gc->PopState(); // restore saved state
    gc->PushState(); // save it again
    gc->Translate(400, 200);

    gc->DrawText("Rotate", 0, -BASE2);

    // Move the origin over to the next location
    gc->Translate(0, 75);

    // draw our path again, rotating it about the central point,
    // and changing colors as we go
    for ( int angle = 0 ; angle < 360 ; angle += 30 )
    {
        gc->PushState(); // save this new current state so we can
        //  pop back to it at the end of the loop
        wxImage::RGBValue val = wxImage::HSVtoRGB(wxImage::HSVValue(float(angle)/360, 1, 1));
        gc->SetBrush(wxBrush(wxColour(val.red, val.green, val.blue, 64)));
        gc->SetPen(wxPen(wxColour(val.red, val.green, val.blue, 128)));

        // use translate to artfully reposition each drawn path
        gc->Translate(1.5 * BASE2 * cos(DegToRad(angle)),
                     1.5 * BASE2 * sin(DegToRad(angle)));

        // use Rotate to rotate the path
        gc->Rotate(DegToRad(angle));

        // now draw it
        gc->DrawPath(path);
        gc->PopState();
    }
    gc->PopState();

    gc->PushState();
    gc->Translate(60, 400);
    gc->DrawText("Scaled smiley inside a square", 0, 0);
    gc->DrawRectangle(BASE2, BASE2, 100, 100);
    gc->DrawBitmap(m_smile_bmp, BASE2, BASE2, 100, 100);
    gc->PopState();
}
#endif // wxUSE_GRAPHICS_CONTEXT

void Scene::DrawCircles(wxDC& dc)
{
    int x = 100,
        y = 100,
        r = 20;

    dc.SetPen( *wxRED_PEN );
    dc.SetBrush( *wxGREEN_BRUSH );

    dc.DrawText(wxT("Some circles"), 0, y);
    dc.DrawCircle(x, y, r);
    dc.DrawCircle(x + 2*r, y, r);
    dc.DrawCircle(x + 4*r, y, r);

    y += 2*r;
    dc.DrawText(wxT("And ellipses"), 0, y);
    dc.DrawEllipse(x - r, y, 2*r, r);
    dc.DrawEllipse(x + r, y, 2*r, r);
    dc.DrawEllipse(x + 3*r, y, 2*r, r);

    y += 2*r;
    dc.DrawText(wxT("And arcs"), 0, y);
    dc.DrawArc(x - r, y, x + r, y, x, y);
    dc.DrawArc(x + 4*r, y, x + 2*r, y, x + 3*r, y);
    dc.DrawArc(x + 5*r, y, x + 5*r, y, x + 6*r, y);

    y += 2*r;
    dc.DrawEllipticArc(x - r, y, 2*r, r, 0, 90);
    dc.DrawEllipticArc(x + r, y, 2*r, r, 90, 180);
    dc.DrawEllipticArc(x + 3*r, y, 2*r, r, 180, 270);
    dc.DrawEllipticArc(x + 5*r, y, 2*r, r, 270, 360);

    // same as above, just transparent brush

    dc.SetPen( *wxRED_PEN );
    dc.SetBrush( *wxTRANSPARENT_BRUSH );

    y += 2*r;
    dc.DrawText(wxT("Some circles"), 0, y);
    dc.DrawCircle(x, y, r);
    dc.DrawCircle(x + 2*r, y, r);
    dc.DrawCircle(x + 4*r, y, r);

    y += 2*r;
    dc.DrawText(wxT("And ellipses"), 0, y);
    dc.DrawEllipse(x - r, y, 2*r, r);
    dc.DrawEllipse(x + r, y, 2*r, r);
    dc.DrawEllipse(x + 3*r, y, 2*r, r);

    y += 2*r;
    dc.DrawText(wxT("And arcs"), 0, y);
    dc.DrawArc(x - r, y, x + r, y, x, y);
    dc.DrawArc(x + 4*r, y, x + 2*r, y, x + 3*r, y);
    dc.DrawArc(x + 5*r, y, x + 5*r, y, x + 6*r, y);

    y += 2*r;
    dc.DrawEllipticArc(x - r, y, 2*r, r, 0, 90);
    dc.DrawEllipticArc(x + r, y, 2*r, r, 90, 180);
    dc.DrawEllipticArc(x + 3*r, y, 2*r, r, 180, 270);
    dc.DrawEllipticArc(x + 5*r, y, 2*r, r, 270, 360);

}

void Scene::DrawSplines(wxDC& dc)
{
#if wxUSE_SPLINES
    dc.DrawText(wxT("Some splines"), 10, 5);

    // values are hardcoded rather than randomly generated
    // so the output can be compared between native
    // implementations on platforms with different random
    // generators

    const int R = 300;
    const wxPoint center( R + 20, R + 20 );
    const int angles[7] = { 0, 10, 33, 77, 13, 145, 90 };
    const int radii[5] = { 100 , 59, 85, 33, 90 };
    const int n = 200;
    wxPoint pts[n];

    // background spline calculation
    unsigned int radius_pos = 0;
    unsigned int angle_pos = 0;
    int angle = 0;
    for ( int i = 0; i < n; i++ )
    {
        angle += angles[ angle_pos ];
        int r = R * radii[ radius_pos ] / 100;
        pts[ i ].x = center.x + (wxCoord)( r * cos( M_PI * angle / 180.0) );
        pts[ i ].y = center.y + (wxCoord)( r * sin( M_PI * angle / 180.0) );

        angle_pos++;
        if ( angle_pos >= WXSIZEOF(angles) ) angle_pos = 0;

        radius_pos++;
        if ( radius_pos >= WXSIZEOF(radii) ) radius_pos = 0;
    }

    // background spline drawing
    dc.SetPen(*wxRED_PEN);
    dc.DrawSpline(WXSIZEOF(pts), pts);

    // less detailed spline calculation
    wxPoint letters[4][5];
    // w
    letters[0][0] = wxPoint( 0,1); //  O           O
    letters[0][1] = wxPoint( 1,3); //   *         *
    letters[0][2] = wxPoint( 2,2); //    *   O   *
    letters[0][3] = wxPoint( 3,3); //     * * * *
    letters[0][4] = wxPoint( 4,1); //      O   O
    // x1
    letters[1][0] = wxPoint( 5,1); //  O*O
    letters[1][1] = wxPoint( 6,1); //     *
    letters[1][2] = wxPoint( 7,2); //      O
    letters[1][3] = wxPoint( 8,3); //       *
    letters[1][4] = wxPoint( 9,3); //        O*O
    // x2
    letters[2][0] = wxPoint( 5,3); //        O*O
    letters[2][1] = wxPoint( 6,3); //       *
    letters[2][2] = wxPoint( 7,2); //      O
    letters[2][3] = wxPoint( 8,1); //     *
    letters[2][4] = wxPoint( 9,1); //  O*O
    // W
    letters[3][0] = wxPoint(10,0); //  O           O
    letters[3][1] = wxPoint(11,3); //   *         *
    letters[3][2] = wxPoint(12,1); //    *   O   *
    letters[3][3] = wxPoint(13,3); //     * * * *
    letters[3][4] = wxPoint(14,0); //      O   O

    const int dx = 2 * R / letters[3][4].x;
    const int h[4] = { -R/2, 0, R/4, R/2 };

    for ( int m = 0; m < 4; m++ )
    {
        for ( int n = 0; n < 5; n++ )
        {
            letters[m][n].x = center.x - R + letters[m][n].x * dx;
            letters[m][n].y = center.y + h[ letters[m][n].y ];
        }

        dc.SetPen( wxPen( *wxBLUE, 1, wxDOT) );
        dc.DrawLines(5, letters[m]);
        dc.SetPen( wxPen( *wxBLACK, 4) );
        dc.DrawSpline(5, letters[m]);
    }

#else
    dc.DrawText(wxT("Splines not supported."), 10, 5);
#endif
}

void Scene::DrawGradients(wxDC& dc)
{
    static const int TEXT_HEIGHT = 15;

    // LHS: linear
    wxRect r(10, 10, 50, 50);
    dc.DrawText(wxT("wxRIGHT"), r.x, r.y);
    r.Offset(0, TEXT_HEIGHT);
    dc.GradientFillLinear(r, *wxWHITE, *wxBLUE, wxRIGHT);

    r.Offset(0, r.height + 10);
    dc.DrawText(wxT("wxLEFT"), r.x, r.y);
    r.Offset(0, TEXT_HEIGHT);
    dc.GradientFillLinear(r, *wxWHITE, *wxBLUE, wxLEFT);

    r.Offset(0, r.height + 10);
    dc.DrawText(wxT("wxDOWN"), r.x, r.y);
    r.Offset(0, TEXT_HEIGHT);
    dc.GradientFillLinear(r, *wxWHITE, *wxBLUE, wxDOWN);

    r.Offset(0, r.height + 10);
    dc.DrawText(wxT("wxUP"), r.x, r.y);
    r.Offset(0, TEXT_HEIGHT);
    dc.GradientFillLinear(r, *wxWHITE, *wxBLUE, wxUP);

    wxRect  gfr = wxRect(r);

    // RHS: concentric
    r = wxRect(200, 10, 50, 50);
    dc.DrawText(wxT("Blue inside"), r.x, r.y);
    r.Offset(0, TEXT_HEIGHT);
    dc.GradientFillConcentric(r, *wxBLUE, *wxWHITE);

    r.Offset(0, r.height + 10);
    dc.DrawText(wxT("White inside"), r.x, r.y);
    r.Offset(0, TEXT_HEIGHT);
    dc.GradientFillConcentric(r, *wxWHITE, *wxBLUE);

    r.Offset(0, r.height + 10);
    dc.DrawText(wxT("Blue in top left corner"), r.x, r.y);
    r.Offset(0, TEXT_HEIGHT);
    dc.GradientFillConcentric(r, *wxBLUE, *wxWHITE, wxPoint(0, 0));

    r.Offset(0, r.height + 10);
    dc.DrawText(wxT("Blue in bottom right corner"), r.x, r.y);
    r.Offset(0, TEXT_HEIGHT);
    dc.GradientFillConcentric(r, *wxBLUE, *wxWHITE, wxPoint(r.width, r.height));

    // check that the area filled by the gradient is exactly the interior of
    // the rectangle
    r.x = 350;
    r.y = 30;
    dc.DrawText("The interior should be filled but", r.x, r.y);
    r.y += 15;
    dc.DrawText(" the red border should remain visible:", r.x, r.y);
    r.y += 15;

    r.width =
    r.height = 50;
    wxRect r2 = r;
    r2.x += 60;
    wxRect r3 = r;
    r3.y += 60;
    wxRect r4 = r2;
    r4.y += 60;
    dc.SetPen(*wxRED_PEN);
    dc.DrawRectangle(r);
    r.Deflate(1);
    dc.GradientFillLinear(r, *wxGREEN, *wxBLACK, wxNORTH);
    dc.DrawRectangle(r2);
    r2.Deflate(1);
    dc.GradientFillLinear(r2, *wxBLACK, *wxGREEN, wxSOUTH);
    dc.DrawRectangle(r3);
    r3.Deflate(1);
    dc.GradientFillLinear(r3, *wxGREEN, *wxBLACK, wxEAST);
    dc.DrawRectangle(r4);
    r4.Deflate(1);
    dc.GradientFillLinear(r4, *wxBLACK, *wxGREEN, wxWEST);

#if wxUSE_GRAPHICS_CONTEXT
    if (m_useContext)
    {
        wxGCDC                      &gdc = (wxGCDC&)dc;
        wxGraphicsContext           *gc = gdc.GetGraphicsContext();
        wxGraphicsPath              pth;
        wxGraphicsGradientStops     stops;

        gfr.Offset(0, gfr.height + 10);
        dc.DrawText(wxT("Linear Gradient with Stops"), gfr.x, gfr.y);
        gfr.Offset(0, TEXT_HEIGHT);

        stops = wxGraphicsGradientStops(*wxRED, *wxBLUE);
        stops.Add(wxColour(255,255,0), 0.33f);
        stops.Add(*wxGREEN, 0.67f);

        gc->SetBrush(gc->CreateLinearGradientBrush(gfr.x, gfr.y,
                                                   gfr.x + gfr.width, gfr.y + gfr.height,
                                                   stops));
        pth = gc->CreatePath();
        pth.MoveToPoint(gfr.x,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y+gfr.height);
        pth.AddLineToPoint(gfr.x,gfr.y+gfr.height);
        pth.CloseSubpath();
        gc->FillPath(pth);

        gfr.Offset(0, gfr.height + 10);
        dc.DrawText(wxT("Radial Gradient with Stops"), gfr.x, gfr.y);
        gfr.Offset(0, TEXT_HEIGHT);

        gc->SetBrush(gc->CreateRadialGradientBrush(gfr.x + gfr.width / 2,
                                                   gfr.y + gfr.height / 2,
                                                   gfr.x + gfr.width / 2,
                                                   gfr.y + gfr.height / 2,
                                                   gfr.width / 2,
                                                   stops));
        pth = gc->CreatePath();
        pth.MoveToPoint(gfr.x,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y+gfr.height);
        pth.AddLineToPoint(gfr.x,gfr.y+gfr.height);
        pth.CloseSubpath();
        gc->FillPath(pth);

        gfr.Offset(0, gfr.height + 10);
        dc.DrawText(wxT("Linear Gradient with Stops and Gaps"), gfr.x, gfr.y);
        gfr.Offset(0, TEXT_HEIGHT);

        stops = wxGraphicsGradientStops(*wxRED, *wxBLUE);
        stops.Add(wxColour(255,255,0), 0.33f);
        stops.Add(wxTransparentColour, 0.33f);
        stops.Add(wxTransparentColour, 0.67f);
        stops.Add(*wxGREEN, 0.67f);

        gc->SetBrush(gc->CreateLinearGradientBrush(gfr.x, gfr.y + gfr.height,
                                                   gfr.x + gfr.width, gfr.y,
                                                   stops));
        pth = gc->CreatePath();
        pth.MoveToPoint(gfr.x,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y+gfr.height);
        pth.AddLineToPoint(gfr.x,gfr.y+gfr.height);
        pth.CloseSubpath();
        gc->FillPath(pth);

        gfr.Offset(0, gfr.height + 10);
        dc.DrawText(wxT("Radial Gradient with Stops and Gaps"), gfr.x, gfr.y);
        gfr.Offset(0, TEXT_HEIGHT);

        gc->SetBrush(gc->CreateRadialGradientBrush(gfr.x + gfr.width / 2,
                                                   gfr.y + gfr.height / 2,
                                                   gfr.x + gfr.width / 2,
                                                   gfr.y + gfr.height / 2,
                                                   gfr.width / 2,
                                                   stops));
        pth = gc->CreatePath();
        pth.MoveToPoint(gfr.x,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y+gfr.height);
        pth.AddLineToPoint(gfr.x,gfr.y+gfr.height);
        pth.CloseSubpath();
        gc->FillPath(pth);

        gfr.Offset(0, gfr.height + 10);
        dc.DrawText(wxT("Gradients with Stops and Transparency"), gfr.x, gfr.y);
        gfr.Offset(0, TEXT_HEIGHT);

        stops = wxGraphicsGradientStops(*wxRED, wxTransparentColour);
        stops.Add(*wxRED, 0.33f);
        stops.Add(wxTransparentColour, 0.33f);
        stops.Add(wxTransparentColour, 0.67f);
        stops.Add(*wxBLUE, 0.67f);
        stops.Add(*wxBLUE, 1.0f);

        pth = gc->CreatePath();
        pth.MoveToPoint(gfr.x,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y);
        pth.AddLineToPoint(gfr.x + gfr.width,gfr.y+gfr.height);
        pth.AddLineToPoint(gfr.x,gfr.y+gfr.height);
        pth.CloseSubpath();

        gc->SetBrush(gc->CreateRadialGradientBrush(gfr.x + gfr.width / 2,
                                                   gfr.y + gfr.height / 2,
                                                   gfr.x + gfr.width / 2,
                                                   gfr.y + gfr.height / 2,
                                                   gfr.width / 2,
                                                   stops));
        gc->FillPath(pth);

        stops = wxGraphicsGradientStops(wxColour(255,0,0, 128), wxColour(0,0,255, 128));
        stops.Add(wxColour(255,255,0,128), 0.33f);
        stops.Add(wxColour(0,255,0,128), 0.67f);

        gc->SetBrush(gc->CreateLinearGradientBrush(gfr.x, gfr.y,
                                                   gfr.x + gfr.width, gfr.y,
                                                   stops));
        gc->FillPath(pth);
    }
#endif // wxUSE_GRAPHICS_CONTEXT
}

void Scene::DrawRegions(wxDC& dc)
{
    dc.DrawText(wxT("You should see a red rect partly covered by a cyan one ")
                wxT("on the left"), 10, 5);
    dc.DrawText(wxT("and 5 smileys from which 4 are partially clipped on the right"),
                10, 5 + dc.GetCharHeight());
    dc.DrawText(wxT("The second copy should be identical but right part of it ")
                wxT("should be offset by 10 pixels."),
                10, 5 + 2*dc.GetCharHeight());

    DrawRegionsHelper(dc, 10, true);
    DrawRegionsHelper(dc, 350, false);
}

void Scene::DrawRegionsHelper(wxDC& dc, wxCoord x, bool firstTime)
{
    wxCoord y = 100;

    dc.DestroyClippingRegion();
    dc.SetBrush( *wxWHITE_BRUSH );
    dc.SetPen( *wxTRANSPARENT_PEN );
    dc.DrawRectangle( x, y, 310, 310 );

    dc.SetClippingRegion( x + 10, y + 10, 100, 270 );

    dc.SetBrush( *wxRED_BRUSH );
    dc.DrawRectangle( x, y, 310, 310 );

    dc.SetClippingRegion( x + 10, y + 10, 100, 100 );

    dc.SetBrush( *wxCYAN_BRUSH );
    dc.DrawRectangle( x, y, 310, 310 );

    dc.DestroyClippingRegion();

    wxRegion region(x + 110, y + 20, 100, 270);
#if !defined(__WXMOTIF__)
    if ( !firstTime )
        region.Offset(10, 10);
#endif
    dc.SetDeviceClippingRegion(region);

    dc.SetBrush( *wxGREY_BRUSH );
    dc.DrawRectangle( x, y, 310, 310 );

    if (m_smile_bmp.IsOk())
    {
        dc.DrawBitmap( m_smile_bmp, x + 150, y + 150, true );
        dc.DrawBitmap( m_smile_bmp, x + 130, y + 10,  true );
        dc.DrawBitmap( m_smile_bmp, x + 130, y + 280, true );
        dc.DrawBitmap( m_smile_bmp, x + 100, y + 70,  true );
        dc.DrawBitmap( m_smile_bmp, x + 200, y + 70,  true );
    }
}

void Scene::OnPaint(wxPaintEvent &WXUNUSED(event))
{
    if ( m_useBuffer )
    {
        wxBufferedPaintDC bpdc(this);
        Draw(bpdc);
    }
    else
    {
        wxPaintDC pdc(this);
        Draw(pdc);
    }
}

void Scene::Draw(wxDC& pdc)
{
#if wxUSE_GRAPHICS_CONTEXT
    wxGCDC gdc;
    wxGraphicsRenderer* const renderer = wxGraphicsRenderer::
#if TEST_CAIRO_EVERYWHERE
        GetCairoRenderer()
#else
        GetDefaultRenderer()
#endif
        ;

    wxGraphicsContext* context;
    if ( wxPaintDC *paintdc = wxDynamicCast(&pdc, wxPaintDC) )
    {
        context = renderer->CreateContext(*paintdc);
    }
    else if ( wxMemoryDC *memdc = wxDynamicCast(&pdc, wxMemoryDC) )
    {
        context = renderer->CreateContext(*memdc);
    }
#if wxUSE_METAFILE && defined(wxMETAFILE_IS_ENH)
    else if ( wxMetafileDC *metadc = wxDynamicCast(&pdc, wxMetafileDC) )
    {
        context = renderer->CreateContext(*metadc);
    }
#endif
    else
    {
        wxFAIL_MSG( "Unknown wxDC kind" );
        return;
    }

    gdc.SetGraphicsContext(context);

    wxDC &dc = m_useContext ? (wxDC&) gdc : (wxDC&) pdc ;
#else
    wxDC &dc = pdc ;
#endif

    PrepareDC(dc);


    if ( m_clip )
        dc.SetClippingRegion(100, 100, 100, 100);

    dc.Clear();

	DrawBackground(dc);

    switch ( m_show )
    {
        case File_ShowDefault:
            DrawDefault(dc);
            break;

        case File_ShowCircles:
            DrawCircles(dc);
            break;

        case File_ShowSplines:
            DrawSplines(dc);
            break;

        case File_ShowRegions:
            DrawRegions(dc);
            break;

        case File_ShowText:
            DrawText(dc);
            break;

        case File_ShowLines:
            DrawTestLines( 0, 100, 0, dc );
            DrawTestLines( 0, 320, 1, dc );
            DrawTestLines( 0, 540, 2, dc );
            DrawTestLines( 0, 760, 6, dc );
            break;

        case File_ShowBrushes:
            DrawTestBrushes(dc);
            break;

        case File_ShowPolygons:
            DrawTestPoly(dc);
            break;

#if wxUSE_GRAPHICS_CONTEXT
        case File_ShowAlpha:
            DrawAlpha(dc);
            break;
        case File_ShowGraphics:
            DrawGraphics(gdc.GetGraphicsContext());
            break;
#endif

        case File_ShowGradients:
            DrawGradients(dc);
            break;

        default:
            break;
    }
}

void Scene::OnMouseMove(wxMouseEvent &event)
{
#if wxUSE_STATUSBAR
    {
        wxClientDC dc(this);
        PrepareDC(dc);

        wxPoint pos = event.GetPosition();
        long x = dc.DeviceToLogicalX( pos.x );
        long y = dc.DeviceToLogicalY( pos.y );
        wxString str;
        str.Printf( wxT("Current mouse position: %d,%d"), (int)x, (int)y );
		m_owner->SetStatusText(str);
    }

    if ( m_rubberBand )
    {
        int x,y, xx, yy ;
        event.GetPosition(&x,&y);
        CalcUnscrolledPosition( x, y, &xx, &yy );
        m_currentpoint = wxPoint( xx , yy ) ;
        wxRect newrect ( m_anchorpoint , m_currentpoint ) ;

        wxClientDC dc( this ) ;
        PrepareDC( dc ) ;

        wxDCOverlay overlaydc( m_overlay, &dc );
        overlaydc.Clear();
#ifdef __WXMAC__
        dc.SetPen( *wxGREY_PEN );
        dc.SetBrush( wxColour( 192,192,192,64 ) );
#else
        dc.SetPen( wxPen( *wxLIGHT_GREY, 2 ) );
        dc.SetBrush( *wxTRANSPARENT_BRUSH );
#endif
        dc.DrawRectangle( newrect );
    }
#else
    wxUnusedVar(event);
#endif // wxUSE_STATUSBAR
}

void Scene::OnMouseDown(wxMouseEvent &event)
{
    int x,y,xx,yy ;
    event.GetPosition(&x,&y);
    CalcUnscrolledPosition( x, y, &xx, &yy );
    m_anchorpoint = wxPoint( xx , yy ) ;
    m_currentpoint = m_anchorpoint ;
    m_rubberBand = true ;
    CaptureMouse() ;
}

void Scene::OnMouseUp(wxMouseEvent &event)
{
    if ( m_rubberBand )
    {
        ReleaseMouse();
        {
            wxClientDC dc( this );
            PrepareDC( dc );
            wxDCOverlay overlaydc( m_overlay, &dc );
            overlaydc.Clear();
        }
        m_overlay.Reset();
        m_rubberBand = false;

        wxPoint endpoint = CalcUnscrolledPosition(event.GetPosition());

        // Don't pop up the message box if nothing was actually selected.
        if ( endpoint != m_anchorpoint )
        {
            wxLogMessage("Selected rectangle from (%d, %d) to (%d, %d)",
                         m_anchorpoint.x, m_anchorpoint.y,
                         endpoint.x, endpoint.y);
        }
    }
	m_show = m_show == MenuShow_Last ? MenuShow_First : m_show + 1;
}

