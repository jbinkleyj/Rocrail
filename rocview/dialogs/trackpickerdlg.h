/*
 Rocrail - Model Railroad Software

 Copyright (C) 2002-2014 Rob Versluis, Rocrail.net

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef __trackpickerdlg__
#define __trackpickerdlg__

#include "rocview/symbols/renderer.h"
#include "rocs/public/list.h"

/**
@file
Subclass of TrackPickerDlgGen, which is generated by wxFormBuilder.
*/

#include "trackpickerdlggen.h"

//// end generated include

/** Implementing TrackPickerDlgGen */
class TrackPickerDlg : public TrackPickerDlgGen
{
  iOList m_SymbolList;

  SymbolRenderer* m_Renderer;
  void onTrackCellLeftClick( wxGridEvent& event );
  void onPageChanged( wxListbookEvent& event );
  void onHelp( wxCommandEvent& event );
  void initSymbols();
  void initGrid();

	public:
		/** Constructor */
		TrackPickerDlg( wxWindow* parent );
	  void onClose( wxCloseEvent& event );
	
};

#endif // __trackpickerdlg__
