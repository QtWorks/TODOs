#ifndef ELEMENTWIDGET_H
#define ELEMENTWIDGET_H

#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QTextBlock>
#include <QMimeData>

class ElementText : public QTextEdit
{
    Q_OBJECT

protected:
    void focusOutEvent(QFocusEvent *event);
    void insertFromMimeData(const QMimeData* source);

public:
    ElementText(const QString& text = "", QWidget *parent = 0);
    virtual ~ElementText();

signals:
    void FocusLost();
};

class ElementWidget : public QFrame
{
    Q_OBJECT

private:
    QHBoxLayout* layout;
    ElementText* text;
    QPushButton* remove;

protected:
    void showEvent(QShowEvent *event);
    void keyPressEvent(QKeyEvent *event);

public:
    ElementWidget(const QString& _text = "", QWidget *parent = 0);
    virtual ~ElementWidget();
    QString Text() const;
    void SetText(const QString& _text);
    void SetFocus();

signals:
    void AddShortcuted();
    void MoveUp(ElementWidget*);
    void MoveDown(ElementWidget*);
    void FocusUp(ElementWidget*);
    void FocusDown(ElementWidget*);

public slots:
    void ResizeTextEdit();
};

#endif // ELEMENTWIDGET_H
