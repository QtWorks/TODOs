#include "ParametersDialog.h"

ParametersDialog::ParametersDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Parameters");

    settings = new QSettings("xavi-b", qApp->applicationDisplayName(), this);

#ifdef _WIN32
    dataPath = "%APPDATA%\\"+qApp->applicationName()+"\\";
#elif __APPLE__
    dataPath = QDir::homePath()+"/Library/Preferences/"+qApp->applicationName()+"/";
#else
    dataPath = QDir::homePath()+"/."+qApp->applicationName()+"/";
#endif

#ifdef _WIN32
    startUpPath = "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
#elif __APPLE__
    startUpPath = QDir::homePath()+"/Library/LaunchAgents/";
#else
    startUpPath = QDir::homePath()+"/.config/autostart/";
#endif

    defaultGroupColor = "rgba(127,0,0,50%)";
    defaultElementColor = "rgba(255,127,127,50%)";
    defaultFontColor = "white";

    startup = new QCheckBox(this);
    startup->setChecked(GetStartUpPolicy());
    startupContainer = new QWidget(this);
    cLayout = new QHBoxLayout;
    cLayout->setMargin(2);
    cLayout->setSpacing(0);
    cLayout->setAlignment(Qt::AlignCenter);
    cLayout->addWidget(startup);
    startupContainer->setLayout(cLayout);

    share = new QPushButton(QIcon::fromTheme("emblem-shared"), "", this);
    share->setAutoDefault(false);
    share->setFixedSize(30,30);
    about = new QPushButton(QIcon::fromTheme("help-about"), "", this);
    about->setAutoDefault(false);
    about->setFixedSize(30,30);
    groupColor = new QPushButton("", this);
    groupColor->setAutoDefault(false);
    groupColor->setFixedSize(30,30);
    groupColor->setStyleSheet("background: "+GroupColor()+";");
    elementColor = new QPushButton("", this);
    elementColor->setAutoDefault(false);
    elementColor->setFixedSize(30,30);
    elementColor->setStyleSheet("background: "+ElementColor()+";");
    fontColor = new QPushButton("", this);
    fontColor->setAutoDefault(false);
    fontColor->setFixedSize(30,30);
    fontColor->setStyleSheet("background: "+FontColor()+";");

    layout = new QFormLayout;
    layout->addRow("Launch on start-up:", startupContainer);
    layout->addRow("Group color:", groupColor);
    layout->addRow("Element color:", elementColor);
    layout->addRow("Font color:", fontColor);
    layout->addRow("Connect your TODOs:", share);
    layout->addRow("About:", about);
    setLayout(layout);

    connect(share,          SIGNAL(clicked(bool)), this, SLOT(OpenShare()));
    connect(startup,        SIGNAL(clicked(bool)), this, SLOT(SetStartUpPolicy(bool)));
    connect(about,          SIGNAL(clicked(bool)), this, SLOT(OpenAbout()));

    connect(groupColor,     SIGNAL(clicked(bool)), this, SLOT(SetGroupColor()));
    connect(elementColor,   SIGNAL(clicked(bool)), this, SLOT(SetElementColor()));
    connect(fontColor,      SIGNAL(clicked(bool)), this, SLOT(SetFontColor()));
}

ParametersDialog::~ParametersDialog()
{

}

QString ParametersDialog::ColorToRgba(const QColor& color) const
{
    return "rgba("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+","+QString::number(color.alpha())+");";
}

QColor ParametersDialog::RgbaToColor(QString rgba) const
{
    QStringList c = rgba.replace("rgba(", "").replace(")", "").split(",");
    return QColor(c[0].toInt(), c[1].toInt(), c[2].toInt(), (c.count()>3) ? c[3].toInt() : 0);
}

void ParametersDialog::SetGroupColor()
{
    QColor color = QColorDialog::getColor(RgbaToColor(GroupColor()), this, "Choose Group Color", QColorDialog::ShowAlphaChannel);
    settings->setValue("GroupColor", ColorToRgba(color));
    groupColor->setStyleSheet("background: "+ColorToRgba(color)+";");

    emit ColorChanged();
}

void ParametersDialog::SetElementColor()
{
    QColor color = QColorDialog::getColor(RgbaToColor(ElementColor()), this, "Choose Element Color", QColorDialog::ShowAlphaChannel);
    settings->setValue("ElementColor", ColorToRgba(color));
    elementColor->setStyleSheet("background: "+ColorToRgba(color)+";");

    emit ColorChanged();
}

void ParametersDialog::SetFontColor()
{
    QColor color = QColorDialog::getColor(RgbaToColor(FontColor()), this, "Choose Font Color", QColorDialog::ShowAlphaChannel);
    settings->setValue("FontColor", ColorToRgba(color));
    fontColor->setStyleSheet("background: "+ColorToRgba(color)+";");

    emit ColorChanged();
}

QString ParametersDialog::GroupColor() const
{
    return settings->value("GroupColor", defaultGroupColor).toString();
}

QString ParametersDialog::ElementColor() const
{
    return settings->value("ElementColor", defaultElementColor).toString();
}

QString ParametersDialog::FontColor() const
{
    return settings->value("FontColor", defaultFontColor).toString();
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

void ParametersDialog::Open(QString str) const
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
    QSettings settings(startUpPath, QSettings::NativeFormat).setValue(qApp->applicationName(), b);
#elif __APPLE__
    QFile f(startUpPath+qApp->applicationName()+".plist");

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
    QFile f(startUpPath+qApp->applicationName()+".desktop");

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
    return QSettings(startUpPath, QSettings::NativeFormat).value(qApp->applicationName(), false).toBool();
#elif __APPLE__
    return QFile(startUpPath+qApp->applicationName()+".plist").exists();
#else
    return QFile(startUpPath+qApp->applicationName()+".desktop").exists();
#endif
}

const QString ParametersDialog::DataPath() const
{
    if(!QDir().exists(dataPath))
        QDir().mkdir(dataPath);

    return dataPath;
}

QSettings* ParametersDialog::Settings() const
{
    return settings;
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
