///////////////////////////////////////////////////////////////////////////// C++ code generated with wxFormBuilder (version Sep 12 2010)// http://www.wxformbuilder.org///// PLEASE DO "NOT" EDIT THIS FILE!///////////////////////////////////////////////////////////////////////////#ifndef __spldlggen__#define __spldlggen__#include <wx/string.h>#include <wx/stattext.h>#include <wx/gdicmn.h>#include <wx/font.h>#include <wx/colour.h>#include <wx/settings.h>#include <wx/textctrl.h>#include <wx/sizer.h>#include <wx/spinctrl.h>#include <wx/button.h>#include <wx/dialog.h>///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Class SplDlgGen///////////////////////////////////////////////////////////////////////////////class SplDlgGen : public wxDialog {	private:		protected:		wxStaticText* m_labIID;		wxTextCtrl* m_IID;		wxStaticText* m_labAddress;		wxSpinCtrl* m_Address;		wxStaticText* m_labNewAddress;		wxSpinCtrl* m_NewAddress;		wxStdDialogButtonSizer* m_sdbSizer1;		wxButton* m_sdbSizer1OK;		wxButton* m_sdbSizer1Cancel;		wxButton* m_sdbSizer1Help;				// Virtual event handlers, overide them in your derived class		virtual void onCancel( wxCommandEvent& event ) { event.Skip(); }		virtual void onHelp( wxCommandEvent& event ) { event.Skip(); }		virtual void onOK( wxCommandEvent& event ) { event.Skip(); }				public:				SplDlgGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SPL"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );		~SplDlgGen();	};#endif //__spldlggen__