#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnBottomHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_QuitOnClose, true);
    setMinimumSize(300, 100);

    menu = new MenuToolBar(this);
    addToolBar(Qt::LeftToolBarArea, menu);

    layout = new QVBoxLayout;
    layout->setContentsMargins(4,0,4,0);
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    scroll = new QScrollArea(this);
    container = new QWidget(this);
    container->setLayout(layout);
    scroll->setWidget(container);
    scroll->setWidgetResizable(true);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setCentralWidget(scroll);

    statusBar = new StatusBar(this);
    statusBar->setSizeGripEnabled(true);
    setStatusBar(statusBar);

    parameters = new ParametersDialog(this);

    connect(menu, SIGNAL(AddPressed()),         this,       SLOT(AddGroupWidget()));
    connect(menu, SIGNAL(ParametersPressed()),  parameters, SLOT(open()));

    connect(statusBar, SIGNAL(Moved(QPoint)), this, SLOT(Move(QPoint)));

    connect(parameters, SIGNAL(ColorChanged()), this, SLOT(LoadStyleSheet()));

    ReadData();
    ReadSettings();

    LoadStyleSheet();
}

MainWindow::~MainWindow()
{

}

void MainWindow::LoadStyleSheet()
{
    setStyleSheet(parameters->Stylesheet());
}

void MainWindow::Move(const QPoint v)
{
    move(v);
}

void MainWindow::ShowElement(QWidget* w)
{
    qApp->processEvents();
    scroll->ensureWidgetVisible(w);
}

GroupWidget* MainWindow::AddGroupWidget()
{
    GroupWidget* group = new GroupWidget(this);
    connect(group, SIGNAL(EnsureElementIsVisible(QWidget*)), this, SLOT(ShowElement(QWidget*)));
    layout->addWidget(group);
    return group;
}

void MainWindow::ReadData()
{
    QFile file(parameters->DataPath()+"list.json");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString text = file.readAll();
        file.close();

        QJsonDocument json = QJsonDocument::fromJson(text.toUtf8());
        QJsonArray groups = json.object()["groups"].toArray();

        for(int i=0; i<groups.size(); i++)
        {
            GroupWidget* group = AddGroupWidget();
            group->SetTitle(groups[i].toObject()["title"].toString());

            QJsonArray elements = groups[i].toObject()["elements"].toArray();
            for(int j=0; j<elements.size(); j++)
            {
                ElementWidget* element = group->AddElement();
                element->SetText(elements[j].toObject()["text"].toString());
            }

            if(!groups[i].toObject()["expanded"].toBool())
                group->Expand();
        }
    }
    else
    {
        qWarning("Can't read saved Todos");
        qWarning((parameters->DataPath()+"list.json").toStdString().c_str());
    }
}

void MainWindow::WriteData()
{
    QFile file(parameters->DataPath()+"list.json");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QJsonObject root;
        QJsonArray groups;

        for(int i=0; i<layout->count(); i++)
        {
            QLayoutItem* item;
            if((item = layout->itemAt(i)) != NULL)
            {
                QJsonObject groupObject;
                QJsonArray elements;

                GroupWidget* group = static_cast<GroupWidget*>(item->widget());
                groupObject["title"] = group->Title();
                groupObject["expanded"] = group->IsExpanded();

                for(int j=0; j<group->Count(); j++)
                {
                    QJsonObject elementObject;
                    elementObject["text"] = group->GetElement(j)->Text();
                    elements.append(elementObject);
                }

                groupObject["elements"] = elements;

                groups.append(groupObject);
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
        qWarning((parameters->DataPath()+"list.json").toStdString().c_str());
    }
}

void MainWindow::ReadSettings()
{
    restoreGeometry(parameters->Settings()->value("MainWindow/Geometry", saveGeometry()).toByteArray());
}

void MainWindow::WriteSettings()
{
    parameters->Settings()->setValue("MainWindow/Geometry", saveGeometry());
}
