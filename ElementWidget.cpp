#include "ElementWidget.h"

ElementText::ElementText(const QString& text, QWidget *parent) : QTextEdit(text, parent)
{

}

ElementText::~ElementText()
{

}

void ElementText::focusOutEvent(QFocusEvent *event)
{
    QTextCursor tc;

    tc= textCursor();
    tc.clearSelection();
    setTextCursor(tc);

    QString temp = toPlainText();
    while(temp.endsWith(' ')) temp.chop(1);
    while(temp.endsWith('\n')) temp.chop(1);
    setText(temp);

    QTextEdit::focusOutEvent(event);
}

void ElementText::insertFromMimeData(const QMimeData* source)
{
    insertPlainText(source->text());
}

ElementWidget::ElementWidget(const QString& text, QWidget *parent) : QFrame(parent)
{
    setMinimumHeight(20);

    _text = new ElementText(text, this);
    _text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _text->setTabChangesFocus(true);
    //text->setFocusPolicy(Qt::StrongFocus);

    _remove = new QPushButton(QIcon(":/images/delete"), "", this);
    _remove->setFixedSize(20,20);

    _layout = new QHBoxLayout;
    _layout->setContentsMargins(0,0,0,0);
    _layout->setSpacing(0);
    _layout->addWidget(_text, 0, Qt::AlignTop);
    _layout->addWidget(_remove, 0, Qt::AlignTop);
    _layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    setLayout(_layout);

    connect(_remove, SIGNAL(clicked(bool)), this, SLOT(deleteLater()));
    connect(_text,   SIGNAL(textChanged()), this, SLOT(ResizeTextEdit()));

    ResizeTextEdit();
}

ElementWidget::~ElementWidget()
{

}

void ElementWidget::ResizeTextEdit()
{
    int height = _text->document()->size().height();

    if(height < _text->document()->defaultFont().pixelSize()+2)
        height = _text->document()->defaultFont().pixelSize()+2;

    _text->setFixedHeight(height);
    setFixedHeight(height);
}

QString ElementWidget::Text() const
{
    return _text->toPlainText();
}

void ElementWidget::SetText(const QString& text)
{
    _text->setPlainText(text);
    ResizeTextEdit();
}

void ElementWidget::SetFocus()
{
    _text->setFocus();
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

    if(event->modifiers() & Qt::ControlModifier)
    {
        if(event->key() == Qt::Key_Up)
            emit MoveUp(this);

        if(event->key() == Qt::Key_Down)
            emit MoveDown(this);

        if(event->key() == Qt::Key_W)
            deleteLater();
    }

    if(event->modifiers() & Qt::AltModifier)
    {
        if(event->key() == Qt::Key_Up)
            emit FocusUp(this);

        if(event->key() == Qt::Key_Down)
            emit FocusDown(this);
    }

    if(event->key() == Qt::Key_Escape)
    {
        _text->clearFocus();
    }
}
