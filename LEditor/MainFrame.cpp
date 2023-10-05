#include "MainFrame.h"

// ------
// to-do
/*
1. add unicode
2. after second opening file clear first file ✅
*/

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	// ---------
	// Menu Bar
	wxMenuBar* menuBar = new wxMenuBar;

	// File
	wxMenu* fileMenu = new wxMenu;

	// File -> Open
	fileMenu->Append(wxID_OPEN, "Open");
	fileMenu->Bind(wxEVT_MENU, &MainFrame::FileOpen, this, wxID_OPEN);

	// File -> Save
	fileMenu->Append(wxID_SAVE, "Save");
	fileMenu->Bind(wxEVT_MENU, &MainFrame::FileSave, this, wxID_SAVE);

	// File -> Save As
	fileMenu->Append(wxID_SAVEAS, "Save as");
	fileMenu->Bind(wxEVT_MENU, &MainFrame::FileSaveAs, this, wxID_SAVEAS);

	// File -> Exit
	fileMenu->Append(wxID_EXIT, "Exit");
	fileMenu->Bind(wxEVT_MENU, &MainFrame::FileExit, this, wxID_EXIT);

	menuBar->Append(fileMenu, "File");
	SetMenuBar(menuBar);

	// ----------
	// Text Area
	textArea = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_AUTO_URL | wxTE_DONTWRAP);
	wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	textArea->SetFont(font);
	// ---------------------------
	// Status Bar (in bottom side)
	CreateStatusBar();
}

void MainFrame::FileOpen(const wxCommandEvent& event)
{
	wxLogStatus("File -> Open");
	wxFileDialog fileOpenDialog(this, "Select file", "", "");
	if (fileOpenDialog.ShowModal() == wxID_CANCEL)
		return;
	std::string line;
	fileOpenPath = fileOpenDialog.GetPath();
	std::ifstream readFile(fileOpenPath.ToStdString());
	if (!readFile.is_open())
	{
		wxMessageBox("Cannot open file: " + fileOpenPath, "Error", wxICON_ERROR);
	}
	textArea->Clear();
	if (readFile.is_open())
	{
		while (std::getline(readFile, line))
		{
			textArea->AppendText(line + "\n");
		}
		textArea->SetInsertionPoint(0);
		readFile.close();
	}
	wxLogStatus(fileOpenPath);
}

void MainFrame::FileSave(const wxCommandEvent& event)
{
	wxLogStatus("File -> Save");
}

void MainFrame::FileSaveAs(const wxCommandEvent& event)
{
	wxLogStatus("File -> Save As");
}

void MainFrame::FileExit(const wxCommandEvent& event)
{
	wxExit();
}