#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QVector>
#include <QColor>

class MainWindow;

class Parser : public QObject
{
    friend class MainWindow;
    Q_OBJECT
private:

    QString path;
    QString serial_num;
    QVector<QString> all_paths;

public:
    explicit Parser(QObject *parent = nullptr);

    void to_parse();// парсит все файлы по пути
    void to_parse_current_dir(); // парсит только корневой путь
    void set_path(const QString & path);

    QTime Str_to_time(const QString & str); // вспомогательная функция конвертор
    int time_step_converter(QTime time,int add); // конвертор для проблемы 59 + 1
    int time_subtraction(QTime time,int sub); // конвертор для проблемы 0 - 1
    QVector<QVector<QString>> parse_resulte_table(const QString & error_path); // Парсинг таблици СКО
    int Find_time_on_vector(QVector<QString>& time_vect ,QString time , bool up_or_down_state); // часть механники вывода общего времени испытаний
    QString Png_path_veryf(const QString & path);
    QVector<int> parse_resulte_table_2_ver2(const QString & client_path,const QString & server_path); // Парсинг таблици МЗД
    QVector<QString> Frames_count_and_time_ver2(const QString & server_path,
        const QString & azdk_server_path,const QString & index,const QString & azdk_number); // Определяет количество кадров и время испытания
    int error_count(const QString & error_path); // вспомогательная функция для определения количества кадров
    bool is_exists(const QString& path);
    QVector<QString> font_pars();

    QVector<QDate> parse_calendar_date_from_file(); // поиск минимальной и максимальной даты испытаний

    QVector<bool> parse_for_pict_script(QString azdk_num, QVector<bool> sfx_pressed);

signals:
    void log_message(const QString & message, QRgb color = qRgb(255, 255, 255));
};

#endif // PARSER_H
