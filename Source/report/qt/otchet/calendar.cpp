#include "calendar.h"
#include <QCalendarWidget>
#include "ui_form.h"


Calendar::Calendar(QWidget *parent):
    QWidget(parent)
        , ui(new Ui::Form)
{
    ui->setupUi(this);
    this->setWindowTitle("Выберите дату");
    //this->setWindowFlags(Qt::SubWindow);




    ui->calendar_begin->setSelectedDate(QDate::currentDate());
    ui->calendar_end->setSelectedDate(QDate::currentDate());


    ui->calendar_begin->selectedDate();
}

QDate Calendar::get_date_begin()
{
    return ui->calendar_begin->selectedDate();
}

QDate Calendar::get_date_end()
{
    return ui->calendar_end->selectedDate();
}

void Calendar::set_date_begin(int y,int m,int d)
{
    ui->calendar_begin->setSelectedDate(QDate(y,m,d));
}

void Calendar::set_date_end(int y,int m,int d)
{
    ui->calendar_end->setSelectedDate(QDate(y,m,d));
}

void Calendar::on_close_clicked()
{
    QDate start = get_date_begin();
    QDate end = get_date_end();


    if(start>end)
    {
      QMessageBox::about(this,"ERROR","Дата начала не может быть больше даты конца!");
      return;
    }



    emit finished();
    this->close();
}
