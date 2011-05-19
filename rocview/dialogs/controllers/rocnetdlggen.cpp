///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "rocnetdlggen.h"

///////////////////////////////////////////////////////////////////////////

rocnetdlggen::rocnetdlggen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer4->AddGrowableCol( 1 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_labIID = new wxStaticText( this, wxID_ANY, wxT("IID"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labIID->Wrap( -1 );
	fgSizer4->Add( m_labIID, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_IID = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_IID, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer8->Add( fgSizer4, 0, wxEXPAND, 5 );
	
	wxString m_SublibChoices[] = { wxT("UDP"), wxT("Serial") };
	int m_SublibNChoices = sizeof( m_SublibChoices ) / sizeof( wxString );
	m_Sublib = new wxRadioBox( this, wxID_ANY, wxT("Type"), wxDefaultPosition, wxDefaultSize, m_SublibNChoices, m_SublibChoices, 1, wxRA_SPECIFY_ROWS );
	m_Sublib->SetSelection( 0 );
	bSizer8->Add( m_Sublib, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* m_OptionsBox;
	m_OptionsBox = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Options") ), wxVERTICAL );
	
	m_CRC = new wxCheckBox( this, wxID_ANY, wxT("CRC"), wxDefaultPosition, wxDefaultSize, 0 );
	m_OptionsBox->Add( m_CRC, 0, wxALL, 5 );
	
	bSizer8->Add( m_OptionsBox, 0, wxEXPAND|wxALL, 5 );
	
	bSizer7->Add( bSizer8, 1, 0, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer7->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer5->AddGrowableCol( 1 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_labDevice = new wxStaticText( this, wxID_ANY, wxT("Device"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labDevice->Wrap( -1 );
	fgSizer5->Add( m_labDevice, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_Device = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 160,-1 ), 0 );
	fgSizer5->Add( m_Device, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	bSizer9->Add( fgSizer5, 1, wxEXPAND, 5 );
	
	wxString m_BPSChoices[] = { wxT("9600"), wxT("19200"), wxT("38400"), wxT("57600"), wxT("115200") };
	int m_BPSNChoices = sizeof( m_BPSChoices ) / sizeof( wxString );
	m_BPS = new wxRadioBox( this, wxID_ANY, wxT("BPS"), wxDefaultPosition, wxDefaultSize, m_BPSNChoices, m_BPSChoices, 1, wxRA_SPECIFY_COLS );
	m_BPS->SetSelection( 1 );
	bSizer9->Add( m_BPS, 0, wxALL, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer9->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer6->AddGrowableCol( 1 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_labAddress = new wxStaticText( this, wxID_ANY, wxT("Address"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labAddress->Wrap( -1 );
	fgSizer6->Add( m_labAddress, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_Address = new wxTextCtrl( this, wxID_ANY, wxT("224.0.0.1"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( m_Address, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_labPort = new wxStaticText( this, wxID_ANY, wxT("Port"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labPort->Wrap( -1 );
	fgSizer6->Add( m_labPort, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_Port = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 65535, 4321 );
	fgSizer6->Add( m_Port, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer9->Add( fgSizer6, 0, wxEXPAND, 5 );
	
	bSizer7->Add( bSizer9, 1, 0, 5 );
	
	bSizer6->Add( bSizer7, 0, wxEXPAND, 5 );
	
	m_StdButton = new wxStdDialogButtonSizer();
	m_StdButtonOK = new wxButton( this, wxID_OK );
	m_StdButton->AddButton( m_StdButtonOK );
	m_StdButtonCancel = new wxButton( this, wxID_CANCEL );
	m_StdButton->AddButton( m_StdButtonCancel );
	m_StdButton->Realize();
	bSizer6->Add( m_StdButton, 1, wxEXPAND|wxALL, 5 );
	
	this->SetSizer( bSizer6 );
	this->Layout();
	bSizer6->Fit( this );
	
	// Connect Events
	m_Sublib->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( rocnetdlggen::OnSublib ), NULL, this );
	m_StdButtonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rocnetdlggen::OnCancel ), NULL, this );
	m_StdButtonOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rocnetdlggen::OnOK ), NULL, this );
}

rocnetdlggen::~rocnetdlggen()
{
	// Disconnect Events
	m_Sublib->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( rocnetdlggen::OnSublib ), NULL, this );
	m_StdButtonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rocnetdlggen::OnCancel ), NULL, this );
	m_StdButtonOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( rocnetdlggen::OnOK ), NULL, this );
}
