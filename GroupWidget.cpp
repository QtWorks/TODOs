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

    connect(_header, SIGNAL(expandPressed()),        this, SLOT(expand()));
    connect(_header, SIGNAL(addPressed()),           this, SLOT(addElement()));
    connect(_header, SIGNAL(deleteAllTriggered()),   this, SLOT(deleteAllElements()));
    connect(_header, SIGNAL(deleteTriggered()),      this, SLOT(deleteLater()));

    connect(_header, SIGNAL(groupMoved(QPoint)),     this, SLOT(moveInLayout(QPoint)));
    _container->hide();
}

GroupWidget::~GroupWidget()
{

}

bool GroupWidget::isExpanded() const
{
    return _isExpanded;
}

void GroupWidget::expand()
{
    _isExpanded = !_isExpanded;

    if(_isExpanded)
        _container->show();
    else
        _container->hide();
}

ElementWidget* GroupWidget::addElement(const QString& text)
{
    if(!_isExpanded)
        expand();

    ElementWidget* element = new ElementWidget(text);
    _cLayout->addWidget(element);
    connect(element, SIGNAL(addShortcuted()),           this, SLOT(addElement()));
    connect(element, SIGNAL(moveUp(ElementWidget*)),    this, SLOT(moveUpElement(ElementWidget*)));
    connect(element, SIGNAL(moveDown(ElementWidget*)),  this, SLOT(moveDownElement(ElementWidget*)));
    connect(element, SIGNAL(focusUp(ElementWidget*)),   this, SLOT(focusUpElement(ElementWidget*)));
    connect(element, SIGNAL(focusDown(ElementWidget*)), this, SLOT(focusDownElement(ElementWidget*)));

    if(this->isVisible())
        emit ensureElementIsVisible(element);

    element->setFocus();
    return element;
}

void GroupWidget::moveUpElement(ElementWidget* w)
{
    int index = _cLayout->indexOf(w);

    if(index > 0)
    {
        _cLayout->removeWidget(w);
        _cLayout->insertWidget(index-1, w);
        emit ensureElementIsVisible(w);
    }
}

void GroupWidget::moveDownElement(ElementWidget* w)
{
    int index = _cLayout->indexOf(w);

    if(index > -1 && index < count()-1)
    {
        _cLayout->removeWidget(w);
        _cLayout->insertWidget(index+1, w);
        emit ensureElementIsVisible(w);
    }
}

void GroupWidget::focusUpElement(ElementWidget* w)
{
    int index = _cLayout->indexOf(w);

    if(index > 0)
    {
        getElement(index-1)->setFocus();
        emit ensureElementIsVisible(w);
    }
}

void GroupWidget::focusDownElement(ElementWidget* w)
{
    int index = _cLayout->indexOf(w);

    if(index > -1 && index < count()-1)
    {
        getElement(index+1)->setFocus();
        emit ensureElementIsVisible(w);
    }
}

void GroupWidget::deleteAllElements()
{
    QLayoutItem* item;

    while((item = _cLayout->itemAt(0)) != NULL)
        delete item->widget();
}

int GroupWidget::count() const
{
    return _cLayout->count();
}

ElementWidget* GroupWidget::getElement(int i)
{
    QLayoutItem* item;
    if((item = _cLayout->itemAt(i)) != NULL)
        return static_cast<ElementWidget*>(item->widget());
    else
        return NULL;
}

QString GroupWidget::title() const
{
    return _header->title();
}

void GroupWidget::setTitle(const QString& title)
{
    _header->setTitle(title);
}

void GroupWidget::moveInLayout(QPoint v)
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

GroupHeaderWidget* GroupWidget::getGroupHeaderWidget()
{
    return _header;
}
