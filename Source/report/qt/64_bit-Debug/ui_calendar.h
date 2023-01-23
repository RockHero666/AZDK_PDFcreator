/********************************************************************************
** Form generated from reading UI file 'calendar.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALENDAR_H
#define UI_CALENDAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_calendar
{
public:

    void setupUi(QWidget *calendar)
    {
        if (calendar->objectName().isEmpty())
            calendar->setObjectName(QString::fromUtf8("calendar"));
        calendar->resize(400, 300);

        retranslateUi(calendar);

        QMetaObject::connectSlotsByName(calendar);
    } // setupUi

    void retranslateUi(QWidget *calendar)
    {
        calendar->setWindowTitle(QCoreApplication::translate("calendar", "calendar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class calendar: public Ui_calendar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENDAR_H
