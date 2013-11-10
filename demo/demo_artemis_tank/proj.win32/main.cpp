#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    EGLView eglView;
	
    eglView.init("Artemis Demo", 480.0f, 800.0f);
    return Application::getInstance()->run();
}
