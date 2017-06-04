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
    Q_DISABLE_COPY(ParametersDialog)

    QFormLayout* _layout;
    QCheckBox* _startup;
    QPushButton* _share;
    QPushButton* _about;
    QPushButton* _groupColor;
    QPushButton* _elementColor;
    QPushButton* _fontColor;
    QWidget* _startupContainer;
    QHBoxLayout *_cLayout;
    QSettings* _settings;

    QString _dataPath;
    QString _startUpPath;
    QString _defaultGroupColor;
    QString _defaultElementColor;
    QString _defaultFontColor;

public:
    ParametersDialog(QWidget* parent = 0);
    virtual ~ParametersDialog();
    const QString DataPath() const;
    bool GetStartUpPolicy() const;
    QSettings* Settings() const;
    const QString Stylesheet() const;
    QString ColorToRgba(const QColor& color) const;
    QColor RgbaToColor(const QString& rgba) const;
    QString GroupColor() const;
    QString ElementColor() const;
    QString FontColor() const;

signals:
    void ColorChanged();

public slots:
    void OpenDataFolder() const;
    void OpenShare() const;
    void OpenAbout() const;
    void Open(const QString& str) const;
    void SetStartUpPolicy(bool b);
    void SetGroupColor();
    void SetElementColor();
    void SetFontColor();
};

#endif // PARAMETERSDIALOG_H
