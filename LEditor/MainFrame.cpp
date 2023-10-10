#include "MainFrame.h"

// ------
// to-do
/*
1. add unicode
2. after second opening file clear first file ✅
3. stop reading a file only after it is closed or the application is closed
4. check for changes in files, which would write * if there are changes in the file
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
	defaultFile = fileOpenDialog.GetPath();
	defaultDir = fileOpenDialog.GetDirectory();
	std::ifstream readFile(defaultFile.ToStdString());

	if (!readFile.is_open())
	{
		wxMessageBox("Cannot open file: " + defaultDir, "Error", wxICON_ERROR);
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
	wxLogStatus(defaultFile);
}

void MainFrame::FileSave(const wxCommandEvent& event)
{
	wxLogStatus("File -> Save");
	if (defaultDir.IsEmpty())
	{
		FileSaveAs(event);
	}
	std::ofstream writeFile(defaultFile.ToStdString());
	wxString contentToSave = textArea->GetValue();
	writeFile << contentToSave.ToStdString();
	writeFile.close();
	wxLogStatus("Saved as " + defaultFile);
}

void MainFrame::FileSaveAs(const wxCommandEvent& event)
{
	wxLogStatus("File -> Save As");
	wxFileDialog fileSaveDialog(this, "Select save path", "", "", "", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (fileSaveDialog.ShowModal() == wxID_CANCEL)
		return;

	defaultFile = fileSaveDialog.GetPath();
	defaultDir = fileSaveDialog.GetDirectory();

	std::ofstream writeFile(defaultFile.ToStdString());

	if (writeFile.is_open())
	{
		wxString contentToSave = textArea->GetValue();
		writeFile << contentToSave.ToStdString();
		writeFile.close();
	}
	wxLogStatus("Saved as " + defaultFile);
}

void MainFrame::FileExit(const wxCommandEvent& event)
{
	wxExit();
}