#include "calendar.h"
#include <QCalendarWidget>
#include "ui_form.h"


Calendar::Calendar(QWidget *parent):
    QWidget(parent)
        , ui(new Ui::Form)
{
 ui->setupUi(this);
    this->resize(400,200);

    // разобратся позже



}
