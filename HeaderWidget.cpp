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
    button = new HeaderButton(text, this);
    line = new HeaderLine(text, this);
    line->setAlignment(Qt::AlignHCenter);

    layout = new QStackedLayout;
    layout->addWidget(button);
    layout->addWidget(line);
    setLayout(layout);

    connect(line,   SIGNAL(returnPressed()),    this, SLOT(ShowButton()));
    connect(line,   SIGNAL(FocusLost()),        this, SLOT(ShowButton()));
    connect(button, SIGNAL(clicked(bool)),      this, SLOT(ClickButton(bool)));
    connect(button, SIGNAL(MiddleClicked()),    this, SLOT(ShowLine()));
}

HeaderWidget::~HeaderWidget()
{

}

void HeaderWidget::SetText(const QString& text)
{
    button->setText(text);
    line->setText(text);
}

QString HeaderWidget::Text() const
{
    return button->text();
}

void HeaderWidget::ShowButton()
{
    layout->setCurrentWidget(button);
    button->setFocus();
    button->setText(line->text());
}

void HeaderWidget::ShowLine()
{
    layout->setCurrentWidget(line);
    line->setFocus();
    line->setText(button->text());
}

void HeaderWidget::ClickButton(bool b)
{
    emit clicked(b);
}
