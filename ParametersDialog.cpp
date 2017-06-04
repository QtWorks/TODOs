#include "ParametersDialog.h"

ParametersDialog::ParametersDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Parameters");

    _settings = new QSettings("xavi-b", qApp->applicationDisplayName(), this);

#ifdef _WIN32
    _dataPath = QDir::homePath()+"\\AppData\\Roaming\\"+qApp->applicationName()+"\\";
#elif __APPLE__
    _dataPath = QDir::homePath()+"/Library/Preferences/"+qApp->applicationName()+"/";
#else
    _dataPath = QDir::homePath()+"/."+qApp->applicationName()+"/";
#endif

#ifdef _WIN32
    _startUpPath = "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
#elif __APPLE__
    _startUpPath = QDir::homePath()+"/Library/LaunchAgents/";
#else
    _startUpPath = QDir::homePath()+"/.config/autostart/";
#endif

    _defaultGroupColor = "rgba(127,0,0,50%)";
    _defaultElementColor = "rgba(255,127,127,50%)";
    _defaultFontColor = "rgba(255,255,255,255)";

    _startup = new QCheckBox(this);
    _startup->setChecked(GetStartUpPolicy());
    _startupContainer = new QWidget(this);
    _cLayout = new QHBoxLayout;
    _cLayout->setMargin(2);
    _cLayout->setSpacing(0);
    _cLayout->setAlignment(Qt::AlignCenter);
    _cLayout->addWidget(_startup);
    _startupContainer->setLayout(_cLayout);

    _share = new QPushButton(QIcon::fromTheme("emblem-shared"), "", this);
    _share->setAutoDefault(false);
    _share->setFixedSize(30,30);
    _about = new QPushButton(QIcon::fromTheme("help-about"), "", this);
    _about->setAutoDefault(false);
    _about->setFixedSize(30,30);
    _groupColor = new QPushButton("", this);
    _groupColor->setAutoDefault(false);
    _groupColor->setFixedSize(30,30);
    _groupColor->setStyleSheet("background: "+GroupColor()+";");
    _elementColor = new QPushButton("", this);
    _elementColor->setAutoDefault(false);
    _elementColor->setFixedSize(30,30);
    _elementColor->setStyleSheet("background: "+ElementColor()+";");
    _fontColor = new QPushButton("", this);
    _fontColor->setAutoDefault(false);
    _fontColor->setFixedSize(30,30);
    _fontColor->setStyleSheet("background: "+FontColor()+";");

    _layout = new QFormLayout;
    _layout->addRow("Launch on start-up:", _startupContainer);
    _layout->addRow("Group color:", _groupColor);
    _layout->addRow("Element color:", _elementColor);
    _layout->addRow("Font color:", _fontColor);
    _layout->addRow("Connect your TODOs:", _share);
    _layout->addRow("About:", _about);
    setLayout(_layout);

    connect(_share,          SIGNAL(clicked(bool)), this, SLOT(OpenShare()));
    connect(_startup,        SIGNAL(clicked(bool)), this, SLOT(SetStartUpPolicy(bool)));
    connect(_about,          SIGNAL(clicked(bool)), this, SLOT(OpenAbout()));

    connect(_groupColor,     SIGNAL(clicked(bool)), this, SLOT(SetGroupColor()));
    connect(_elementColor,   SIGNAL(clicked(bool)), this, SLOT(SetElementColor()));
    connect(_fontColor,      SIGNAL(clicked(bool)), this, SLOT(SetFontColor()));
}

ParametersDialog::~ParametersDialog()
{

}

QString ParametersDialog::ColorToRgba(const QColor& color) const
{
    return "rgba("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+","+QString::number(color.alpha())+")";
}

QColor ParametersDialog::RgbaToColor(const QString& rgba) const
{
    QStringList c = QString(rgba).replace("rgba(", "").replace(")", "").split(",");
    return QColor(c[0].toInt(), c[1].toInt(), c[2].toInt(), c[3].toInt());
}

void ParametersDialog::SetGroupColor()
{
    QColor color = QColorDialog::getColor(RgbaToColor(GroupColor()), this, "Choose Group Color", QColorDialog::ShowAlphaChannel);

    if(color.isValid())
    {
        _settings->setValue("GroupColor", ColorToRgba(color));
        _groupColor->setStyleSheet("background: "+ColorToRgba(color)+";");

        emit ColorChanged();
    }
}

