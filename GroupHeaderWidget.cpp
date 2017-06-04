#include "GroupHeaderWidget.h"

GroupHeaderWidget::GroupHeaderWidget(QWidget *parent) : QWidget(parent)
{
    _title = new HeaderWidget("Group", this);
    _title->setFixedHeight(20);
    _title->setContextMenuPolicy(Qt::CustomContextMenu);

    _add = new QPushButton(QIcon(":/images/add"), "", this);
    _add->setFixedSize(20,20);

    _layout = new QHBoxLayout;
    _layout->setContentsMargins(0,0,0,0);
    _layout->setSpacing(0);
    _layout->addWidget(_title);
    _layout->addWidget(_add);
    _layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    setLayout(_layout);

    connect(_title,  SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));

    connect(_title,  SIGNAL(clicked(bool)), this, SLOT(PressExpand()));
    connect(_add,    SIGNAL(clicked(bool)), this, SLOT(PressAdd()));
}

GroupHeaderWidget::~GroupHeaderWidget()
{

}

void GroupHeaderWidget::PressExpand()
{
    emit ExpandPressed();
}

void GroupHeaderWidget::PressAdd()
{
    emit AddPressed();
}

void GroupHeaderWidget::TriggerDeleteAll()
{
    emit DeleteAllTriggered();
}

void GroupHeaderWidget::TriggerDelete()
{
    emit DeleteTriggered();
}

void GroupHeaderWidget::ShowContextMenu(const QPoint& position)
{
    QMenu contextMenu(this);

    QAction deleteAllA("Delete All Elements", this);
    contextMenu.addAction(&deleteAllA);
    QAction deleteA("Delete Group", this);
    contextMenu.addAction(&deleteA);

    connect(&deleteAllA,    SIGNAL(triggered()), this, SLOT(TriggerDeleteAll()));
    connect(&deleteA,       SIGNAL(triggered()), this, SLOT(TriggerDelete()));

    contextMenu.exec(_title->mapToGlobal(position));
}

QString GroupHeaderWidget::Title() const
{
    return _title->Text();
}

void GroupHeaderWidget::SetTitle(const QString& title)
{
    _title->SetText(title);
    _title->ShowButton();
}

void GroupHeaderWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        _startDragPos = event->globalPos();
    }
}

void GroupHeaderWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        setCursor(Qt::ClosedHandCursor);
        emit GroupMoving(event->globalPos()-_startDragPos);
    }
}

void GroupHeaderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->globalPos() != _startDragPos)
    {
        setCursor(Qt::ArrowCursor);
        emit GroupMoved(event->globalPos()-_startDragPos);
    }
}

HeaderWidget* GroupHeaderWidget::GetHeaderWidget()
{
    return _title;
}
