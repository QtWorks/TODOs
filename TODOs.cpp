#include "TODOs.h"

TODOs::TODOs(int argc, char *argv[]) : QApplication(argc, argv)
{
    setApplicationName("TODOs");
    setOrganizationName("xavi-b");

    w.show();

    connect(this, SIGNAL(lastWindowClosed()), &w, SLOT(WriteData()));
    connect(this, SIGNAL(lastWindowClosed()), &w, SLOT(WriteSettings()));
}

TODOs::~TODOs()
{

}
