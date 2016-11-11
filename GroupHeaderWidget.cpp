#include "GroupHeaderWidget.h"

GroupHeaderWidget::GroupHeaderWidget(QWidget *parent) : QWidget(parent)
{
    title = new HeaderWidget("Group", this);
    title->setFixedHeight(20);
    title->setContextMenuPolicy(Qt::CustomContextMenu);

    add = new QPushButton(QIcon::fromTheme("list-add"), "", this);
    add->setFixedSize(20,20);

    layout = new QHBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(title);
    layout->addWidget(add);
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    setLayout(layout);

    connect(title,  SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));

    connect(title,  SIGNAL(clicked(bool)), this, SLOT(PressExpand()));
    connect(add,    SIGNAL(clicked(bool)), this, SLOT(PressAdd()));
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

    contextMenu.exec(title->mapToGlobal(position));
}

QString GroupHeaderWidget::Title() const
{
    return title->Text();
}

void GroupHeaderWidget::SetTitle(QString _title)
{
    title->SetText(_title);
}

void GroupHeaderWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        startDragPos = event->globalPos();
    }
}

void GroupHeaderWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        setCursor(Qt::ClosedHandCursor);
        emit GroupMoving(event->globalPos()-startDragPos);
    }
}

void GroupHeaderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->globalPos() != startDragPos)
    {
        setCursor(Qt::ArrowCursor);
        emit GroupMoved(event->globalPos()-startDragPos);
    }
}
