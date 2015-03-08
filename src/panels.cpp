///////////////////////////////////////////////////////////////////////////////
// Name:        auidemo.cpp
// Purpose:     wxaui: wx advanced user interface - sample/test program
// Author:      Benjamin I. Williams
// Modified by:
// Created:     2005-10-03
// Copyright:   (C) Copyright 2005, Kirix Corporation, All Rights Reserved.
// Licence:     wxWindows Library Licence, Version 3.1
///////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "panels.h"

wxBEGIN_EVENT_TABLE(wxSizeReportCtrl, wxControl)
EVT_PAINT(wxSizeReportCtrl::OnPaint)
EVT_SIZE(wxSizeReportCtrl::OnSize)
EVT_ERASE_BACKGROUND(wxSizeReportCtrl::OnEraseBackground)
wxEND_EVENT_TABLE()


wxBEGIN_EVENT_TABLE(SettingsPanel, wxPanel)
EVT_SPINCTRL(ID_PaneBorderSize, SettingsPanel::OnPaneBorderSize)
EVT_SPINCTRL(ID_SashSize, SettingsPanel::OnSashSize)
EVT_SPINCTRL(ID_CaptionSize, SettingsPanel::OnCaptionSize)
EVT_BUTTON(ID_BackgroundColor, SettingsPanel::OnSetColor)
EVT_BUTTON(ID_SashColor, SettingsPanel::OnSetColor)
EVT_BUTTON(ID_InactiveCaptionColor, SettingsPanel::OnSetColor)
EVT_BUTTON(ID_InactiveCaptionGradientColor, SettingsPanel::OnSetColor)
EVT_BUTTON(ID_InactiveCaptionTextColor, SettingsPanel::OnSetColor)
EVT_BUTTON(ID_ActiveCaptionColor, SettingsPanel::OnSetColor)
EVT_BUTTON(ID_ActiveCaptionGradientColor, SettingsPanel::OnSetColor)
EVT_BUTTON(ID_ActiveCaptionTextColor, SettingsPanel::OnSetColor)
EVT_BUTTON(ID_BorderColor, SettingsPanel::OnSetColor)
EVT_BUTTON(ID_GripperColor, SettingsPanel::OnSetColor)
wxEND_EVENT_TABLE()