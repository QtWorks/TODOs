#include "ElementWidget.h"

ElementText::ElementText(QString text, QWidget *parent) : QTextEdit(text, parent)
{

}

ElementText::~ElementText()
{

}

void ElementText::focusOutEvent(QFocusEvent *event)
{
    QTextCursor tc = textCursor();
    tc.clearSelection();
    setTextCursor(tc);

    QTextEdit::focusOutEvent(event);
}

ElementWidget::ElementWidget(QString _text, QWidget *parent) : QFrame(parent)
{
    setMinimumHeight(20);

    text = new ElementText(_text, this);
    text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    text->setTabChangesFocus(true);

    remove = new QPushButton(QIcon::fromTheme("list-remove"), "", this);
    remove->setFixedSize(20,20);

    layout = new QHBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(text, 0, Qt::AlignTop);
    layout->addWidget(remove, 0, Qt::AlignTop);
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    setLayout(layout);

    connect(remove, SIGNAL(clicked(bool)), this, SLOT(deleteLater()));
    connect(text,   SIGNAL(textChanged()), this, SLOT(ResizeTextEdit()));

    ResizeTextEdit();
}

ElementWidget::~ElementWidget()
{

}

void ElementWidget::ResizeTextEdit()
{
    int height = text->document()->size().height();

    if(height < text->document()->defaultFont().pixelSize()+2)
        height = text->document()->defaultFont().pixelSize()+2;

    text->setFixedHeight(height);
    setFixedHeight(height);
}

QString ElementWidget::Text() const
{
    return text->toPlainText();
}

void ElementWidget::SetText(QString _text)
{
    text->setPlainText(_text);
    ResizeTextEdit();
}

void ElementWidget::SetFocus()
{
    text->setFocus();
}

void ElementWidget::showEvent(QShowEvent *event)
{
    ResizeTextEdit();
}

void ElementWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->matches(QKeySequence::AddTab) || event->matches(QKeySequence::New))
    {
        emit AddShortcuted();
    }

    if(event->key() == Qt::Key_Escape)
    {
        text->clearFocus();
    }
}
