/*
 * Класс журналирования
*/
#include "azdklogger.h"
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QTimer>
#include <QtCore/QDateTime>

#pragma region Settings
#define SETS_NAME "name"
#define SETS_PATH "path"
#define SETS_TYPE "type"
#define SETS_APPEND "append"
#define SETS_TIMESTAMP "timestamp"
#define SETS_FLUSH "autoflush"

#define SETS_CLR_COMMON "common"
#define SETS_CLR_ERRS "error"
#define SETS_CLR_WARNS "warnings"
#define SETS_CLR_SETS "settings"
#define SETS_CLR_SOCKET "socket"
#define SETS_CLR_ACTION "action"
#define SETS_CLR_TASK "task"
#define SETS_CLR_DATA "data"
#define SETS_CLR_BKGRND "background"
#define SETS_CLR_SPEC1 "spec1"
#define SETS_CLR_SPEC2 "spec2"
#define SETS_CLR_SPEC3 "spec3"
#define SETS_CLR_SPEC4 "spec4"
#pragma endregion

/**
 * @brief Загрузка цвета сообщения из настроек
 * 
 * @param jso Объект JSON с настройками
 * @param logger указатель на объект журналирования
 * @param clrIdx тип сообщения
 * @param setName имя настройки
 * @return true в случае имеющеся настройки в объекте настроек
 * @return false если настройки нет
 */
static bool loadColor(const QJsonObject& jso, AzdkLogger* logger, LogType clrIdx, const QString& setName)
{
    if (!jso.contains(setName)) return false;
    auto jsv = jso[setName];
    quint32 clr = 0;
    if (jsv.isString())
    {
        bool ok;
        auto str = jsv.toString();
        if (str.startsWith('#')) str.remove(0, 1);
        clr = str.toUInt(&ok, 16);
        if (!ok) return false;
    }
    else
    {
        clr = jsv.toInt(-1);
        if (clr == -1) return false;
    }
    clr |= 0xFF000000;
    logger->setColor(clrIdx, clr);
    return true;
}

AzdkLogger::AzdkLogger(QObject* parent)
    : QObject(parent)
    , mTimestampFormat("hh:mm:ss.zzz")
    , mSessionFormat("dd.MM.yyyy HH:mm:ss")
{
    setColor(LogType::Common, 0xFFA0A0A4);

    mFlushTimer = new QTimer(this);
    connect(mFlushTimer, &QTimer::timeout, this, &AzdkLogger::flushAll);
    mFlushTimer->start(60000);
}

AzdkLogger::~AzdkLogger()
{
    clear();
}

/**
 * @brief Открытие фалйа журнала сообщений на запись
 * 
 * @param filepath путь к файлу журнала
 * @param ltype тип сообщений, которые будут записываться в этот файл
 * @param name имя журнала
 * @param appendMode режим записи - дописывать в конец файла
 * @param timestamp добавлять момент времени в начале строки
 * @param autoflush немедленная запись на диск и опустошение буфера
 * @return true в случае когда файл может быть открыт на запись
 * @return false если открытие на запись файла невозможно
 */
