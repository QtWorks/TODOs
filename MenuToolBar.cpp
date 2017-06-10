#include "MenuToolBar.h"

#include "TODOs.h"

MenuToolBar::MenuToolBar(QWidget *parent) : QToolBar(parent)
{
    setMovable(false);

    _add = addAction(QIcon(":/images/add"), "AddButton");
    _parameters = addAction(QIcon(":/images/params"), "SettingsButton");
    _quit = addAction(QIcon(":/images/quit"), "QuitButton");

    widgetForAction(_add)->setFixedSize(30, 30);
    widgetForAction(_parameters)->setFixedSize(30, 30);
    widgetForAction(_quit)->setFixedSize(30, 30);

    (qobject_cast<QToolButton*>(widgetForAction(_add)))->setAutoRaise(false);
    (qobject_cast<QToolButton*>(widgetForAction(_parameters)))->setAutoRaise(false);
    (qobject_cast<QToolButton*>(widgetForAction(_quit)))->setAutoRaise(false);

    connect(_add,        SIGNAL(triggered(bool)), this, SIGNAL(addPressed()));
    connect(_parameters, SIGNAL(triggered(bool)), this, SIGNAL(parametersPressed()));
    connect(_quit,       SIGNAL(triggered(bool)), qApp, SLOT(closeAllWindows()));
}

MenuToolBar::~MenuToolBar()
{

}

void MenuToolBar::updateIcons(const QString& color)
{
    _add->setIcon(TODOs::colorizeIcon(":/images/add", QColor(color)));
    _parameters->setIcon(TODOs::colorizeIcon(":/images/params", QColor(color)));
    _quit->setIcon(TODOs::colorizeIcon(":/images/quit", QColor(color)));
}
