#ifndef GROUPWIDGET_H
#define GROUPWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QColor>

#include "ElementWidget.h"
#include "GroupHeaderWidget.h"

class GroupWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout* layout;
    QVBoxLayout* cLayout;
    GroupHeaderWidget* header;
    QWidget* container;

    bool isExpanded;

public:
    GroupWidget(QWidget *parent = 0);
    virtual ~GroupWidget();
    int Count() const;
    ElementWidget* GetElement(int i);
    QString Title() const;
    void SetTitle(QString _title);
    bool IsExpanded() const;

signals:
    void EnsureElementIsVisible(QWidget* w);

public slots:
    void Expand();
    ElementWidget* AddElement(QString text="");
    void DeleteAllElements();
    void MoveInLayout(QPoint v);
};

#endif // GROUPWIDGET_H
