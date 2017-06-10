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
    Q_DISABLE_COPY(GroupWidget)

    QVBoxLayout* _layout;
    QVBoxLayout* _cLayout;
    GroupHeaderWidget* _header;
    QWidget* _container;

    bool _isExpanded;

public:
    GroupWidget(QWidget *parent = nullptr);
    virtual ~GroupWidget();
    int count() const;
    ElementWidget* getElement(int i);
    QString title() const;
    void setTitle(const QString& title);
    bool isExpanded() const;
    GroupHeaderWidget* getGroupHeaderWidget();

signals:
    void ensureElementIsVisible(QWidget* w);

public slots:
    void expand();
    ElementWidget* addElement(const QString& text="");
    void moveUpElement(ElementWidget* w);
    void moveDownElement(ElementWidget* w);
    void focusUpElement(ElementWidget* w);
    void focusDownElement(ElementWidget* w);
    void deleteAllElements();
    void moveInLayout(QPoint v);
};

#endif // GROUPWIDGET_H
