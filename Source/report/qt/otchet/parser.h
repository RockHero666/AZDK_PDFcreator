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

    void to_parse();// ������ ��� ����� �� ����
    void to_parse_current_dir(); // ������ ������ �������� ����
    void set_path(const QString & path);

    QTime Str_to_time(const QString & str); // ��������������� ������� ���������
    int time_step_converter(QTime time,int add); // ��������� ��� �������� 59 + 1
    int time_subtraction(QTime time,int sub); // ��������� ��� �������� 0 - 1
    QVector<QVector<QString>> parse_resulte_table(const QString & error_path); // ������� ������� ���
    int Find_time_on_vector(QVector<QString>& time_vect ,QString time , bool up_or_down_state); // ����� ��������� ������ ������ ������� ���������
    QString Png_path_veryf(const QString & path);
    QVector<int> parse_resulte_table_2_ver2(const QString & client_path,const QString & server_path); // ������� ������� ���
    QVector<QString> Frames_count_and_time_ver2(const QString & server_path,
        const QString & azdk_server_path,const QString & index,const QString & azdk_number); // ���������� ���������� ������ � ����� ���������
    int error_count(const QString & error_path); // ��������������� ������� ��� ����������� ���������� ������
    bool is_exists(const QString& path);
    QVector<QString> font_pars();

    QVector<QDate> parse_calendar_date_from_file(); // ����� ����������� � ������������ ���� ���������

    QVector<bool> parse_for_pict_script(QString azdk_num, QVector<bool> sfx_pressed);

signals:
    void log_message(const QString & message, QRgb color = qRgb(255, 255, 255));
};

#endif // PARSER_H
