#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QStatusBar>
#include <QMouseEvent>

class StatusBar : public QStatusBar
{
    Q_OBJECT

private:
    QPoint startPos;
    bool moving;

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);

public:
    StatusBar(QWidget* parent = 0);
    virtual ~StatusBar();

signals:
    void Moved(const QPoint);
};

#endif // STATUSBAR_H
