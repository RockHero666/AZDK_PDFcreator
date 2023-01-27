/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QCalendarWidget *calendar_begin;
    QCalendarWidget *calendar_end;
    QPushButton *close;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(645, 277);
        Form->setMinimumSize(QSize(645, 277));
        Form->setMaximumSize(QSize(645, 277));
        calendar_begin = new QCalendarWidget(Form);
        calendar_begin->setObjectName(QString::fromUtf8("calendar_begin"));
        calendar_begin->setGeometry(QRect(10, 50, 280, 156));
        calendar_end = new QCalendarWidget(Form);
        calendar_end->setObjectName(QString::fromUtf8("calendar_end"));
        calendar_end->setGeometry(QRect(350, 50, 280, 156));
        close = new QPushButton(Form);
        close->setObjectName(QString::fromUtf8("close"));
        close->setGeometry(QRect(280, 220, 80, 21));
        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 10, 131, 16));
        label_2 = new QLabel(Form);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(430, 10, 131, 16));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        close->setText(QCoreApplication::translate("Form", "\320\236\320\232", nullptr));
        label->setText(QCoreApplication::translate("Form", "\320\224\320\260\321\202\320\260 \320\275\320\260\321\207\320\260\320\273\320\260 \320\270\321\201\320\277\321\213\321\202\320\260\320\275\320\270\320\271", nullptr));
        label_2->setText(QCoreApplication::translate("Form", "\320\224\320\260\321\202\320\260 \320\272\320\276\320\275\321\206\320\260 \320\270\321\201\320\277\321\213\321\202\320\260\320\275\320\270\320\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
