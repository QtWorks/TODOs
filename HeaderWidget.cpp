#include "HeaderWidget.h"

HeaderLine::HeaderLine(const QString& text, QWidget *parent) : QLineEdit(text, parent)
{

}

HeaderLine::~HeaderLine()
{

}

void HeaderLine::focusOutEvent(QFocusEvent *event)
{
    emit FocusLost();
    QLineEdit::focusOutEvent(event);
}

HeaderButton::HeaderButton(const QString &text, QWidget *parent) : QPushButton(text, parent)
{

}

HeaderButton::~HeaderButton()
{

}

void HeaderButton::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::MiddleButton)
        emit MiddleClicked();
    else
        QPushButton::mousePressEvent(event);
}

HeaderWidget::HeaderWidget(const QString& text, QWidget *parent) : QWidget(parent)
{
    _button = new HeaderButton(text, this);
    _line = new HeaderLine(text, this);
    _line->setAlignment(Qt::AlignHCenter);

    _layout = new QStackedLayout;
    _layout->addWidget(_button);
    _layout->addWidget(_line);
    setLayout(_layout);

    connect(_line,   SIGNAL(returnPressed()),    this, SLOT(ShowButton()));
    connect(_line,   SIGNAL(FocusLost()),        this, SLOT(ShowButton()));
    connect(_button, SIGNAL(clicked(bool)),      this, SLOT(ClickButton(bool)));
    connect(_button, SIGNAL(MiddleClicked()),    this, SLOT(ShowLine()));
}

HeaderWidget::~HeaderWidget()
{

}

void HeaderWidget::SetText(const QString& text)
{
    _button->setText(text);
    _line->setText(text);
}

QString HeaderWidget::Text() const
{
    return _button->text();
}

void HeaderWidget::ShowButton()
{
    _layout->setCurrentWidget(_button);
    _button->setFocus();
    _button->setText(_line->text());
}

void HeaderWidget::ShowLine()
{
    _layout->setCurrentWidget(_line);
    _line->setFocus();
    _line->setText(_button->text());
}

void HeaderWidget::ClickButton(bool b)
{
    emit clicked(b);
}
