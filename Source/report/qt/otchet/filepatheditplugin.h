/**
* \file filepatheditplugin.h
* \brief Плагин к Qt Designer для класса FilePathEdit
*/
#ifndef FILEPATHEDITPLUGIN_H
#define FILEPATHEDITPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class FilePathEditPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface" FILE "filepatheditplugin.json")
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    FilePathEditPlugin(QObject *parent = 0);

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);

private:
    bool initialized;
};

#endif // FILEPATHEDITPLUGIN_H
