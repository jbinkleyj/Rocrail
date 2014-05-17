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

#ifndef __rocnetdlg__
#define __rocnetdlg__

/**
@file
Subclass of rocnetdlggen, which is generated by wxFormBuilder.
*/

#include "rocnetdlggen.h"
#include "rocs/public/node.h"

/** Implementing rocnetdlggen */
class RocNetDlg : public rocnetdlggen
{
protected:
	// Handlers for rocnetdlggen events.
	void OnSublib( wxCommandEvent& event );
	void OnCancel( wxCommandEvent& event );
	void OnOK( wxCommandEvent& event );
	void OnHelp( wxCommandEvent& event );
	void onNodeListSelected( wxListEvent& event );
	
  void initLabels();
  void initValues();
  void initNodeList();
  void evaluate();
  iONode m_Props;
  const char* m_Devices;

public:
	/** Constructor */
	RocNetDlg( wxWindow* parent, iONode props, const char* devices=NULL );
};

#endif // __rocnetdlg__
