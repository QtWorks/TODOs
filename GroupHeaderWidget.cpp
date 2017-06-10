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

    connect(_title,  SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));

    connect(_title,  SIGNAL(clicked(bool)), this, SIGNAL(expandPressed()));
    connect(_add,    SIGNAL(clicked(bool)), this, SIGNAL(addPressed()));
}

GroupHeaderWidget::~GroupHeaderWidget()
{

}

void GroupHeaderWidget::showContextMenu(const QPoint& position)
{
    QMenu contextMenu(this);

    QAction deleteAllA("Delete All Elements", this);
    contextMenu.addAction(&deleteAllA);
    QAction deleteA("Delete Group", this);
    contextMenu.addAction(&deleteA);

    connect(&deleteAllA,    SIGNAL(triggered()), this, SIGNAL(deleteAllTriggered()));
    connect(&deleteA,       SIGNAL(triggered()), this, SIGNAL(deleteTriggered()));

    contextMenu.exec(_title->mapToGlobal(position));
}

QString GroupHeaderWidget::title() const
{
    return _title->text();
}

void GroupHeaderWidget::setTitle(const QString& title)
{
    _title->setText(title);
    _title->showButton();
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
        emit groupMoving(event->globalPos()-_startDragPos);
    }
}

void GroupHeaderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->globalPos() != _startDragPos)
    {
        setCursor(Qt::ArrowCursor);
        emit groupMoved(event->globalPos()-_startDragPos);
    }
}

HeaderWidget* GroupHeaderWidget::getHeaderWidget()
{
    return _title;
}
