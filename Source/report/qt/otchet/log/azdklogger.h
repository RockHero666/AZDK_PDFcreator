#pragma once
/*
 * Класс журналирования
*/

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QHash>
#include <memory>



class QTextStream;
class QJsonArray;
class QTimer;

/// Типы (цвета) сообщений для журналирования или вывода на экран
enum class LogType {
    Common,         //!< Любые неспециализированные сообщения
    Error,          //!< Сообщения об ошибках
    Warning,        //!< Сообщения-предупреждения
    Settings,       //!< Сообщения загрузки/сохранения настроек
    Socket,         //!< Сообщения сетевой передачи данных
    Action,         //!< Сообщения о различной активности
    Task,           //!< Сообщения о запуске и ходе исполнения вспомогательных задач
    Data,           //!< Сообщения о загрузке, сохранении или передачи данных
    Special0,       //!< Пользовательский тип 0
    Special1,       //!< Пользовательский тип 1
    Special2,       //!< Пользовательский тип 2
    Special3,       //!< Пользовательский тип 3
    Special4        //!< Пользовательский тип 4
};

/// Класс для журналирования сообщений различных типов по разным файлам
class AzdkLogger : public QObject
{
   
    Q_OBJECT

    using LogPtr = std::shared_ptr<QTextStream>;

    enum Flags {
        AL_APPEND = 1 << 0,
        AL_TIMESTAMP = 1 << 1,
        AL_AUTOFLUSH = 1 << 2,
        AL_SHOW_NEW_SESSION = 1 << 3
    };

public:
    AzdkLogger(QObject* parent = nullptr);
    ~AzdkLogger();

    bool open(const QString& filepath, LogType type, const QString& name = QString(), bool appendMode = true, bool timestamp = false, bool autoflush = false);
    
    bool isOpen(LogType type) const;

    bool close(int type);

    void log(const QString& msg, LogType type = LogType::Common, int indent = 0, bool supress_timestamp = false);

    void jsReadLoggers(const QJsonArray& jso, bool append = false);
    void jsWriteLoggers(QJsonArray& jso);

    void jsReadColors(const QJsonObject& jso);
    void jsWriteColors(QJsonObject& jso);

    void setDefaultType(LogType type) { mDefaultType = type; }

    void ignoreType(LogType type);

    quint32 color(LogType type) const;
    void setColor(LogType type, quint32 clr);

    void useDefaultLogger(bool on = true) { mUseDefaultLogger = on; }

    bool hasLogger(LogType type) const;

    void flushAll();

    void setTimestampFormat(const QString& _format) { mTimestampFormat = _format; }
    const QString& timestampFormat() const { return mTimestampFormat; }

    void setLogTemplateName(const QString& newName);

protected:
    void clear();
    QHash<int, LogPtr>::const_iterator getLogger(LogType type) const;

private:
    QHash<int, quint32> mColorTable;
    QHash<int, QString> mFiles;
    QHash<int, LogPtr> mLoggers;
    QHash<int, int> mFlags;
    QHash<int, QString> mNames;
    QList<int> mIgnoredTypes;
    LogType mDefaultType = LogType::Common;
    bool mUseDefaultLogger = true;
    QTimer* mFlushTimer = nullptr;

    QString mTimestampFormat;
    QString mSessionFormat;
};
