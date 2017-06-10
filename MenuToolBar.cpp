#include "MenuToolBar.h"

MenuToolBar::MenuToolBar(QWidget *parent) : QToolBar(parent)
{
    setMovable(false);

    _add = addAction(QIcon(":/images/add"), "AddButton");
    _parameters = addAction(QIcon(":/images/params"), "SettingsButton");
    _quit = addAction(QIcon(":/images/quit"), "QuitButton");

    widgetForAction(_add)->setFixedSize(30, 30);
    widgetForAction(_parameters)->setFixedSize(30, 30);
    widgetForAction(_quit)->setFixedSize(30, 30);

    (static_cast<QToolButton*>(widgetForAction(_add)))->setAutoRaise(false);
    (static_cast<QToolButton*>(widgetForAction(_parameters)))->setAutoRaise(false);
    (static_cast<QToolButton*>(widgetForAction(_quit)))->setAutoRaise(false);

    connect(_add,        SIGNAL(triggered(bool)), this, SLOT(pressAdd()));
    connect(_parameters, SIGNAL(triggered(bool)), this, SLOT(pressParameters()));
    connect(_quit,       SIGNAL(triggered(bool)), qApp, SLOT(closeAllWindows()));
}

MenuToolBar::~MenuToolBar()
{

}

void MenuToolBar::pressAdd()
{
    emit addPressed();
}

void MenuToolBar::pressParameters()
{
    emit parametersPressed();
}
