#include "MainFrame.h"

// ------
// to-do
/*
1. add unicode
2. after second opening file clear first file ✅
3. lock file reading after open
4. check for changes in files, which would write * if there are changes in the file
5. in MainFrame::File Close, create a message box with confirmation to close the file
*/

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	// ---------
	// Menu Bar
	wxMenuBar* menuBar = new wxMenuBar;

	// File
	wxMenu* fileMenu = new wxMenu;

	// File -> Open
	fileMenu->Append(wxID_OPEN, wxString::FromUTF8("\xF0\x9F\x93\x81 Open"));
	fileMenu->Bind(wxEVT_MENU, &MainFrame::FileOpen, this, wxID_OPEN);

	// File -> Save
	fileMenu->Append(wxID_SAVE, wxString::FromUTF8("\xE2\x9C\x93 Save"));
	fileMenu->Bind(wxEVT_MENU, &MainFrame::FileSave, this, wxID_SAVE);

	// File -> Save As
	fileMenu->Append(wxID_SAVEAS, wxString::FromUTF8("\xE2\x9C\x93 Save As"));
	fileMenu->Bind(wxEVT_MENU, &MainFrame::FileSaveAs, this, wxID_SAVEAS);

	// File -> Close
	fileMenu->Append(wxID_CLOSE, wxString::FromUTF8("\xE2\x9D\x8C Close"));
	fileMenu->Bind(wxEVT_MENU, &MainFrame::FileClose, this, wxID_CLOSE);

	fileMenu->AppendSeparator();

	// File -> Exit
	fileMenu->Append(wxID_EXIT, wxString::FromUTF8("\xE2\x9D\x8C Exit"));
	fileMenu->Bind(wxEVT_MENU, &MainFrame::FileExit, this, wxID_EXIT);

	menuBar->Append(fileMenu, wxString::FromUTF8("\xF0\x9F\x93\x81 File"));

	// Help
	wxMenu* helpMenu = new wxMenu;

	// Help -> About
	helpMenu->Append(wxID_ABOUT, wxString::FromUTF8("\xE2\x9D\x93 About"));
	helpMenu->Bind(wxEVT_MENU, &MainFrame::HelpAbout, this, wxID_ABOUT);

	menuBar->Append(helpMenu, wxString::FromUTF8("\xE2\x9D\x93 Help"));
	
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

// ---------
// Menu Bar

// --------------
// File Menu
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
		wxMessageBox("Cannot open file: " + defaultFile, "Error", wxICON_ERROR);
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
	wxLogStatus("Opened " + defaultFile);
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
	writeFile.write(contentToSave.utf8_str(), contentToSave.length());
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
	if (!readFile.is_open())
	{
		wxMessageBox("Cannot open file: " + defaultFile, "Error", wxICON_ERROR);
	}
	wxLogStatus("Saved as " + defaultFile);
}

void MainFrame::FileClose(const wxCommandEvent& event)
{
	wxLogStatus(defaultFile + " closed");
	defaultFile = wxEmptyString;
	defaultDir = wxEmptyString;
	textArea->Clear();
}

void MainFrame::FileExit(const wxCommandEvent& event)
{
	wxExit();
}

// ----------
// Help Menu

void MainFrame::HelpAbout(const wxCommandEvent& event)
{
	wxMessageBox("----------------------------------------------------\n| LEditor - Simple Text Editor\n| Razenxc Software 2023 © - github.com/razenxc/LEditor\n| Apache-2.0 license\n----------------------------------------------------", "About Program", wxOK | wxSTAY_ON_TOP | wxICON_NONE, textArea);
}