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

private:
Ui::Form *ui;
};

#endif // CALENDAR_H
