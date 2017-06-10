#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnBottomHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_QuitOnClose, true);
    setMinimumSize(300, 100);

    _menu = new MenuToolBar(this);
    addToolBar(Qt::LeftToolBarArea, _menu);

    _layout = new QVBoxLayout;
    _layout->setContentsMargins(4,0,4,0);
    _layout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    _scroll = new QScrollArea(this);
    _container = new QWidget(this);
    _container->setLayout(_layout);
    _scroll->setWidget(_container);
    _scroll->setWidgetResizable(true);
    _scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setCentralWidget(_scroll);

    _statusBar = new StatusBar(this);
    _statusBar->setSizeGripEnabled(true);
    setStatusBar(_statusBar);

    _parameters = new ParametersDialog(this);

    connect(_menu, SIGNAL(addPressed()),         this,          SLOT(addGroupWidget()));
    connect(_menu, SIGNAL(parametersPressed()),  _parameters,   SLOT(open()));

    connect(_statusBar, SIGNAL(moved(QPoint)),   this, SLOT(moveWindow(QPoint)));

    connect(_parameters, SIGNAL(colorChanged()), this, SLOT(loadStyleSheet()));

    readData();
    readSettings();

    loadStyleSheet();
}

MainWindow::~MainWindow()
{

}

void MainWindow::loadStyleSheet()
{
    setStyleSheet(_parameters->stylesheet());
    _menu->updateIcons(_parameters->fontColor());

    for(int i=0; i<_layout->count(); i++)
    {
        QLayoutItem* item;
        if((item = _layout->itemAt(i)) != NULL)
        {
            GroupWidget* group = qobject_cast<GroupWidget*>(item->widget());

            if(group)
            {
                group->updateIcons(_parameters->fontColor());
                for(int j=0; j<group->count(); j++)
                {
                    group->getElement(j)->updateIcons(_parameters->fontColor());
                }
            }
        }
    }
}

void MainWindow::moveWindow(const QPoint v)
{
    move(v);
}

void MainWindow::showElement(QWidget* w)
{
    qApp->processEvents();
    _scroll->ensureWidgetVisible(w);
}

GroupWidget* MainWindow::addGroupWidget()
{
    GroupWidget* group = new GroupWidget(this);
    connect(group, SIGNAL(ensureElementIsVisible(QWidget*)), this, SLOT(showElement(QWidget*)));
    _layout->addWidget(group);
    group->getGroupHeaderWidget()->getHeaderWidget()->showLine();
    group->updateIcons(_parameters->fontColor());
    showElement(group);
    return group;
}

void MainWindow::readData()
{
    QFile file(_parameters->dataPath()+"list.json");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString text = file.readAll();
        file.close();

        QJsonDocument json = QJsonDocument::fromJson(text.toUtf8());
        QJsonArray groups = json.object()["groups"].toArray();

        for(int i=0; i<groups.size(); i++)
        {
            GroupWidget* group = addGroupWidget();
            group->setTitle(groups[i].toObject()["title"].toString());

            QJsonArray elements = groups[i].toObject()["elements"].toArray();
            for(int j=0; j<elements.size(); j++)
            {
                ElementWidget* element = group->addElement();
                element->setText(elements[j].toObject()["text"].toString());
            }

            if(!groups[i].toObject()["expanded"].toBool())
                group->expand();
        }
    }
    else
    {
        qWarning("Can't read saved Todos");
        qWarning((_parameters->dataPath()+"list.json").toStdString().c_str());
    }
}

void MainWindow::writeData()
{
    QFile file(_parameters->dataPath()+"list.json");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QJsonObject root;
        QJsonArray groups;

        for(int i=0; i<_layout->count(); i++)
        {
            QLayoutItem* item;
            if((item = _layout->itemAt(i)) != NULL)
            {
                QJsonObject groupObject;
                QJsonArray elements;

                GroupWidget* group = qobject_cast<GroupWidget*>(item->widget());

                if(group)
                {
                    groupObject["title"] = group->title();
                    groupObject["expanded"] = group->isExpanded();

                    for(int j=0; j<group->count(); j++)
                    {
                        QJsonObject elementObject;
                        elementObject["text"] = group->getElement(j)->text();
                        elements.append(elementObject);
                    }

                    groupObject["elements"] = elements;

                    groups.append(groupObject);
                }
            }
        }

        root["groups"] = groups;

        QJsonDocument json(root);
        file.write(json.toJson());
        file.close();
    }
    else
    {
        qWarning("Can't write saved Todos");
        qWarning((_parameters->dataPath()+"list.json").toStdString().c_str());
    }
}

void MainWindow::readSettings()
{
    setMinimumSize(250, 250);
    restoreGeometry(_parameters->settings()->value("MainWindow/Geometry", saveGeometry()).toByteArray());
}

void MainWindow::writeSettings()
{
    _parameters->settings()->setValue("MainWindow/Geometry", saveGeometry());
}