bool AzdkLogger::open(const QString& filepath, LogType ltype, const QString& name,
                      bool appendMode, bool timestamp, bool autoflush)
{
    QFile* file;
    if (appendMode)
        file = new QFile(filepath, this);
    else
    {
        int n = filepath.lastIndexOf('.');
        QString extraFileName = filepath.left(n);
        QString extName = filepath.mid(n);
        extraFileName += "-" + QDateTime::currentDateTime().toString("yyyy.MM.dd-hh.mm.ss") + extName;
        file = new QFile(extraFileName, this);
    }
    auto fl = QIODevice::WriteOnly | QIODevice::Text;
    if (appendMode) fl |= QIODevice::Append;

    int type = (int)ltype;

    for (auto logger : mLoggers)
    {
        auto file = dynamic_cast<QFile*>(logger ? logger->device() : nullptr);
        if (!file) continue;
        //if (QFileInfo(file->fileName()) == QFileInfo(name))
        //{
        //    mLoggers.insert(type, logger);
        //    mFlags.insert(type, mFlags.value(type));
        //    return true;
        //}
    }

    std::shared_ptr<QTextStream> logger;
    if (file->open(fl))
        logger = std::make_shared<QTextStream>(file);

    if (!logger)
    {
        delete file;
        return false;
    }

    logger->setCodec("UTF-8");

    if (mLoggers.contains(type))
    {
        auto oldfile = mLoggers.value(type)->device();
        if (oldfile && oldfile->isOpen())
            oldfile->close();
        delete oldfile;
        mLoggers.remove(type);
    }
    int flags = 0;
    if (appendMode) flags |= AL_APPEND | AL_SHOW_NEW_SESSION;
    if (timestamp) flags |= AL_TIMESTAMP;
    if (autoflush) flags |= AL_AUTOFLUSH;
    mLoggers.insert(type, logger);
    mFlags.insert(type, flags);
    mFiles.insert(type, filepath);
    if (!name.isEmpty())
        mNames.insert(type, name);
    
    return true;
}

/**
 * @brief Проверяет, открыт ли файл журналирования для заданного типа сообщений
 * 
 * @param type тип сообщений
 * @return true если файл открыт
 * @return false если файл не открыт
 */
bool AzdkLogger::isOpen(LogType type) const
{
    auto it = mLoggers.find((int)type);
    if (it == mLoggers.cend()) return false;
    auto device = (*it)->device();
    return device && device->isOpen();
}

bool AzdkLogger::close(int _type)
{
    if (!mLoggers.contains(_type)) return false;

    auto logger = mLoggers.value(_type);

    auto fl = dynamic_cast<QFile*>(logger->device());
    if (fl)
    {
        fl->close();
        auto len = fl->size();
        if (!len) fl->remove();
        delete fl;
        logger->setDevice(nullptr);
    }

    mFiles.remove(_type);
    mFlags.remove(_type);

    return true;
}


/**
 * @brief Вывод сообщения в файл журнала
 * 
 * @param msg сообщение
 * @param type тип сообщения
 * @param indent число пробелов перед сообщением
 * @param supress_timestamp запрет вывода метки времени
 */
void AzdkLogger::log(const QString& msg, LogType type, int indent, bool supress_timestamp)
{
    if (mIgnoredTypes.contains((int)type)) return;
    auto it = getLogger(type);
    if (it == mLoggers.cend()) return;

    int flags = mFlags.value((int)type);

    auto& stream = *(*it);

    if (flags & AL_SHOW_NEW_SESSION)
    {
        stream << "\n---=== " + tr("new session") + " " + QDateTime::currentDateTime().toString(mSessionFormat) + " ===---\n";
        mFlags[(int)type] = flags & ~AL_SHOW_NEW_SESSION;
    }

    if (indent > 0) stream <<  QString(indent, ' ');
    if ((flags & AL_TIMESTAMP) && !supress_timestamp)
        stream << QTime::currentTime().toString(mTimestampFormat) << "; ";
    stream << msg << "\n";
    if (flags & AL_AUTOFLUSH) stream.flush();
}

/**
 * @brief Загрузка настроек файлов журнала
 * 
 * @param jso Объект настроек JSON
 * @param append значение false очищает список файлов журналов
 */
void AzdkLogger::jsReadLoggers(const QJsonArray& jso, bool append)
{
    if (!append) clear();
    for (const auto& jsv : jso)
    {
        if (jsv.isObject())
        {
            auto jsl = jsv.toObject();
            open(jsl[SETS_PATH].toString(), (LogType)jsl[SETS_TYPE].toInt(), jsl[SETS_NAME].toString(),
                jsl[SETS_APPEND].toBool(), jsl[SETS_TIMESTAMP].toBool(), jsl[SETS_FLUSH].toBool());
        }
    }
}

