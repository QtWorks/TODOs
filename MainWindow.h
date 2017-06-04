#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QStatusBar>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "ParametersDialog.h"
#include "MenuToolBar.h"
#include "StatusBar.h"
#include "GroupWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Q_DISABLE_COPY(MainWindow)

    QVBoxLayout* _layout;
    QScrollArea* _scroll;
    QWidget* _container;
    MenuToolBar* _menu;
    StatusBar* _statusBar;

    ParametersDialog* _parameters;

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    void ReadData();
    void ReadSettings();

public slots:
    void ShowElement(QWidget* w);
    GroupWidget *AddGroupWidget();
    void WriteData();
    void WriteSettings();
    void Move(const QPoint v);
    void LoadStyleSheet();
};

#endif // MAINWINDOW_H
