#include "LEditor.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(LEditor);

bool LEditor::OnInit()
{
	wxSetEnv("LC_CTYPE", "en_US.UTF-8");
	MainFrame* mainFrame = new MainFrame("LEditor");
	mainFrame->SetClientSize(400, 600);
	mainFrame->Center();
	mainFrame->Show();

	return true;
}