/**
 * @brief Сохранение настроек файлов журналов
 * 
 * @param jso Объект настроек JSON
 */
void AzdkLogger::jsWriteLoggers(QJsonArray& jso)
{
    for (auto it = mLoggers.cbegin(); it != mLoggers.cend(); ++it)
    {
        auto type = it.key();
        auto logger = *it;
        auto file = dynamic_cast<QFile*>(logger ? logger->device() : nullptr);
        auto flags = mFlags.value(type);
        if (!file) continue;
        QJsonObject jsl;
        jsl[SETS_PATH] = mFiles.value(type);
        jsl[SETS_TYPE] = type;
        jsl[SETS_TIMESTAMP] = (flags & AL_TIMESTAMP) == AL_TIMESTAMP;
        jsl[SETS_APPEND] = (flags & AL_APPEND) == AL_APPEND;
        jsl[SETS_FLUSH] = (flags & AL_AUTOFLUSH) == AL_AUTOFLUSH;
        if (mNames.contains(type))
            jsl[SETS_NAME] = mNames.value(type);
        jso.append(jsl);
    }
}

/**
 * @brief Загрузка цветов всех типов сообщений
 * 
 * @param jsClr Объект настроек JSON
 */
void AzdkLogger::jsReadColors(const QJsonObject& jsClr)
{
    loadColor(jsClr, this, LogType::Common, SETS_CLR_COMMON);
    loadColor(jsClr, this, LogType::Error, SETS_CLR_ERRS);
    loadColor(jsClr, this, LogType::Warning, SETS_CLR_WARNS);
    loadColor(jsClr, this, LogType::Settings, SETS_CLR_SETS);
    loadColor(jsClr, this, LogType::Socket, SETS_CLR_SOCKET);
    loadColor(jsClr, this, LogType::Action, SETS_CLR_ACTION);
    loadColor(jsClr, this, LogType::Task, SETS_CLR_TASK);
    loadColor(jsClr, this, LogType::Data, SETS_CLR_DATA);
    loadColor(jsClr, this, LogType::Special0, SETS_CLR_BKGRND);
    loadColor(jsClr, this, LogType::Special1, SETS_CLR_SPEC1);
    loadColor(jsClr, this, LogType::Special2, SETS_CLR_SPEC2);
    loadColor(jsClr, this, LogType::Special3, SETS_CLR_SPEC3);
    loadColor(jsClr, this, LogType::Special4, SETS_CLR_SPEC4);
}

/**
 * @brief Сохранение цветов всех типов сообщений
 * 
 * @param jsClr Объект настроек JSON
 */
void AzdkLogger::jsWriteColors(QJsonObject& jsClr)
{
    for (auto it = mColorTable.cbegin(); it != mColorTable.cend(); ++it)
    {
        LogType clrIdx = (LogType)it.key();
        auto str = "#" + QString::number(*it, 16);
        switch (clrIdx)
        {
        case LogType::Common: jsClr[SETS_CLR_COMMON] = str; break;
        case LogType::Error: jsClr[SETS_CLR_ERRS] = str; break;
        case LogType::Warning: jsClr[SETS_CLR_WARNS] = str; break;
        case LogType::Settings: jsClr[SETS_CLR_SETS] = str; break;
        case LogType::Socket: jsClr[SETS_CLR_SOCKET] = str; break;
        case LogType::Action: jsClr[SETS_CLR_ACTION] = str; break;
        case LogType::Task: jsClr[SETS_CLR_TASK] = str; break;
        case LogType::Data: jsClr[SETS_CLR_DATA] = str; break;
        case LogType::Special0: jsClr[SETS_CLR_BKGRND] = str; break;
        case LogType::Special1: jsClr[SETS_CLR_SPEC1] = str; break;
        case LogType::Special2: jsClr[SETS_CLR_SPEC2] = str; break;
        case LogType::Special3: jsClr[SETS_CLR_SPEC3] = str; break;
        case LogType::Special4: jsClr[SETS_CLR_SPEC4] = str; break;
        default: continue;
        }
    }
}

