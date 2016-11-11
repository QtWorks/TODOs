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
    QVBoxLayout* layout;
    QScrollArea* scroll;
    QWidget* container;
    MenuToolBar* menu;
    StatusBar* statusBar;

    ParametersDialog* parameters;

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    void ReadData();
    void ReadSettings();

public slots:
    GroupWidget *AddGroupWidget();
    void WriteData();
    void WriteSettings();
    void Move(const QPoint v);
    void LoadStyleSheet();
};

#endif // MAINWINDOW_H
