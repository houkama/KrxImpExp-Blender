///////////////////////////////////////////////////////////////////////////////
// Name:        ColorFgTabNotebook.cpp
// Purpose:     Implementation of class wxCheckNotebook.
// Author:      Vitaly Baranov
// Created:     January 14, 2009
// Modified by:  
// Licence:     GNU General Public License
///////////////////////////////////////////////////////////////////////////////

#include "StdHeaders.h"

#include "CheckNotebook.h"
#include <wx/imaglist.h>

#include <checked_enabled.xpm>
#include <unchecked_enabled.xpm>



//////////////////////////////////////////////////////////////////////
// wxCheckColorTabNotebook

IMPLEMENT_CLASS(wxCheckNotebook, wxNotebook)

BEGIN_EVENT_TABLE(wxCheckNotebook, wxNotebook)
EVT_PAINT(wxCheckNotebook::OnPaint)
END_EVENT_TABLE()

// Ctor
wxCheckNotebook::wxCheckNotebook(wxWindow* parent, wxWindowID id, const wxPoint& pt, const wxSize& sz, long style):
wxNotebook(parent, id, pt, sz, style)
{
	LoadIcons();
}

// Load icons from graphical files; used by contructor only
void wxCheckNotebook::LoadIcons()
{
	//m_imageList = new wxImageList(16, 16, true);
	SetImageList(new wxImageList(16, 16, true));
	AssignImageList(GetImageList());
	GetImageList()->Add(wxIcon(unchecked_enabled_xpm));
	GetImageList()->Add(wxIcon(checked_enabled_xpm));
}

// Dtor
wxCheckNotebook::~wxCheckNotebook()
{
}

// Events
void wxCheckNotebook::OnPaint(wxPaintEvent& event)
{
	for(size_t i = 0; i < GetPageCount(); ++i)
	{
		SetPageImage(i, (i == GetSelection() ? 1 : 0));
	}
	event.Skip();
}

