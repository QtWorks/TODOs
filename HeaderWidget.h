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
    HeaderLine(const QString& text = "", QWidget *parent = nullptr);
    virtual ~HeaderLine();

signals:
    void focusLost();
};

class HeaderButton : public QPushButton
{
    Q_OBJECT

private:
    Q_DISABLE_COPY(HeaderButton)

protected:
    void mousePressEvent(QMouseEvent *event);

public:
    HeaderButton(const QString& text = "", QWidget *parent = nullptr);
    virtual ~HeaderButton();

signals:
    void middleClicked();
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
    HeaderWidget(const QString& text = "", QWidget *parent = nullptr);
    virtual ~HeaderWidget();
    void setText(const QString& text);
    QString text() const;

signals:
    void clicked(bool b);

public slots:
    void showButton();
    void showLine();
    void clickButton(bool b);
};

#endif // HEADERWIDGET_H
