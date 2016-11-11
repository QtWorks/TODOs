#include "StatusBar.h"

StatusBar::StatusBar(QWidget *parent) : QStatusBar(parent)
{

}

StatusBar::~StatusBar()
{

}

void StatusBar::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        if(event->pos().x() < size().width() - size().height())
        {
            setCursor(Qt::ClosedHandCursor);
            emit Moved(event->globalPos() - mapTo(parentWidget(), startPos));
        }
    }
}

void StatusBar::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        if(event->pos().x() < size().width() - size().height())
            startPos = event->pos();
    }
}

void StatusBar::mouseReleaseEvent(QMouseEvent *event)
{
    setCursor(Qt::OpenHandCursor);
}

void StatusBar::enterEvent(QEvent *event)
{
    setCursor(Qt::OpenHandCursor);
}
