#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QToolBar>
#include <QVBoxLayout>
#include <QAction>
#include <QIcon>
#include <QToolButton>
#include <QApplication>

class MenuToolBar : public QToolBar
{
    Q_OBJECT

private:
    Q_DISABLE_COPY(MenuToolBar)

    QAction* _add;
    QAction* _parameters;
    QAction* _quit;

public:
    MenuToolBar(QWidget *parent = 0);
    virtual ~MenuToolBar();

signals:
    void AddPressed();
    void ParametersPressed();

public slots:
    void PressAdd();
    void PressParameters();
};

#endif // MENUWIDGET_H
