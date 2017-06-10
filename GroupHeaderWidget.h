#ifndef GROUPHEADERWIDGET_H
#define GROUPHEADERWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMenu>
#include <QAction>

#include "HeaderWidget.h"

class GroupHeaderWidget : public QWidget
{
    Q_OBJECT

private:
    Q_DISABLE_COPY(GroupHeaderWidget)

    HeaderWidget* _title;
    QPushButton* _add;
    QHBoxLayout* _layout;

    QPoint _startDragPos;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:
    GroupHeaderWidget(QWidget *parent = nullptr);
    virtual ~GroupHeaderWidget();
    QString title() const;
    void setTitle(const QString& title);
    HeaderWidget* getHeaderWidget();
    void updateIcons(const QString& color);

signals:
    void expandPressed();
    void addPressed();
    void deleteAllTriggered();
    void deleteTriggered();
    void groupMoving(QPoint);
    void groupMoved(QPoint);

public slots:
    void showContextMenu(const QPoint& position);

};

#endif // GROUPHEADERWIDGET_H
