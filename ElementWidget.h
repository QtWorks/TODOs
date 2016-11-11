#ifndef ELEMENTWIDGET_H
#define ELEMENTWIDGET_H

#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QKeyEvent>

class ElementWidget : public QFrame
{
    Q_OBJECT

private:
    QHBoxLayout* layout;
    QTextEdit* text;
    QPushButton* remove;

protected:
    void showEvent(QShowEvent *event);
    void keyPressEvent(QKeyEvent *event);

public:
    ElementWidget(QString _text = "", QWidget *parent = 0);
    virtual ~ElementWidget();
    QString Text() const;
    void SetText(QString _text);
    void SetFocus();

signals:
    void AddShortcuted();

public slots:
    void ResizeTextEdit();
};

#endif // ELEMENTWIDGET_H
