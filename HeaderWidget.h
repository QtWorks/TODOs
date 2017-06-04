#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>
#include <QStackedLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMouseEvent>

class HeaderLine : public QLineEdit
{
    Q_OBJECT

private:
    Q_DISABLE_COPY(HeaderLine)

protected:
    void focusOutEvent(QFocusEvent *event);

public:
    HeaderLine(const QString& text = "", QWidget *parent = 0);
    virtual ~HeaderLine();

signals:
    void FocusLost();
};

class HeaderButton : public QPushButton
{
    Q_OBJECT

private:
    Q_DISABLE_COPY(HeaderButton)

protected:
    void mousePressEvent(QMouseEvent *event);

public:
    HeaderButton(const QString& text = "", QWidget *parent = 0);
    virtual ~HeaderButton();

signals:
    void MiddleClicked();
};

class HeaderWidget : public QWidget
{
    Q_OBJECT

private:
    Q_DISABLE_COPY(HeaderWidget)

    QStackedLayout* _layout;
    HeaderButton* _button;
    HeaderLine* _line;

public:
    HeaderWidget(const QString& text = "", QWidget *parent = 0);
    virtual ~HeaderWidget();
    void SetText(const QString& text);
    QString Text() const;

signals:
    void clicked(bool b);

public slots:
    void ShowButton();
    void ShowLine();
    void ClickButton(bool b);
};

#endif // HEADERWIDGET_H
