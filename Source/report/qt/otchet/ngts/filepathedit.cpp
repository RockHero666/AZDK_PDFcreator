#include "filepathedit.h"

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QAction>
#include <QtWidgets/QCompleter>
#include <QtWidgets/QFileSystemModel>

//#include <QtCore/QDebug>

FilePathEdit::FilePathEdit(QWidget *p, FilePathEdit::Mode m)
    :QWidget(p), dPath(0), mMode(m), cbFileList(0), lePath(0), mListMode(false)
{
    pbPrompt = new QPushButton("...");
    pbPrompt->setFixedWidth(32);

    QHBoxLayout *hbl = new QHBoxLayout;
    hbl->setContentsMargins(0, 0, 0, 0);
    hbl->setSpacing(0);

    cbFileList = new QComboBox;
    cbFileList->setVisible(false);
    hbl->addWidget(cbFileList, 1);
    //connect(cbFileList, SIGNAL(currentIndexChanged(int)), this, SLOT(pathPChanged()));

    lePath = new QLineEdit;
    hbl->addWidget(lePath, 1);
    connect(lePath, &QLineEdit::textEdited, this, &FilePathEdit::pathPChanged);

    QCompleter *qc = new QCompleter(this);
    qc->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    QFileSystemModel *fsm = new QFileSystemModel(qc);
    fsm->setReadOnly(true);
    fsm->setRootPath("");
    qc->setModel(fsm);

    QAction *a = new QAction(lePath);
    a->setShortcut(Qt::Key_Tab);
    a->setShortcutContext(Qt::WidgetShortcut);
    lePath->addAction(a);
    connect(a, &QAction::triggered, this, &FilePathEdit::completePath);

    lePath->setCompleter(qc);

    hbl->addWidget(pbPrompt);

    setLayout(hbl);
    setAutoFillBackground(true);
    connect(pbPrompt, &QPushButton::clicked, this, &FilePathEdit::openDialog);
}

QString FilePathEdit::getPath() const
{
    if (isList())
    {
        QDir dir(cbFileList->currentData().toString());
        return dir.absoluteFilePath(cbFileList->currentText());
    }
    else
        return QFileInfo(lePath->text()).absoluteFilePath();
}

void FilePathEdit::setPath(const QString& path)
{
    QFileInfo fi(path);
    QFileInfo fiOld(oldPath);
    if (isList())
    {
        int k;
        QString dir = fi.dir().path();
        QString file = fi.fileName();
        for (k = 0; k < cbFileList->count(); ++k)
        {
            QVariant d = cbFileList->itemData(k);
            if (d.isValid() && !d.isNull() && d.toString() != dir)
                continue;
            if (file == cbFileList->itemText(k))
                break;
        }
        if (k >= cbFileList->count())
        {
            cbFileList->addItem(fi.fileName(), fi.dir().path());
            k = cbFileList->count() - 1;
            cbFileList->setItemData(k, path, Qt::ToolTipRole);
        }
        cbFileList->setCurrentIndex(k);
        pathPChanged(path);
    }
    else if (fi != fiOld)
    {
        auto ap = fi.absoluteFilePath();
        auto rp = QDir().relativeFilePath(path);
        if (rp.size() < ap.size()) oldPath = std::move(rp);
        else oldPath = std::move(ap);
        lePath->setText(oldPath);
        emit pathChanged(oldPath);
    }
}

void FilePathEdit::openDialog()
{
    QString qs;
    QStringList fls;
    QFileInfo fl;
    
    if (dPath) fl.setFile(*dPath);
    else fl.setFile(lePath->text());

    qs = fl.absoluteDir().path();

    switch (mMode)
    {
    case Mode::FILEOPEN:
        qs = QFileDialog::getOpenFileName(this, tr("Укажите файл ") + mPrompt, qs, filters);
        break;
    case Mode::MULTIOPEN:
        fls = QFileDialog::getOpenFileNames(this, tr("Укажите файлы ") + mPrompt, qs, filters);
        if (fls.isEmpty()) return;
        if (mListMode) setList(fls);
        qs = fls.last();
        break;
    case Mode::FILESAVE:
        qs = QFileDialog::getSaveFileName(this, tr("Укажите файл ") + mPrompt, qs, filters);
        break;
    case Mode::DIRPATH:
        qs = QFileDialog::getExistingDirectory(this, tr("Укажите директорию ") + mPrompt, qs);
        break;
    }
    if (!qs.isEmpty())
    {
        setPath(qs);
        if (dPath) (*dPath) = qs;
    }
}

void FilePathEdit::pathPChanged(const QString& newPath)
{
    if (!newPath.compare(oldPath)) return;
    oldPath = newPath;
    emit pathChanged(oldPath);
}

void FilePathEdit::addFilter(const QString & fltr)
{
    if (!filters.isEmpty())
        filters.append(";;");
    filters.append(fltr);
}

void FilePathEdit::removeFilters()
{
    filters.clear();
}

void FilePathEdit::setList(const QStringList &list)
{
    cbFileList->clear();
    if (list.isEmpty()) return;

    for (const QString& qs : list)
    {
        QFileInfo fi(qs);
        auto qsp = fi.absoluteFilePath();
        cbFileList->addItem(fi.fileName(), qsp);
        cbFileList->setItemData(cbFileList->count() - 1, qsp, Qt::ToolTipRole);
    }
    pathPChanged(list.last());

}

void FilePathEdit::completePath()
{
    if (lePath)
    {
        QCompleter *qc = lePath->completer();
        if (qc) qc->setCurrentRow(0);
    }
}

QString FilePathEdit::getAbsolutePath() const
{
    return QDir().absoluteFilePath(getPath());
}

QString FilePathEdit::getRelativePath() const
{
    QString s(QDir().relativeFilePath(getPath()));
    if (s.count("..") > 3)
        return getAbsolutePath();
    return s;
}

QStringList FilePathEdit::getPathList() const
{
    if (!mListMode) return QStringList(getPath());
    QStringList sl;
    for (int k = 0; k < cbFileList->count(); ++k)
        sl << cbFileList->itemData(k).toString();
    return sl;
}

void FilePathEdit::setPrompt(const QString & prompt)
{
    mPrompt = prompt;
}

void FilePathEdit::clearPath()
{
    lePath->clear();
}

void FilePathEdit::setMode(Mode m)
{
    mMode = m;

    setListMode(mListMode);
}

void FilePathEdit::setListMode(bool on /*= true*/)
{
    mListMode = on;

    switch (mMode)
    {
    case Mode::FILEOPEN:
    case Mode::MULTIOPEN:
        break;
    default:
        return;
    }

    cbFileList->setVisible(false);
    lePath->setVisible(false);

    if (on)
    {
        cbFileList->setVisible(true);
    }
    else
    {
        lePath->setVisible(true);
    }
}

void FilePathEdit::setDisableEdit(bool on)
{
    lePath->setReadOnly(on);
}
