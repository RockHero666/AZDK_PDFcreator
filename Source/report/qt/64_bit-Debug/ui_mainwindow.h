/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *create_button;
    QLineEdit *name_report_line;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *management_report_line;
    QLineEdit *management_sky_report_line;
    QLabel *label_4;
    QCheckBox *sfx_o;
    QCheckBox *sfx_ro1;
    QCheckBox *sfx_r1;
    QCheckBox *sfx_r3;
    QCheckBox *sfx_s;
    QCheckBox *sfx_all;
    QLineEdit *path_to_file_line;
    QPushButton *puth_to_file_button;
    QLabel *label_5;
    QFrame *line;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *firmware_line;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QFrame *line_2;
    QLabel *label_16;
    QLineEdit *file_name_line;
    QLabel *label_17;
    QLineEdit *savepath_line;
    QPushButton *save_path_button;
    QPushButton *to_path_button;
    QLabel *label_18;
    QLabel *label_19;
    QCheckBox *checkBox;
    QComboBox *comboBox;
    QDateEdit *dateEdit_start;
    QDateEdit *dateEdit_end;
    QLabel *label_20;
    QLabel *label_21;
    QDoubleSpinBox *size_doubleSpinBox;
    QDoubleSpinBox *focus_doubleSpinBox;
    QDoubleSpinBox *influence_doubleSpinBox;
    QDoubleSpinBox *intensity_doubleSpinBox;
    QSpinBox *number_spinBox;
    QSpinBox *number_ods_spinBox;
    QCheckBox *checkBox_timer;
    QLabel *label_22;
    QComboBox *speed_comboBox;
    QProgressBar *progressBar;
    QCheckBox *sfx_r2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 730);
        MainWindow->setMinimumSize(QSize(800, 730));
        MainWindow->setMaximumSize(QSize(800, 730));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        create_button = new QPushButton(centralwidget);
        create_button->setObjectName(QString::fromUtf8("create_button"));
        create_button->setGeometry(QRect(600, 590, 141, 21));
        name_report_line = new QLineEdit(centralwidget);
        name_report_line->setObjectName(QString::fromUtf8("name_report_line"));
        name_report_line->setGeometry(QRect(200, 80, 221, 21));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 80, 151, 16));
        label->setScaledContents(true);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 110, 151, 16));
        label_2->setScaledContents(true);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 140, 161, 20));
        label_3->setScaledContents(true);
        management_report_line = new QLineEdit(centralwidget);
        management_report_line->setObjectName(QString::fromUtf8("management_report_line"));
        management_report_line->setGeometry(QRect(200, 110, 221, 21));
        management_sky_report_line = new QLineEdit(centralwidget);
        management_sky_report_line->setObjectName(QString::fromUtf8("management_sky_report_line"));
        management_sky_report_line->setGeometry(QRect(200, 140, 221, 21));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(610, 10, 121, 16));
        sfx_o = new QCheckBox(centralwidget);
        sfx_o->setObjectName(QString::fromUtf8("sfx_o"));
        sfx_o->setGeometry(QRect(630, 140, 81, 19));
        sfx_ro1 = new QCheckBox(centralwidget);
        sfx_ro1->setObjectName(QString::fromUtf8("sfx_ro1"));
        sfx_ro1->setGeometry(QRect(630, 60, 81, 19));
        sfx_r1 = new QCheckBox(centralwidget);
        sfx_r1->setObjectName(QString::fromUtf8("sfx_r1"));
        sfx_r1->setGeometry(QRect(630, 80, 81, 19));
        sfx_r3 = new QCheckBox(centralwidget);
        sfx_r3->setObjectName(QString::fromUtf8("sfx_r3"));
        sfx_r3->setGeometry(QRect(630, 120, 81, 19));
        sfx_s = new QCheckBox(centralwidget);
        sfx_s->setObjectName(QString::fromUtf8("sfx_s"));
        sfx_s->setGeometry(QRect(630, 40, 81, 19));
        sfx_all = new QCheckBox(centralwidget);
        sfx_all->setObjectName(QString::fromUtf8("sfx_all"));
        sfx_all->setGeometry(QRect(630, 160, 91, 19));
        path_to_file_line = new QLineEdit(centralwidget);
        path_to_file_line->setObjectName(QString::fromUtf8("path_to_file_line"));
        path_to_file_line->setGeometry(QRect(20, 40, 401, 21));
        puth_to_file_button = new QPushButton(centralwidget);
        puth_to_file_button->setObjectName(QString::fromUtf8("puth_to_file_button"));
        puth_to_file_button->setGeometry(QRect(440, 40, 80, 21));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 20, 161, 20));
        label_5->setScaledContents(true);
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 190, 801, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(180, 210, 201, 16));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 250, 151, 16));
        firmware_line = new QLineEdit(centralwidget);
        firmware_line->setObjectName(QString::fromUtf8("firmware_line"));
        firmware_line->setGeometry(QRect(170, 370, 151, 21));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 370, 151, 16));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 410, 151, 16));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 450, 151, 16));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 490, 151, 16));
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 530, 151, 16));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 570, 151, 16));
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 610, 151, 16));
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 650, 151, 16));
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(530, -10, 20, 761));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(620, 250, 111, 20));
        file_name_line = new QLineEdit(centralwidget);
        file_name_line->setObjectName(QString::fromUtf8("file_name_line"));
        file_name_line->setGeometry(QRect(560, 280, 221, 21));
        label_17 = new QLabel(centralwidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(590, 310, 171, 16));
        savepath_line = new QLineEdit(centralwidget);
        savepath_line->setObjectName(QString::fromUtf8("savepath_line"));
        savepath_line->setGeometry(QRect(560, 340, 221, 21));
        save_path_button = new QPushButton(centralwidget);
        save_path_button->setObjectName(QString::fromUtf8("save_path_button"));
        save_path_button->setGeometry(QRect(630, 370, 80, 21));
        to_path_button = new QPushButton(centralwidget);
        to_path_button->setObjectName(QString::fromUtf8("to_path_button"));
        to_path_button->setGeometry(QRect(590, 460, 161, 21));
        label_18 = new QLabel(centralwidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(10, 330, 151, 16));
        label_19 = new QLabel(centralwidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(10, 290, 151, 16));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(170, 650, 72, 19));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(170, 570, 72, 22));
        dateEdit_start = new QDateEdit(centralwidget);
        dateEdit_start->setObjectName(QString::fromUtf8("dateEdit_start"));
        dateEdit_start->setGeometry(QRect(190, 330, 110, 22));
        dateEdit_end = new QDateEdit(centralwidget);
        dateEdit_end->setObjectName(QString::fromUtf8("dateEdit_end"));
        dateEdit_end->setGeometry(QRect(360, 330, 110, 22));
        label_20 = new QLabel(centralwidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(170, 333, 16, 16));
        label_21 = new QLabel(centralwidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(330, 333, 21, 16));
        size_doubleSpinBox = new QDoubleSpinBox(centralwidget);
        size_doubleSpinBox->setObjectName(QString::fromUtf8("size_doubleSpinBox"));
        size_doubleSpinBox->setGeometry(QRect(170, 530, 71, 22));
        focus_doubleSpinBox = new QDoubleSpinBox(centralwidget);
        focus_doubleSpinBox->setObjectName(QString::fromUtf8("focus_doubleSpinBox"));
        focus_doubleSpinBox->setGeometry(QRect(170, 490, 71, 22));
        influence_doubleSpinBox = new QDoubleSpinBox(centralwidget);
        influence_doubleSpinBox->setObjectName(QString::fromUtf8("influence_doubleSpinBox"));
        influence_doubleSpinBox->setGeometry(QRect(170, 450, 71, 22));
        intensity_doubleSpinBox = new QDoubleSpinBox(centralwidget);
        intensity_doubleSpinBox->setObjectName(QString::fromUtf8("intensity_doubleSpinBox"));
        intensity_doubleSpinBox->setGeometry(QRect(170, 410, 71, 22));
        number_spinBox = new QSpinBox(centralwidget);
        number_spinBox->setObjectName(QString::fromUtf8("number_spinBox"));
        number_spinBox->setGeometry(QRect(170, 240, 71, 22));
        number_ods_spinBox = new QSpinBox(centralwidget);
        number_ods_spinBox->setObjectName(QString::fromUtf8("number_ods_spinBox"));
        number_ods_spinBox->setGeometry(QRect(170, 280, 71, 22));
        checkBox_timer = new QCheckBox(centralwidget);
        checkBox_timer->setObjectName(QString::fromUtf8("checkBox_timer"));
        checkBox_timer->setGeometry(QRect(170, 690, 72, 19));
        label_22 = new QLabel(centralwidget);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(10, 690, 151, 16));
        speed_comboBox = new QComboBox(centralwidget);
        speed_comboBox->setObjectName(QString::fromUtf8("speed_comboBox"));
        speed_comboBox->setGeometry(QRect(170, 610, 161, 22));
        speed_comboBox->setEditable(true);
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(600, 650, 141, 23));
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"    text-align: center;\n"
"}"));
        progressBar->setMaximum(100);
        progressBar->setValue(0);
        progressBar->setTextDirection(QProgressBar::TopToBottom);
        sfx_r2 = new QCheckBox(centralwidget);
        sfx_r2->setObjectName(QString::fromUtf8("sfx_r2"));
        sfx_r2->setGeometry(QRect(630, 100, 81, 19));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        create_button->setText(QCoreApplication::translate("MainWindow", "\320\241\320\264\320\265\320\273\320\260\321\202\321\214 \320\276\321\202\321\207\320\265\321\202", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\276\321\202\321\207\320\265\321\202\320\260 \321\201\320\262\321\217\320\267\320\270", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\276\321\202\321\207\320\265\321\202\320\260 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\276\321\202\321\207\320\265\321\202\320\260 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217 \320\275\320\265\320\261\320\276\320\274", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\242\321\200\320\265\320\261\321\203\320\265\320\274\321\213\320\265 \321\201\321\203\321\204\321\204\320\270\320\272\321\201\321\213 ", nullptr));
        sfx_o->setText(QCoreApplication::translate("MainWindow", "o", nullptr));
        sfx_ro1->setText(QCoreApplication::translate("MainWindow", "r01", nullptr));
        sfx_r1->setText(QCoreApplication::translate("MainWindow", "r1", nullptr));
        sfx_r3->setText(QCoreApplication::translate("MainWindow", "r3", nullptr));
        sfx_s->setText(QCoreApplication::translate("MainWindow", "s", nullptr));
        sfx_all->setText(QCoreApplication::translate("MainWindow", "\320\262\321\213\320\261\321\200\320\260\321\202\321\214 \320\262\321\201\320\265", nullptr));
        puth_to_file_button->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\272 \320\277\320\260\320\277\320\272\320\265 \321\201 \320\276\321\202\321\207\320\265\321\202\320\276\320\274", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217 \320\264\320\273\321\217 \321\201\320\276\321\201\321\202\320\260\320\262\320\273\320\265\320\275\320\270\321\217 \320\276\321\202\321\207\320\265\321\202\320\260", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\234\320\227\320\224 \320\220\320\227\320\224\320\232-1.5 \342\204\226", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\222\320\265\321\200\321\201\320\270\321\217 \320\277\321\200\320\276\321\210\320\270\320\262\320\272\320\270", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\320\275\321\201\320\270\320\262\320\275\320\276\321\201\321\202\321\214 ", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\320\222\320\273\320\270\321\217\320\275\320\270\320\265 \320\262\320\265\320\273\320\270\321\207\320\270\320\275\321\213", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\320\244\320\276\320\272\321\203\321\201 ", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217 \320\267\320\262\320\265\320\267\320\264\321\213 ", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\321\200\321\204\320\265\320\271\321\201", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214 \320\270\320\275\321\202\320\265\321\200\321\204\320\265\320\271\321\201\320\260", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\266\320\270\320\274 \320\261\320\270\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "  \320\230\320\274\321\217 \320\276\321\202\321\207\320\265\321\202\320\260 (.pdf)", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\264\320\273\321\217 \321\204\320\276\321\200\320\274\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217 \320\276\321\202\321\207\320\265\321\202\320\260", nullptr));
        save_path_button->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
        to_path_button->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\271\321\202\320\270 \320\262 \320\272\320\260\321\202\320\260\320\273\320\276\320\263", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \320\270\321\201\320\277\321\213\321\202\320\260\320\275\320\270\320\271", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\320\236\320\224\320\241 1 \342\204\226", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276", nullptr));
        checkBox_timer->setText(QCoreApplication::translate("MainWindow", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\321\200\320\276\320\266\320\265\320\262\320\276\320\271 \321\202\320\260\320\271\320\274\320\265\321\200", nullptr));
        sfx_r2->setText(QCoreApplication::translate("MainWindow", "r2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
