#include <QApplication>
#include "AppCore"
#include "canvas.h"
//==================================================================================================
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!app_core::initializeApplication( "desktopWidget",
                                         "nayk",
                                         "nayk1982.github.io"
                                         )) {
        return 0;
    }

    Canvas canvas;
    canvas.show();

    a.setQuitOnLastWindowClosed(true);
    return a.exec();
}
//==================================================================================================
