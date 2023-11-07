#pragma once
#include "wx/wx.h"
#include "wx/fileconf.h"
#include <fstream>

class MainFrame : public wxFrame
{
private:
	// ---------------
	// Text Area vars
	wxTextCtrl* textArea;

	// ----------------------
	// Files vars
	wxString defaultDir = wxEmptyString;
	wxString defaultFile = wxEmptyString;
	std::ofstream writeFile;
	std::ofstream readFile;
public:
	MainFrame(const wxString& title);

	// --------
	// MenuBar

	// File
	void FileOpen(wxCommandEvent& event);
	void FileSave(wxCommandEvent& event);
	void FileSaveAs(wxCommandEvent& event);
	void FileClose(wxCommandEvent& event);
	void FileExit(wxCommandEvent& event);

	// Help
	void HelpAbout(wxCommandEvent& event);

	// ----
	// App
	void Shortcuts(wxKeyEvent& event);
	void OnAppClose(wxCloseEvent& event);
};