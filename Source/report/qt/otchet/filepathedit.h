#ifndef FILEPATHEDIT_H
#define FILEPATHEDIT_H

#include <QtWidgets/QWidget>

class QLineEdit;
class QPushButton;
class QString;
class QComboBox;

class FilePathEdit : public QWidget
{
    Q_OBJECT

    friend class FilePathEditDelegate;

    Q_PROPERTY(Mode dialogMode READ mode WRITE setMode)
    Q_PROPERTY(bool listMode READ isList WRITE setListMode)

public:
    enum Mode {
        FILESAVE = 0,
        FILEOPEN = 1,
        DIRPATH = 2,
        MULTIOPEN = 3
    };
    Q_ENUM(Mode)

    FilePathEdit(QWidget *parent = 0, Mode mode = FILEOPEN);
    QString getPath() const;
    QString getAbsolutePath() const;
    QString getRelativePath() const;
    QStringList getPathList() const;
    void setPath(const QString& path);
    void setDefaultPathPtr(QString *str) { dPath = str; }
    void setFilter(const QString& fltr) { filters = fltr; }
    void addFilter(const QString& fltr);
    void removeFilters();
    void setList(const QStringList &list);
    void setPrompt(const QString & prompt);
    void clearPath();

    inline Mode mode() const { return mMode; }
    void setMode(Mode m);

    bool isList() const { return mListMode; }
    void setListMode(bool on = true);

    void setDisableEdit(bool on = true);

protected:
    QComboBox *cbFileList;
    QLineEdit *lePath;
    QPushButton *pbPrompt;
    QString *dPath;     // указатель на строку, в которой хранится "путь по умолчанию"
    QString filters;    // строка с фильрами
    QString oldPath;
    QString mPrompt;

    Mode mMode;
    bool mListMode;

protected:
    void openDialog();
    void pathPChanged(const QString&);
    void completePath();

signals:
    void pathChanged(const QString &);
};

#endif // FILEPATHEDIT_H
