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

private:
    Q_DISABLE_COPY(ElementText)

protected:
    void focusOutEvent(QFocusEvent *event);
    void insertFromMimeData(const QMimeData* source);

public:
    ElementText(const QString& text = "", QWidget *parent = nullptr);
    virtual ~ElementText();

};

class ElementWidget : public QFrame
{
    Q_OBJECT

private:
    Q_DISABLE_COPY(ElementWidget)

    QHBoxLayout* _layout;
    ElementText* _text;
    QPushButton* _remove;

protected:
    void showEvent(QShowEvent *event);
    void keyPressEvent(QKeyEvent *event);

public:
    ElementWidget(const QString& text = "", QWidget *parent = nullptr);
    virtual ~ElementWidget();
    QString text() const;
    void setText(const QString& text);
    void setFocus();
    void updateIcons(const QString& color);

signals:
    void addShortcuted();
    void moveUp(ElementWidget*);
    void moveDown(ElementWidget*);
    void focusUp(ElementWidget*);
    void focusDown(ElementWidget*);

public slots:
    void resizeTextEdit();
};

#endif // ELEMENTWIDGET_H
