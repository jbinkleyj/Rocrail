/* Rocrail - Model Railroad Software Copyright (C) 2002-2014 Rob Versluis, Rocrail.net This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/#ifndef __spldlg__#define __spldlg__/**@fileSubclass of SplDlgGen, which is generated by wxFormBuilder.*/#include "spldlggen.h"//// end generated include/** Implementing SplDlgGen */class SplDlg : public SplDlgGen{	protected:		// Handlers for SplDlgGen events.		void onCancel( wxCommandEvent& event );		void onHelp( wxCommandEvent& event );		void onOK( wxCommandEvent& event );	public:		/** Constructor */		SplDlg( wxWindow* parent );	//// end generated class members	};#endif // __spldlg__