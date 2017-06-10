#ifndef TODOS_H
#define TODOS_H

#include <QApplication>
#include <QPixmap>
#include <QBitmap>

#include "MainWindow.h"

class TODOs : public QApplication
{
private:
    Q_DISABLE_COPY(TODOs)

    MainWindow w;

public:
    TODOs(int argc, char *argv[]);
    virtual ~TODOs();
    static QIcon colorizeIcon(const QString& iconFileName, const QColor& color);

};

#endif // TODOS_H
