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
    ParametersDialog(QWidget* parent = nullptr);
    virtual ~ParametersDialog();
    const QString dataPath() const;
    bool getStartUpPolicy() const;
    QSettings* settings() const;
    const QString stylesheet() const;
    QString groupColor() const;
    QString elementColor() const;
    QString fontColor() const;

signals:
    void colorChanged();

public slots:
    void openDataFolder() const;
    void openShare() const;
    void openAbout() const;
    void open(const QString& str) const;
    void setStartUpPolicy(bool b);
    void setGroupColor();
    void setElementColor();
    void setFontColor();
};

#endif // PARAMETERSDIALOG_H
