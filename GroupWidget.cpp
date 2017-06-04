#include "GroupWidget.h"

GroupWidget::GroupWidget(QWidget *parent) : QWidget(parent), _isExpanded(true)
{
    setMinimumHeight(20+2);
    setFixedHeight(20+2);

    _header = new GroupHeaderWidget(this);
    _header->setFixedHeight(20);

    _container = new QWidget(this);

    _cLayout = new QVBoxLayout;
    _cLayout->setContentsMargins(0,0,0,0);
    _cLayout->setSpacing(0);
    _container->setLayout(_cLayout);
    _container->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    _layout = new QVBoxLayout;
    _layout->setContentsMargins(0,0,0,0);
    _layout->setSpacing(0);
    _layout->addWidget(_header);
    _layout->addWidget(_container);
    _layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    setLayout(_layout);

    connect(_header, SIGNAL(ExpandPressed()),        this, SLOT(Expand()));
    connect(_header, SIGNAL(AddPressed()),           this, SLOT(AddElement()));
    connect(_header, SIGNAL(DeleteAllTriggered()),   this, SLOT(DeleteAllElements()));
    connect(_header, SIGNAL(DeleteTriggered()),      this, SLOT(deleteLater()));

    connect(_header, SIGNAL(GroupMoved(QPoint)),     this, SLOT(MoveInLayout(QPoint)));
}

GroupWidget::~GroupWidget()
{

}

bool GroupWidget::IsExpanded() const
{
    return _isExpanded;
}

void GroupWidget::Expand()
{
    _isExpanded = !_isExpanded;

    if(_isExpanded)
        _container->show();
    else
        _container->hide();
}

ElementWidget* GroupWidget::AddElement(const QString& text)
{
    if(!_isExpanded)
        Expand();

    ElementWidget* element = new ElementWidget(text);
    _cLayout->addWidget(element);
    connect(element, SIGNAL(AddShortcuted()),           this, SLOT(AddElement()));
    connect(element, SIGNAL(MoveUp(ElementWidget*)),    this, SLOT(MoveUpElement(ElementWidget*)));
    connect(element, SIGNAL(MoveDown(ElementWidget*)),  this, SLOT(MoveDownElement(ElementWidget*)));
    connect(element, SIGNAL(FocusUp(ElementWidget*)),   this, SLOT(FocusUpElement(ElementWidget*)));
    connect(element, SIGNAL(FocusDown(ElementWidget*)), this, SLOT(FocusDownElement(ElementWidget*)));

    if(this->isVisible())
        emit EnsureElementIsVisible(element);

    element->SetFocus();
    return element;
}

void GroupWidget::MoveUpElement(ElementWidget* w)
{
    int index = _cLayout->indexOf(w);

    if(index > 0)
    {
        _cLayout->removeWidget(w);
        _cLayout->insertWidget(index-1, w);
        emit EnsureElementIsVisible(w);
    }
}

void GroupWidget::MoveDownElement(ElementWidget* w)
{
    int index = _cLayout->indexOf(w);

    if(index > -1 && index < Count()-1)
    {
        _cLayout->removeWidget(w);
        _cLayout->insertWidget(index+1, w);
        emit EnsureElementIsVisible(w);
    }
}

void GroupWidget::FocusUpElement(ElementWidget* w)
{
    int index = _cLayout->indexOf(w);

    if(index > 0)
    {
        GetElement(index-1)->SetFocus();
        emit EnsureElementIsVisible(w);
    }
}

void GroupWidget::FocusDownElement(ElementWidget* w)
{
    int index = _cLayout->indexOf(w);

    if(index > -1 && index < Count()-1)
    {
        GetElement(index+1)->SetFocus();
        emit EnsureElementIsVisible(w);
    }
}

void GroupWidget::DeleteAllElements()
{
    QLayoutItem* item;

    while((item = _cLayout->itemAt(0)) != NULL)
        delete item->widget();
}

int GroupWidget::Count() const
{
    return _cLayout->count();
}

ElementWidget* GroupWidget::GetElement(int i)
{
    QLayoutItem* item;
    if((item = _cLayout->itemAt(i)) != NULL)
        return static_cast<ElementWidget*>(item->widget());
    else
        return NULL;
}

QString GroupWidget::Title() const
{
    return _header->Title();
}

void GroupWidget::SetTitle(const QString& title)
{
    _header->SetTitle(title);
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

GroupHeaderWidget* GroupWidget::GetGroupHeaderWidget()
{
    return _header;
}
