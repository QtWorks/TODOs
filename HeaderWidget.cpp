#include "HeaderWidget.h"

HeaderButton::HeaderButton(const QString &text, QWidget *parent) : QPushButton(text, parent)
{

}

HeaderButton::~HeaderButton()
{

}

void HeaderButton::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::MiddleButton)
        emit middleClicked();
    else
        QPushButton::mousePressEvent(event);
}

HeaderWidget::HeaderWidget(const QString& text, QWidget *parent) : QWidget(parent)
{
    _button = new HeaderButton(text, this);
    _line = new QLineEdit(text, this);
    _line->setAlignment(Qt::AlignHCenter);

    _layout = new QStackedLayout;
    _layout->addWidget(_button);
    _layout->addWidget(_line);
    setLayout(_layout);

    connect(_line,   SIGNAL(editingFinished()),  this, SLOT(showButton()));
    //connect(_line,   SIGNAL(focusLost()),        this, SLOT(showButton()));
    connect(_button, SIGNAL(clicked(bool)),      this, SIGNAL(clicked(bool)));
    connect(_button, SIGNAL(middleClicked()),    this, SLOT(showLine()));
}

HeaderWidget::~HeaderWidget()
{

}

void HeaderWidget::setText(const QString& text)
{
    _button->setText(text);
    _line->setText(text);
}

QString HeaderWidget::text() const
{
    return _button->text();
}

void HeaderWidget::showButton()
{
    _layout->setCurrentWidget(_button);
    _button->setFocus();
    _button->setText(_line->text());
}

void HeaderWidget::showLine()
{
    _layout->setCurrentWidget(_line);
    _line->setFocus();
    _line->setText(_button->text());
}
