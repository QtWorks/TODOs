#include "MenuToolBar.h"

MenuToolBar::MenuToolBar(QWidget *parent) : QToolBar(parent)
{
    setMovable(false);

    add = addAction(QIcon(":/images/add"), "AddButton");
    parameters = addAction(QIcon(":/images/params"), "SettingsButton");
    quit = addAction(QIcon(":/images/quit"), "QuitButton");

    widgetForAction(add)->setFixedSize(30, 30);
    widgetForAction(parameters)->setFixedSize(30, 30);
    widgetForAction(quit)->setFixedSize(30, 30);

    (static_cast<QToolButton*>(widgetForAction(add)))->setAutoRaise(false);
    (static_cast<QToolButton*>(widgetForAction(parameters)))->setAutoRaise(false);
    (static_cast<QToolButton*>(widgetForAction(quit)))->setAutoRaise(false);

    connect(add,        SIGNAL(triggered(bool)), this, SLOT(PressAdd()));
    connect(parameters, SIGNAL(triggered(bool)), this, SLOT(PressParameters()));
    connect(quit,       SIGNAL(triggered(bool)), qApp, SLOT(closeAllWindows()));
}

MenuToolBar::~MenuToolBar()
{

}

void MenuToolBar::PressAdd()
{
    emit AddPressed();
}

void MenuToolBar::PressParameters()
{
    emit ParametersPressed();
}