/**
 * @brief Игнорирование журнала указанного типа сообщения (будут посылаться в @LogType::Common)
 * 
 * @param type Тип сообщения
 */
void AzdkLogger::ignoreType(LogType type)
{
    mIgnoredTypes.append((int)type);
}

/**
 * @brief Получение RGB цвета для заданного типа сообщений
 * 
 * @param type тип сообщений
 * @return quint32 
 */
quint32 AzdkLogger::color(LogType type) const
{
    auto it = mColorTable.find((int)type);
    if (it != mColorTable.cend()) return *it;
    it = mColorTable.find((int)mDefaultType);
    return it == mColorTable.cend() ? 0xFFFFFFFF :  *it;
}

/**
 * @brief Установка цвета для заданного типа сообщений
 * 
 * @param type тип сообщений
 * @param clr RGB цвет
 */
void AzdkLogger::setColor(LogType type, quint32 clr)
{
    mColorTable.insert((int)type, clr);
}

/**
 * @brief Проверка наличия файла журнала для указанного типа сообщений
 * 
 * @param type тип сообщений
 * @return true/false наличие/отсутствие файла журанала
 */
bool AzdkLogger::hasLogger(LogType type) const
{
    return getLogger(type) != mLoggers.cend();
}

void AzdkLogger::setLogTemplateName(const QString& newName)
{
    for (auto _type : mLoggers.keys())
    {
        bool append = mFlags.value(_type) & AL_APPEND;
        bool timestamp = mFlags.value(_type) & AL_TIMESTAMP;
        bool autoflush = mFlags.value(_type) & AL_AUTOFLUSH;
        QString _name = mNames.value(_type);
        QString _filepath;
        auto file = dynamic_cast<QFile*>(mLoggers[_type]->device());
        if (file)
        {
            _filepath = file->fileName();
            int k = qMax(_filepath.lastIndexOf('/'), _filepath.lastIndexOf('\\'));
            _filepath = _filepath.left(k + 1);
        }
        _filepath += newName + ".";
        _filepath += _name.isEmpty() ? QString::asprintf("type%d", _type) : _name;
        _filepath += ".txt";
        auto datePlace = _filepath.contains("%date%");
        auto timePlace = _filepath.contains("%time%");
        if (datePlace || timePlace)
        {
            QDateTime dt = QDateTime::currentDateTime();
            if (datePlace) _filepath.replace("%date%", dt.toString("yyyy.MM.dd"));
            if (timePlace) _filepath.replace("%time%", dt.toString("hh.mm.ss"));
        }
        //_filepath.replace("%type%", QString::asprintf("type%d", _type));
        //_filepath += ".txt";
        close(_type);
        open(_filepath, (LogType)_type, _name, true, timestamp, autoflush);
        if (!append) mFlags[_type] &= ~AL_APPEND;
    }
}

/// @brief Очистка списка файла журналов с их корректным закрытием
void AzdkLogger::clear()
{
    for (auto logType : mLoggers.keys())
        close(logType);
    mLoggers.clear();
    mIgnoredTypes.clear();
}

/// @brief Сброс буферов в файлы журналов
void AzdkLogger::flushAll()
{
    for (auto it = mLoggers.begin(); it != mLoggers.end(); ++it)
    {
        if (mFlags.value(it.key()) & AL_AUTOFLUSH) continue;
        it.value()->flush();
    }
}

/**
 * @brief Получение итератора на файл (поток) журанала, для Common журнла всегда присутствует
 * 
 * @param type тип сообщений
 * @return итератор на файл журнала
 */
QHash<int, AzdkLogger::LogPtr>::const_iterator AzdkLogger::getLogger(LogType type) const
{
    auto it = mLoggers.find((int)type);
    if (it == mLoggers.cend() && mUseDefaultLogger)
        it = mLoggers.find((int)mDefaultType);
    return it;
}
