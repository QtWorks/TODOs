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
    HeaderWidget* title;
    QPushButton* add;
    QHBoxLayout* layout;

    QPoint startDragPos;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:
    GroupHeaderWidget(QWidget *parent = 0);
    virtual ~GroupHeaderWidget();
    QString Title() const;
    void SetTitle(QString _title);
    HeaderWidget* GetHeaderWidget();

signals:
    void ExpandPressed();
    void AddPressed();
    void DeleteAllTriggered();
    void DeleteTriggered();
    void GroupMoving(QPoint);
    void GroupMoved(QPoint);

public slots:
    void ShowContextMenu(const QPoint& position);
    void PressExpand();
    void PressAdd();
    void TriggerDeleteAll();
    void TriggerDelete();
};

#endif // GROUPHEADERWIDGET_H
