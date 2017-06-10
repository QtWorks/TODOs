#include "TODOs.h"

TODOs::TODOs(int argc, char *argv[]) : QApplication(argc, argv)
{
    setApplicationName("TODOs");
    setOrganizationName("xavi-b");

    w.show();

    connect(this, SIGNAL(lastWindowClosed()), &w, SLOT(writeData()));
    connect(this, SIGNAL(lastWindowClosed()), &w, SLOT(writeSettings()));
}

TODOs::~TODOs()
{

}
