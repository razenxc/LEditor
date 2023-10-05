#include "LEditor.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(LEditor);

bool LEditor::OnInit()
{
	MainFrame* mainFrame = new MainFrame("LEditor");
	mainFrame->SetClientSize(400, 600);
	mainFrame->Center();
	mainFrame->Show();

	return true;
}