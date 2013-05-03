/* Rocrail - Model Railroad Software Copyright (C) 2002-2013 Rob Versluis, Rocrail.net Without an official permission commercial use is not permitted. Forking this project is not permitted. This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/#ifndef WX_PRECOMP    #include "wx/wx.h"#endif#include "throttledlg.h"#include "rocs/public/str.h"#include "rocs/public/trace.h"#include "rocs/public/system.h"#include "rocview/public/guiapp.h"#include "rocview/public/base.h"#include "rocview/dialogs/locseldlg.h"#include "rocrail/wrapper/public/Plan.h"#include "rocrail/wrapper/public/Loc.h"#include "rocrail/wrapper/public/Car.h"#include "rocrail/wrapper/public/SysCmd.h"#include "rocrail/wrapper/public/FunCmd.h"#include "rocrail/wrapper/public/FunDef.h"#include "rocrail/wrapper/public/DataReq.h"#include "rocview/wrapper/public/Gui.h"#include "rocview/xpm/nopict.xpm"ThrottleDlg::ThrottleDlg( wxWindow* parent, iOList list, iOMap map, const char* locid )  :ThrottleDlgGen( parent ){  this->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ThrottleDlg::onButton ) );  this->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( ThrottleDlg::onSlider ) );  this->Connect( wxEVT_DESTROY, wxWindowDestroyEventHandler( ThrottleDlg::onDestroy ) );  m_Stop->SetLabel( wxGetApp().getMsg( "stop" ) );  m_Break->SetLabel( wxGetApp().getMsg( "break" ) );  m_DlgList = list;  m_DlgMap  = map;  ListOp.add( m_DlgList, (obj)this );  m_Props = NULL;  m_iFnGroup = 0;  m_bDir = true;  SetTitle(wxGetApp().getMsg( "locctrl" ));  if( StrOp.len( wGui.getdirimagefwd(wxGetApp().getIni()) ) > 0 && StrOp.len( wGui.getdirimagerev(wxGetApp().getIni()) )) {    m_Dir->SetIcon( m_bDir ? getIcon(wGui.getdirimagefwd(wxGetApp().getIni())):getIcon(wGui.getdirimagerev(wxGetApp().getIni())) );  }  if( locid != NULL ) {    m_Props = wxGetApp().getFrame()->findLoc(locid);    if( m_Props != NULL ) {      updateImage();      setFLabels();      m_iSpeed = wLoc.getV(m_Props);      m_Speed->SetValue( wxString::Format(wxT("%d"), m_iSpeed) );      m_SpeedSlider->SetRange( 0, wLoc.getV_max(m_Props) );      m_SpeedSlider->SetValue( m_iSpeed, true );    }  }  else {    updateImage();  }}ThrottleDlg::~ThrottleDlg(){  // Disconnect Events  this->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ThrottleDlg::onButton ) );  this->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( ThrottleDlg::onSlider ) );  this->Disconnect( wxEVT_DESTROY, wxWindowDestroyEventHandler( ThrottleDlg::onDestroy ) );}void ThrottleDlg::onDestroy( wxWindowDestroyEvent& event ){  onClose((wxCloseEvent&)event);}void ThrottleDlg::modelEvent( iONode evt ) {  TraceOp.trc( "throttledlg", TRCLEVEL_INFO, __LINE__, 9999, "model event" );  if( m_Props == NULL )    return;  const char* id = wLoc.getid( evt );  if( !StrOp.equals( id, wLoc.getid(m_Props)))    return;  const char* et = NodeOp.getName( evt );  if( StrOp.equals( wLoc.name(), et ) ) {    /* update speed */    m_iSpeed = wLoc.getV(evt);    m_Speed->SetValue( wxString::Format(wxT("%d"), m_iSpeed) );    m_SpeedSlider->SetValue( m_iSpeed, true );    /* update direction */    m_bDir = wLoc.isdir( evt)?true:false;    m_Dir->SetLabel( m_bDir?_T(">>"):_T("<<") );    if( StrOp.len( wGui.getdirimagefwd(wxGetApp().getIni()) ) > 0 && StrOp.len( wGui.getdirimagerev(wxGetApp().getIni()) )) {      m_Dir->SetIcon( m_bDir ? getIcon(wGui.getdirimagefwd(wxGetApp().getIni())):getIcon(wGui.getdirimagerev(wxGetApp().getIni())) );    }    if( wxGetApp().getFrame()->isTooltip())      m_Dir->SetToolTip( m_bDir?wxGetApp().getMsg( "forwards" ):wxGetApp().getMsg( "reverse" ) );    /* update function "n" */    m_bFn = wLoc.isfn( evt)?true:false;    m_F0->setLED(m_bFn);    wLoc.setfn(m_Props, wLoc.isfn(evt));  }  else if( StrOp.equals( wFunCmd.name(), et ) ) {    setFX(evt);    setFLabels();    if( NodeOp.findAttr(evt, "f0") ) {      m_bFn = wFunCmd.isf0(evt )?true:false;      wLoc.setfn( m_Props, m_bFn?True:False );      m_F0->setLED(m_bFn);    }  }}bool ThrottleDlg::setFX( iONode node ) {  int fx = wLoc.getfx(m_Props);  wLoc.setfx(m_Props,      (NodeOp.getBool(node, "f1",  fx&0x0001?True:False)?0x0001:0x00) |      (NodeOp.getBool(node, "f2",  fx&0x0002?True:False)?0x0002:0x00) |      (NodeOp.getBool(node, "f3",  fx&0x0004?True:False)?0x0004:0x00) |      (NodeOp.getBool(node, "f4",  fx&0x0008?True:False)?0x0008:0x00) |      (NodeOp.getBool(node, "f5",  fx&0x0010?True:False)?0x0010:0x00) |      (NodeOp.getBool(node, "f6",  fx&0x0020?True:False)?0x0020:0x00) |      (NodeOp.getBool(node, "f7",  fx&0x0040?True:False)?0x0040:0x00) |      (NodeOp.getBool(node, "f8",  fx&0x0080?True:False)?0x0080:0x00) |      (NodeOp.getBool(node, "f9" ,  fx&0x0100?True:False)?0x0100:0x00) |      (NodeOp.getBool(node, "f10",  fx&0x0200?True:False)?0x0200:0x00) |      (NodeOp.getBool(node, "f11",  fx&0x0400?True:False)?0x0400:0x00) |      (NodeOp.getBool(node, "f12",  fx&0x0800?True:False)?0x0800:0x00) |      (NodeOp.getBool(node, "f13",  fx&0x1000?True:False)?0x1000:0x00) |      (NodeOp.getBool(node, "f14",  fx&0x2000?True:False)?0x2000:0x00) |      (NodeOp.getBool(node, "f15",  fx&0x4000?True:False)?0x4000:0x00) |      (NodeOp.getBool(node, "f16",  fx&0x8000?True:False)?0x8000:0x00) |      (NodeOp.getBool(node, "f17",  fx&0x010000?True:False)?0x010000:0x00) |      (NodeOp.getBool(node, "f18",  fx&0x020000?True:False)?0x020000:0x00) |      (NodeOp.getBool(node, "f19",  fx&0x040000?True:False)?0x040000:0x00) |      (NodeOp.getBool(node, "f20",  fx&0x080000?True:False)?0x080000:0x00) |      (NodeOp.getBool(node, "f21",  fx&0x100000?True:False)?0x100000:0x00) |      (NodeOp.getBool(node, "f22",  fx&0x200000?True:False)?0x200000:0x00) |      (NodeOp.getBool(node, "f23",  fx&0x400000?True:False)?0x400000:0x00) |      (NodeOp.getBool(node, "f24",  fx&0x800000?True:False)?0x800000:0x00) |      (NodeOp.getBool(node, "f25",  fx&0x01000000?True:False)?0x01000000:0x00) |      (NodeOp.getBool(node, "f26",  fx&0x02000000?True:False)?0x02000000:0x00) |      (NodeOp.getBool(node, "f27",  fx&0x04000000?True:False)?0x04000000:0x00) |      (NodeOp.getBool(node, "f28",  fx&0x08000000?True:False)?0x08000000:0x00)      );  return true;}void ThrottleDlg::onSlider(wxScrollEvent& event) {  TraceOp.trc( "throttledlg", TRCLEVEL_INFO, __LINE__, 9999, "slider %d", m_SpeedSlider->GetValue() );  m_iSpeed = m_SpeedSlider->GetValue();  speedCmd( event.GetEventType() != wxEVT_SCROLL_THUMBTRACK );}wxBitmap* ThrottleDlg::getIcon(const char* icon) {  wxBitmap* bitmap = NULL;  wxBitmapType bmptype = wxBITMAP_TYPE_XPM;  if( StrOp.endsWithi( icon, ".gif" ) )    bmptype = wxBITMAP_TYPE_GIF;  else if( StrOp.endsWithi( icon, ".png" ) )    bmptype = wxBITMAP_TYPE_PNG;  TraceOp.trc( "frame", TRCLEVEL_INFO, __LINE__, 9999, "get icon %s", icon );  const char* imagepath = wGui.getimagepath(wxGetApp().m_Ini);  static char pixpath[256];  StrOp.fmtb( pixpath, "%s%c%s", imagepath, SystemOp.getFileSeparator(), FileOp.ripPath( icon ) );  if( FileOp.exist(pixpath))    bitmap = new wxBitmap(wxString(pixpath,wxConvUTF8), bmptype);  else {    // request the image from server:    iONode node = NodeOp.inst( wDataReq.name(), NULL, ELEMENT_NODE );    wDataReq.setid( node, wLoc.getid(m_Props) );    wDataReq.setcmd( node, wDataReq.get );    wDataReq.settype( node, wDataReq.image );    wDataReq.setfilename( node, icon );    wxGetApp().sendToRocrail( node );  }  return bitmap;}void ThrottleDlg::setFLabels() {  LEDButton* m_F[15] = {m_F0,m_F1,m_F2,m_F3,m_F4,m_F5,m_F6,m_F7,m_F8,m_F9,m_F10,m_F11,m_F12,m_F13,m_F14};  TraceOp.trc( "throttledlg", TRCLEVEL_INFO, __LINE__, 9999, "setFLabels group=%d", m_iFnGroup );  m_F0->SetLabel( _T("lights") );  m_F0->SetIcon(NULL);  for( int i = 1; i < 15; i++ ) {    m_F[i]->SetLabel( wxString::Format(_T("F%d"), i + m_iFnGroup * 14) );    m_F[i]->SetIcon(NULL);  }  m_F0->setLED(wLoc.isfn( m_Props )?true:false);  int fx = wLoc.getfx(m_Props);  if( m_iFnGroup > 1 )    m_iFnGroup = 0;  fx = fx >> (m_iFnGroup * 14 );  for(int i = 0; i < 14; i++ ) {    m_F[i+1]->setLED ((fx & (0x0001 << i) )?true:false );  }  iONode fundef = wLoc.getfundef( m_Props );  while( fundef != NULL ) {    wxString fntxt = wxString(wFunDef.gettext( fundef ),wxConvUTF8);    int fn = wFunDef.getfn( fundef );    int idx = fn - m_iFnGroup*14;    if( fn == 0 ) {      if( wxGetApp().getFrame()->isTooltip())        m_F0->SetToolTip( fntxt );      if( wFunDef.geticon(fundef) != NULL && StrOp.len( wFunDef.geticon(fundef) ) > 0 ) {        m_F0->SetIcon(getIcon(wFunDef.geticon(fundef)));      }      else {        m_F0->SetIcon(NULL);        m_F0->SetLabel(fntxt);      }    }    else if( idx > 0 && idx < 15 ) {      TraceOp.trc( "throttledlg", TRCLEVEL_INFO, __LINE__, 9999, "funtion[%d] index=%d group=%d", fn, idx, m_iFnGroup );      if( wxGetApp().getFrame()->isTooltip() )        m_F[idx]->SetToolTip( fntxt );      if( wFunDef.geticon(fundef) != NULL && StrOp.len( wFunDef.geticon(fundef) ) > 0 ) {        m_F[idx]->SetIcon(getIcon(wFunDef.geticon(fundef)));      }      else {        m_F[idx]->SetIcon(NULL);        m_F[idx]->SetLabel(fntxt);      }    }    fundef = wLoc.nextfundef( m_Props, fundef );  }}#define MAXHEIGHT 48void ThrottleDlg::updateImage() {  iONode lc = m_Props;  if( lc != NULL && wLoc.getimage( lc ) != NULL && StrOp.len(wLoc.getimage( lc )) > 0 ) {    wxBitmapType bmptype = wxBITMAP_TYPE_XPM;    if( StrOp.endsWithi( wLoc.getimage( lc ), ".gif" ) )      bmptype = wxBITMAP_TYPE_GIF;    else if( StrOp.endsWithi( wLoc.getimage( lc ), ".png" ) )      bmptype = wxBITMAP_TYPE_PNG;    const char* imagepath = wGui.getimagepath(wxGetApp().getIni());    static char pixpath[256];    StrOp.fmtb( pixpath, "%s%c%s", imagepath, SystemOp.getFileSeparator(), FileOp.ripPath( wLoc.getimage( lc ) ) );    if( FileOp.exist(pixpath)) {      TraceOp.trc( "throttledlg", TRCLEVEL_INFO, __LINE__, 9999, "picture [%s]", pixpath );      wxImage img(wxString(pixpath,wxConvUTF8), bmptype);      if( img.GetHeight() > MAXHEIGHT ) {        int h = img.GetHeight();        int w = img.GetWidth();        float scale = (float)h / (float)MAXHEIGHT;        float width = (float)w / scale;        wxBitmap bmp(img.Scale((int)width, MAXHEIGHT, wxIMAGE_QUALITY_NORMAL));        m_LocoImage->SetBitmapLabel( bmp );      }      else {        m_LocoImage->SetBitmapLabel( wxBitmap(img) );      }    }    else {      TraceOp.trc( "throttledlg", TRCLEVEL_WARNING, __LINE__, 9999, "picture [%s] not found", pixpath );      m_LocoImage->SetBitmapLabel( wxBitmap(nopict_xpm) );    }    m_LocoImage->SetToolTip(wxString(wLoc.getdesc( lc ),wxConvUTF8));  }  else {    m_LocoImage->SetBitmapLabel( wxBitmap(nopict_xpm) );  }  m_LocoImage->Refresh();  GetSizer()->Fit(this);  GetSizer()->Layout();  SetTitle(wxGetApp().getMsg( "locctrl" ) + _T(" ") + wxString(wLoc.getid( lc ),wxConvUTF8) );}void ThrottleDlg::speedCmd(bool sendCmd){  if( !sendCmd || m_Props == NULL ) {    return;  }  TraceOp.trc( "throttledlg", TRCLEVEL_INFO, __LINE__, 9999, "speedCmd %d", m_iSpeed );  m_Speed->SetValue( wxString::Format(wxT("%d"), m_iSpeed) );  iONode cmd = NodeOp.inst( wLoc.name(), NULL, ELEMENT_NODE );  wLoc.setid( cmd, wLoc.getid( m_Props ) );  wLoc.setV( cmd, m_iSpeed );  wLoc.setfn( cmd, m_bFn?True:False );  wLoc.setdir( cmd, m_bDir?True:False );  wxGetApp().sendToRocrail( cmd );  cmd->base.del(cmd);}void ThrottleDlg::funCmd(int fidx, bool on){  if( m_Props == NULL )    return;  TraceOp.trc( "throttledlg", TRCLEVEL_INFO, __LINE__, 9999, "funCmd %d %s", fidx, on?"ON":"OFF" );  wLoc.setfx(m_Props,      (m_bFx[ 0]?0x0001:0x00) | (m_bFx[ 1]?0x0002:0x00) | (m_bFx[ 2]?0x0004:0x00) | (m_bFx[ 3]?0x0008:0x00) |      (m_bFx[ 4]?0x0010:0x00) | (m_bFx[ 5]?0x0020:0x00) | (m_bFx[ 6]?0x0040:0x00) | (m_bFx[ 7]?0x0080:0x00) |      (m_bFx[ 8]?0x0100:0x00) | (m_bFx[ 9]?0x0200:0x00) | (m_bFx[10]?0x0400:0x00) | (m_bFx[11]?0x0800:0x00) |      (m_bFx[12]?0x00001000:0x00) | (m_bFx[13]?0x00002000:0x00) | (m_bFx[14]?0x00004000:0x00) | (m_bFx[15]?0x00008000:0x00) |      (m_bFx[16]?0x00010000:0x00) | (m_bFx[17]?0x00020000:0x00) | (m_bFx[18]?0x00040000:0x00) | (m_bFx[19]?0x00080000:0x00) |      (m_bFx[20]?0x00100000:0x00) | (m_bFx[21]?0x00200000:0x00) | (m_bFx[22]?0x00400000:0x00) | (m_bFx[23]?0x00800000:0x00) |      (m_bFx[24]?0x01000000:0x00) | (m_bFx[25]?0x02000000:0x00) | (m_bFx[26]?0x04000000:0x00) | (m_bFx[27]?0x08000000:0x00)      );  iONode cmd = NodeOp.inst( wFunCmd.name(), NULL, ELEMENT_NODE );  wFunCmd.setfnchanged ( cmd, fidx );  wFunCmd.setid ( cmd, wLoc.getid( m_Props ) );  wFunCmd.setgroup ( cmd, fidx==-1?0:fidx/4 + 1 );  wFunCmd.setfncnt ( cmd, wLoc.getfncnt( m_Props ) );  wFunCmd.setf0 ( cmd, m_bFn?True:False );  wFunCmd.setf1 ( cmd, m_bFx[ 0]?True:False );  wFunCmd.setf2 ( cmd, m_bFx[ 1]?True:False );  wFunCmd.setf3 ( cmd, m_bFx[ 2]?True:False );  wFunCmd.setf4 ( cmd, m_bFx[ 3]?True:False );  wFunCmd.setf5 ( cmd, m_bFx[ 4]?True:False );  wFunCmd.setf6 ( cmd, m_bFx[ 5]?True:False );  wFunCmd.setf7 ( cmd, m_bFx[ 6]?True:False );  wFunCmd.setf8 ( cmd, m_bFx[ 7]?True:False );  wFunCmd.setf9 ( cmd, m_bFx[ 8]?True:False );  wFunCmd.setf10( cmd, m_bFx[ 9]?True:False );  wFunCmd.setf11( cmd, m_bFx[10]?True:False );  wFunCmd.setf12( cmd, m_bFx[11]?True:False );  wFunCmd.setf13( cmd, m_bFx[12]?True:False );  wFunCmd.setf14( cmd, m_bFx[13]?True:False );  wFunCmd.setf15( cmd, m_bFx[14]?True:False );  wFunCmd.setf16( cmd, m_bFx[15]?True:False );  wFunCmd.setf17( cmd, m_bFx[16]?True:False );  wFunCmd.setf18( cmd, m_bFx[17]?True:False );  wFunCmd.setf19( cmd, m_bFx[18]?True:False );  wFunCmd.setf20( cmd, m_bFx[19]?True:False );  wFunCmd.setf21( cmd, m_bFx[20]?True:False );  wFunCmd.setf22( cmd, m_bFx[21]?True:False );  wFunCmd.setf23( cmd, m_bFx[22]?True:False );  wFunCmd.setf24( cmd, m_bFx[23]?True:False );  wFunCmd.setf25( cmd, m_bFx[24]?True:False );  wFunCmd.setf26( cmd, m_bFx[25]?True:False );  wFunCmd.setf27( cmd, m_bFx[26]?True:False );  wFunCmd.setf28( cmd, m_bFx[27]?True:False );  wxGetApp().sendToRocrail( cmd );  cmd->base.del(cmd);}void ThrottleDlg::onButton(wxCommandEvent& event) {  TraceOp.trc( "throttledlg", TRCLEVEL_INFO, __LINE__, 9999, "OnButton event..." );  if ( event.GetEventObject() == m_LocoImage ) {    TraceOp.trc( "throttledlg", TRCLEVEL_INFO, __LINE__, 9999, "LocoImage" );    LocSelDlg*  dlg = new LocSelDlg(this, NULL, false );    if( wxID_OK == dlg->ShowModal() ) {      m_Props = dlg->getProperties();      if( m_Props != NULL ) {        m_iFnGroup = 0;        updateImage();        setFLabels();        m_iSpeed = wLoc.getV(m_Props);        m_Speed->SetValue( wxString::Format(wxT("%d"), m_iSpeed) );        m_SpeedSlider->SetRange( 0, wLoc.getV_max(m_Props) );        m_SpeedSlider->SetValue( m_iSpeed, true );      }    }    dlg->Destroy();    Raise();  }  else if ( event.GetEventObject() == m_Dir ) {    TraceOp.trc( "throttledlg", TRCLEVEL_INFO, __LINE__, 9999, "Direction" );    m_bDir = ! m_bDir;    m_Dir->SetLabel( m_bDir?_T(">>"):_T("<<") );    if( StrOp.len( wGui.getdirimagefwd(wxGetApp().getIni()) ) > 0 && StrOp.len( wGui.getdirimagerev(wxGetApp().getIni()) )) {      m_Dir->SetIcon( m_bDir ? getIcon(wGui.getdirimagefwd(wxGetApp().getIni())):getIcon(wGui.getdirimagerev(wxGetApp().getIni())) );    }    if( wxGetApp().getFrame()->isTooltip())      m_Dir->SetToolTip( m_bDir?wxGetApp().getMsg( "forwards" ):wxGetApp().getMsg( "reverse" ) );    if( wGui.isresetspeeddir(wxGetApp().getIni()) ) {      m_iSpeed = 0;      m_SpeedSlider->SetValue( m_iSpeed, true );    }    speedCmd(true);  }  else if ( event.GetEventObject() == m_Stop ) {    TraceOp.trc( "throttledlg", TRCLEVEL_INFO, __LINE__, 9999, "Stop" );    m_iSpeed = 0;    m_SpeedSlider->SetValue( m_iSpeed, true );    speedCmd(true);  }  else if ( event.GetEventObject() == m_Break ) {    TraceOp.trc( "throttledlg", TRCLEVEL_INFO, __LINE__, 9999, "Break" );    iONode cmd = NodeOp.inst( wSysCmd.name(), NULL, ELEMENT_NODE );    wLoc.setcmd( cmd, wSysCmd.stop );    wSysCmd.setinformall(cmd, True);    wxGetApp().sendToRocrail( cmd );    cmd->base.del(cmd);  }  else if ( event.GetEventObject() == m_FG ) {    TraceOp.trc( "throttledlg", TRCLEVEL_INFO, __LINE__, 9999, "FG" );    m_iFnGroup++;    if( m_iFnGroup > 1 )      m_iFnGroup = 0;    setFLabels();  }  else {    LEDButton* m_F[15] = {m_F0,m_F1,m_F2,m_F3,m_F4,m_F5,m_F6,m_F7,m_F8,m_F9,m_F10,m_F11,m_F12,m_F13,m_F14};    for( int i = 0; i < 15; i++ ) {      if( event.GetEventObject() == m_F[i] ) {        TraceOp.trc( "throttledlg", TRCLEVEL_INFO, __LINE__, 9999, "F%d", i );        m_F[i]->setLED(!m_F[i]->ON);        funCmd(i+m_iFnGroup*14, m_F[i]->ON);        break;      }    }  }}void ThrottleDlg::onClose( wxCloseEvent& event ) {  ListOp.removeObj( m_DlgList, (obj)this );  if( m_Props == NULL ) {    Destroy();    return;  }  int x,y;  GetPosition(&x,&y);  const char* LocID = wLoc.getid(m_Props);  TraceOp.trc( "throttledlg", TRCLEVEL_INFO, __LINE__, 9999, "position [%d,%d] for [%s]", x, y, LocID );  if( StrOp.len(LocID) > 0 ) {    char* pos = (char*)MapOp.get(m_DlgMap, LocID);    if( pos != NULL ) {      TraceOp.trc( "throttledlg", TRCLEVEL_INFO, __LINE__, 9999, "remove previous position [%s] for [%s]", pos, LocID );      StrOp.free(pos);      MapOp.remove(m_DlgMap, LocID);    }    pos = StrOp.fmt("%d,%d", x, y);    MapOp.put( m_DlgMap, LocID, (obj)pos );  }  Destroy();}