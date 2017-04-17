#include "StatusBar.h"

StatusBar::StatusBar(QWidget *parent) : QStatusBar(parent), moving(false)
{

}

StatusBar::~StatusBar()
{

}

void StatusBar::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        if(moving)
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
        {
            startPos = event->pos();
            moving = true;
        }
    }
}

void StatusBar::mouseReleaseEvent(QMouseEvent *event)
{
    moving  = false;
    setCursor(Qt::OpenHandCursor);
}

void StatusBar::enterEvent(QEvent *event)
{
    setCursor(Qt::OpenHandCursor);
}
