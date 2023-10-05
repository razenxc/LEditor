#pragma once
#include "wx/wx.h"
#include <fstream>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

	// --------
	// MenuBar
	void FileOpen(const wxCommandEvent& event);
	void FileSave(const wxCommandEvent& event);
	void FileSaveAs(const wxCommandEvent& event);
	void FileExit(const wxCommandEvent& event);
private:
	// ---------------
	// Text Area vars
	wxTextCtrl* textArea;

	// ----------------------
	// Open File Dialog vars
	wxString fileOpenPath;
	std::ifstream readFile;
};