void ParametersDialog::SetElementColor()
{
    QColor color = QColorDialog::getColor(RgbaToColor(ElementColor()), this, "Choose Element Color", QColorDialog::ShowAlphaChannel);

    if(color.isValid())
    {
        _settings->setValue("ElementColor", ColorToRgba(color));
        _elementColor->setStyleSheet("background: "+ColorToRgba(color)+";");

        emit ColorChanged();
    }
}

void ParametersDialog::SetFontColor()
{
    QColor color = QColorDialog::getColor(RgbaToColor(FontColor()), this, "Choose Font Color", QColorDialog::ShowAlphaChannel);

    if(color.isValid())
    {
        _settings->setValue("FontColor", ColorToRgba(color));
        _fontColor->setStyleSheet("background: "+ColorToRgba(color)+";");

        emit ColorChanged();
    }
}

QString ParametersDialog::GroupColor() const
{
    return _settings->value("GroupColor", _defaultGroupColor).toString();
}

QString ParametersDialog::ElementColor() const
{
    return _settings->value("ElementColor", _defaultElementColor).toString();
}

QString ParametersDialog::FontColor() const
{
    return _settings->value("FontColor", _defaultFontColor).toString();
}

void ParametersDialog::OpenDataFolder() const
{
    Open(DataPath());
}

void ParametersDialog::OpenShare() const
{
    QString url = "http://www.google.fr"; // TODO
    Open(url);
}

void ParametersDialog::OpenAbout() const
{
    Open("http://www.xavi-b.fr");
}

void ParametersDialog::Open(const QString& str) const
{
#ifdef _WIN32
    QProcess::startDetached("explorer", QStringList() << str);
#elif __APPLE__
    QProcess::startDetached("open",     QStringList() << str);
#else
    QProcess::startDetached("xdg-open", QStringList() << str);
#endif
}

void ParametersDialog::SetStartUpPolicy(bool b)
{
#ifdef _WIN32
    QSettings(_startUpPath, QSettings::NativeFormat).setValue(qApp->applicationName(), b);
#elif __APPLE__
    QFile f(_startUpPath+qApp->applicationName()+".plist");

    if(b)
    {
        if(f.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            f.write("<?xml version="1.0" encoding="UTF-8"?>\n");
            f.write("<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">\n");
            f.write("<plist version="1.0"><dict>\n");
            f.write("<key>Label</key>\n");
            f.write(("<string>com."+qApp->organizationName().toLower()+"."+qApp->applicationName().toLower()+"</string>\n").toStdString().c_str());
            f.write("<key>ProgramArguments</key>\n");
            f.write("<array>\n");
            f.write(("<string>"+qApp->applicationName().toLower()+"</string>\n").toStdString().c_str());
            f.write("</array>\n");
            f.write("<key>KeepAlive</key><true/>\n");
            f.write("</dict></plist>\n");
            f.close();
        }
    }
    else
    {
        f.remove();
    }
#else
    QFile f(_startUpPath+qApp->applicationName()+".desktop");

    if(b)
    {
        if(f.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            f.write("[Desktop Entry]\n");
            f.write(("Exec="+qApp->applicationFilePath()+"\n").toStdString().c_str());
            f.close();
        }
    }
    else
    {
        f.remove();
    }
#endif
}

bool ParametersDialog::GetStartUpPolicy() const
{
#ifdef _WIN32
    return QSettings(_startUpPath, QSettings::NativeFormat).value(qApp->applicationName(), false).toBool();
#elif __APPLE__
    return QFile(_startUpPath+qApp->applicationName()+".plist").exists();
#else
    return QFile(_startUpPath+qApp->applicationName()+".desktop").exists();
#endif
}

const QString ParametersDialog::DataPath() const
{
    if(!QDir().exists(_dataPath))
        QDir().mkdir(_dataPath);

    return _dataPath;
}

QSettings* ParametersDialog::Settings() const
{
    return _settings;
}

const QString ParametersDialog::Stylesheet() const
{
    QFile f(":/qss");

    if(f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString str = f.readAll();
        str = str.replace("%GROUP_COLOR%", GroupColor());
        str = str.replace("%ELEMENT_COLOR%", ElementColor());
        str = str.replace("%FONT_COLOR%", FontColor());
        f.close();
        return str;
    }
    else
    {
        qWarning("No custom stylesheet");
    }

    return "";
}
