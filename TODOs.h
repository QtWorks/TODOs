#ifndef TODOS_H
#define TODOS_H

#include <QApplication>

#include "MainWindow.h"

class TODOs : public QApplication
{
private:
    Q_DISABLE_COPY(TODOs)

    MainWindow w;

public:
    TODOs(int argc, char *argv[]);
    virtual ~TODOs();
};

#endif // TODOS_H
