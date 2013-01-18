#include "CubeApp.hpp"
#include "CubeDlg.hpp"

IMPLEMENT_APP(CubeDlgApp)

bool CubeDlgApp::OnInit()
{
    CubeDlg* dialog = new CubeDlg(NULL);
    SetTopWindow(dialog);
    dialog->Show(true);
    return true;
}

int CubeDlgApp::OnExit()
{
    return 0;
}
