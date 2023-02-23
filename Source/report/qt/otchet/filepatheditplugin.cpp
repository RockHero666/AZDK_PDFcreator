#include <filepathedit.h>

#include <QtCore/QtPlugin>
#include "filepatheditplugin.h"

FilePathEditPlugin::FilePathEditPlugin(QObject *parent)
    : QObject(parent)
{
    initialized = false;
}

void FilePathEditPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
    if (initialized)
        return;

    initialized = true;
}

bool FilePathEditPlugin::isInitialized() const
{
    return initialized;
}

QWidget *FilePathEditPlugin::createWidget(QWidget *parent)
{
    return new FilePathEdit(parent);
}

QString FilePathEditPlugin::name() const
{
    return "FilePathEdit";
}

QString FilePathEditPlugin::group() const
{
    return "Custom Widgets";
}

QIcon FilePathEditPlugin::icon() const
{
    return QIcon();
}

QString FilePathEditPlugin::toolTip() const
{
    return QString();
}

QString FilePathEditPlugin::whatsThis() const
{
    return QString();
}

bool FilePathEditPlugin::isContainer() const
{
    return false;
}

QString FilePathEditPlugin::domXml() const
{
    return tr(
        "<ui language=\"c++\"> displayname=\"FilePathEdit\" >\n"
        "   <widget class=\"FilePathEdit\" name=\"fpe\">\n"
        "       <property name=\"geometry\">\n"
        "           <rect>\n"
        "               <x>0</x>\n"
        "               <y>0</y>\n"
        "               <width>120</width>\n"
        "               <height>23</height>\n"
        "           </rect>\n"
        "       </property>\n"
        "   </widget>\n"
        "   <customwidgets>\n"
        "       <customwidget>\n"
        "           <class>FilePathEdit</class>\n"
        "           <addpagemethod>addPage</addpagemethod>\n"
        "           <propertyspecifications>\n"
        "               <stringpropertyspecification name=\"mode\" type=\"singleline\" />\n"
        "           </propertyspecifications>\n"
        "       </customwidget>\n"
        "   </customwidgets>\n"
        "</ui>"
        );
}

QString FilePathEditPlugin::includeFile() const
{
    return "ngts/filepathedit.h";
}

