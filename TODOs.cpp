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

QIcon TODOs::colorizeIcon(const QString& iconFileName, const QColor& color)
{
    QPixmap px(iconFileName);
    QPixmap pxr(px.size());
    pxr.fill(color);
    pxr.setMask(px.createMaskFromColor(Qt::transparent));
    return QIcon(pxr);
}
