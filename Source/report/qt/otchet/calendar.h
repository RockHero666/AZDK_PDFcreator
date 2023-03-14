#ifndef CALENDAR_H
#define CALENDAR_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class Form; }
QT_END_NAMESPACE

class Calendar : public QWidget
{
    Q_OBJECT
public:
    Calendar(QWidget *parent = nullptr);

    QDate get_date_begin();
    QDate get_date_end();

    void set_date_begin(int y,int m,int d);
    void set_date_end(int y,int m,int d);
    void set_date_begin(QDate & date);
    void set_date_end(QDate& date);


private slots:
    void on_close_clicked();

signals:
    void finished();

private:
Ui::Form *ui;
};

#endif // CALENDAR_H
