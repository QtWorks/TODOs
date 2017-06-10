#include "StatusBar.h"

StatusBar::StatusBar(QWidget *parent)
    : QStatusBar(parent), _moving(false)
{

}

StatusBar::~StatusBar()
{

}

void StatusBar::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        if(_moving)
        {
            setCursor(Qt::ClosedHandCursor);
            emit moved(event->globalPos() - mapTo(parentWidget(), _startPos));
        }
    }
}

void StatusBar::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        if(event->pos().x() < size().width() - size().height())
        {
            _startPos = event->pos();
            _moving = true;
        }
    }
}

void StatusBar::mouseReleaseEvent(QMouseEvent *event)
{
    _moving  = false;
    setCursor(Qt::OpenHandCursor);
}

void StatusBar::enterEvent(QEvent *event)
{
    setCursor(Qt::OpenHandCursor);
}
