#include <wx/wx.h>
#include "main.h"
#include "main_page.h"


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MainPage* mainPage = new MainPage(); // G��wne okno bankomatu.
    mainPage->Show(true);
    return true;

}

