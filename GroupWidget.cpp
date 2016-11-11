#include "GroupWidget.h"

GroupWidget::GroupWidget(QWidget *parent) : QWidget(parent), isExpanded(true)
{
    setMinimumHeight(20+2);
    setFixedHeight(20+2);

    header = new GroupHeaderWidget(this);
    header->setFixedHeight(20);

    container = new QWidget(this);

    cLayout = new QVBoxLayout;
    cLayout->setContentsMargins(0,0,0,0);
    cLayout->setSpacing(0);
    container->setLayout(cLayout);
    container->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(header);
    layout->addWidget(container);
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    setLayout(layout);

    connect(header, SIGNAL(ExpandPressed()),        this, SLOT(Expand()));
    connect(header, SIGNAL(AddPressed()),           this, SLOT(AddElement()));
    connect(header, SIGNAL(DeleteAllTriggered()),   this, SLOT(DeleteAllElements()));
    connect(header, SIGNAL(DeleteTriggered()),      this, SLOT(deleteLater()));

    connect(header, SIGNAL(GroupMoved(QPoint)),     this, SLOT(MoveInLayout(QPoint)));
}

GroupWidget::~GroupWidget()
{

}

bool GroupWidget::IsExpanded() const
{
    return isExpanded;
}

void GroupWidget::Expand()
{
    isExpanded = !isExpanded;

    if(isExpanded)
        container->show();
    else
        container->hide();
}

ElementWidget* GroupWidget::AddElement(QString text)
{
    if(!isExpanded)
        Expand();

    ElementWidget* element = new ElementWidget(text);
    cLayout->addWidget(element);
    connect(element, SIGNAL(AddShortcuted()), this, SLOT(AddElement()));
    element->SetFocus();
    return element;
}


void GroupWidget::DeleteAllElements()
{
    QLayoutItem* item;

    while((item = cLayout->itemAt(0)) != NULL)
        delete item->widget();
}

int GroupWidget::Count() const
{
    return cLayout->count();
}

ElementWidget* GroupWidget::GetElement(int i)
{
    QLayoutItem* item;
    if((item = cLayout->itemAt(i)) != NULL)
        return static_cast<ElementWidget*>(item->widget());
    else
        return NULL;
}

QString GroupWidget::Title() const
{
    return header->Title();
}

void GroupWidget::SetTitle(QString _title)
{
    header->SetTitle(_title);
}

void GroupWidget::MoveInLayout(QPoint v)
{
    QVBoxLayout* parentLayout = static_cast<QVBoxLayout*>(parentWidget()->layout());

    int index = parentLayout->indexOf(this);

    for(int i=0; i<parentLayout->count(); i++)
    {
        if(parentLayout->itemAt(i)->widget()->rect().contains(parentLayout->itemAt(i)->widget()->mapFromGlobal(QCursor::pos())))
        {
            index = i;
            break;
        }
    }

    parentLayout->removeWidget(this);
    parentLayout->insertWidget(index, this);
}
