/*
 Rocrail - Model Railroad Software

 Copyright (C) 2002-2014 Rob Versluis, Rocrail.net

 


 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#ifndef __waybilldlg__
#define __waybilldlg__

/**
@file
Subclass of waybillgen, which is generated by wxFormBuilder.
*/

#include "waybilldlggen.h"
#include "basenotebook.h"

#include "rocs/public/node.h"

/** Implementing waybillgen */
class WaybillDlg : public waybillgen
{
  iONode m_Props;
  bool   m_bSave;
  int    m_TabAlign;
  int    m_SetPage;

  void initLabels();
  bool evaluate();
  void initIndex();
  void initValues();
  void initLocationCombo();

public:
  /** Constructor */
  WaybillDlg( wxWindow* parent, iONode node, bool save=true );

  void onWaybillList( wxCommandEvent& event );
  void onNewWaybill( wxCommandEvent& event );
  void onDeleteWaybill( wxCommandEvent& event );
  void onApply( wxCommandEvent& event );
  void onCancel( wxCommandEvent& event );
  void OnCopy( wxCommandEvent& event );
  void onOK( wxCommandEvent& event );
  void onSetPage( wxCommandEvent& event );

  iONode getSelectedWaybill();
  bool isDelivered();

};

#endif // __waybilldlg__
