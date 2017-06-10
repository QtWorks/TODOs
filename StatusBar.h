#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QStatusBar>
#include <QMouseEvent>

class StatusBar : public QStatusBar
{
    Q_OBJECT

private:
    Q_DISABLE_COPY(StatusBar)

    QPoint _startPos;
    bool _moving;

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);

public:
    StatusBar(QWidget* parent = nullptr);
    virtual ~StatusBar();

signals:
    void moved(const QPoint);
};

#endif // STATUSBAR_H
