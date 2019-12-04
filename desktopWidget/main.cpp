#include <QApplication>
#include "AppCore"

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


    a.setQuitOnLastWindowClosed(true);
    return a.exec();
}
//==================================================================================================
