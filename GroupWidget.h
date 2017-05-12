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
    void SetTitle(const QString& _title);
    bool IsExpanded() const;
    GroupHeaderWidget* GetGroupHeaderWidget();

signals:
    void EnsureElementIsVisible(QWidget* w);

public slots:
    void Expand();
    ElementWidget* AddElement(const QString& text="");
    void MoveUpElement(ElementWidget* w);
    void MoveDownElement(ElementWidget* w);
    void FocusUpElement(ElementWidget* w);
    void FocusDownElement(ElementWidget* w);
    void DeleteAllElements();
    void MoveInLayout(QPoint v);
};

#endif // GROUPWIDGET_H
