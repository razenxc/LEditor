#pragma once
#include "wx/wx.h"
#include "wx/fileconf.h"
#include <fstream>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

	// --------
	// MenuBar

	// File
	void FileOpen(const wxCommandEvent& event);
	void FileSave(const wxCommandEvent& event);
	void FileSaveAs(const wxCommandEvent& event);
	void FileClose(const wxCommandEvent& event);
	void FileExit(const wxCommandEvent& event);

	// Help
	void HelpAbout(const wxCommandEvent& event);
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
};