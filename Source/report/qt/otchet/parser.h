#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QDirIterator>
#include <QDebug>
#include <QVector>
#include <QTextStream>
#include <QTime>
#include <QDate>
#include <QFile>
#include <iostream>
#include <algorithm>


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




    void to_parse();
    void set_path(const QString & path);
    void set_serial_num(const QString & path);

    QTime Str_to_time(const QString & str);
    int time_step_converter(QTime time,int add);
    int time_subtraction(QTime time,int sub);
    QVector<QVector<QString>> parse_resulte_table(const QString & error_path);
    QVector<int> parse_resulte_table_2(const QString & client_path,const QString & server_path);
    int Find_time_on_vector(QVector<QString>& time_vect ,QString time , bool up_or_down_state);
    QVector<QString> Frames_count_and_time(const QString & server_path,const QString & index);
    QString Png_path_veryf(const QString & path);
    QVector<int> parse_resulte_table_2_ver2(const QString & client_path,const QString & server_path);
    QVector<QString> Frames_count_and_time_ver2(const QString & server_path,const QString & azdk_server_path,const QString & index);


};

#endif // PARSER_H
