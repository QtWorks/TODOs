#ifndef PARAMETERSDIALOG_H
#define PARAMETERSDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QSettings>
#include <QColorDialog>

class ParametersDialog : public QDialog
{
    Q_OBJECT
private:
    QFormLayout* layout;
    QCheckBox* startup;
    QPushButton* share;
    QPushButton* about;
    QPushButton* groupColor;
    QPushButton* elementColor;
    QPushButton* fontColor;
    QWidget* startupContainer;
    QHBoxLayout *cLayout;
    QSettings* settings;

    QString dataPath;
    QString startUpPath;
    QString defaultGroupColor;
    QString defaultElementColor;
    QString defaultFontColor;

public:
    ParametersDialog(QWidget* parent = 0);
    virtual ~ParametersDialog();
    const QString DataPath() const;
    bool GetStartUpPolicy() const;
    QSettings* Settings() const;
    const QString Stylesheet() const;
    QString ColorToRgba(const QColor& color) const;
    QColor RgbaToColor(QString rgba) const;
    QString GroupColor() const;
    QString ElementColor() const;
    QString FontColor() const;

signals:
    void ColorChanged();

public slots:
    void OpenDataFolder() const;
    void OpenShare() const;
    void OpenAbout() const;
    void Open(QString str) const;
    void SetStartUpPolicy(bool b);
    void SetGroupColor();
    void SetElementColor();
    void SetFontColor();
};

#endif // PARAMETERSDIALOG_H
