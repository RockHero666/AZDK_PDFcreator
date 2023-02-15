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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "log/logw.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *label_16;
    QLineEdit *file_name_line;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_17;
    QLineEdit *savepath_line;
    QPushButton *save_path_button;
    QSpacerItem *verticalSpacer_4;
    QPushButton *to_path_button;
    QSpacerItem *verticalSpacer_5;
    QPushButton *create_button;
    QProgressBar *progressBar;
    QSpacerItem *verticalSpacer_6;
    QFrame *line_4;
    QFrame *line;
    LogWidget *loger;
    QFrame *line_2;
    QGridLayout *gridLayout;
    QLabel *label_8;
    QLabel *label_22;
    QComboBox *speed_comboBox;
    QLabel *label_6;
    QLabel *label_23;
    QLabel *label_15;
    QSpinBox *duration_spinBox;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer;
    QLabel *label_7;
    QCheckBox *checkBox_timer;
    QSpinBox *number_ods_spinBox;
    QLabel *label_13;
    QDoubleSpinBox *focus_doubleSpinBox;
    QComboBox *comboBox;
    QLabel *label_9;
    QSpinBox *number_spinBox;
    QLabel *label_10;
    QLineEdit *firmware_line;
    QDoubleSpinBox *intensity_doubleSpinBox;
    QDoubleSpinBox *influence_doubleSpinBox;
    QDoubleSpinBox *size_doubleSpinBox;
    QLabel *label_19;
    QCheckBox *checkBox;
    QPushButton *pushButton;
    QLabel *label_18;
    QLabel *label_12;
    QLabel *label_14;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line_3;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *sfx_o;
    QCheckBox *sfx_r1;
    QCheckBox *sfx_r3;
    QCheckBox *sfx_s;
    QCheckBox *sfx_all;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QCheckBox *sfx_ro1;
    QCheckBox *sfx_r2;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_8;
    QGridLayout *gridLayout_2;
    QLineEdit *name_report_line;
    QSpacerItem *verticalSpacer;
    QLabel *label_5;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *path_to_file_line;
    QLineEdit *management_report_line;
    QPushButton *puth_to_file_button;
    QLineEdit *management_sky_report_line;
    QSpacerItem *verticalSpacer_2;
    QFrame *line_5;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1229, 770);
        MainWindow->setMinimumSize(QSize(800, 750));
        MainWindow->setMaximumSize(QSize(111111, 1111111));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_16);

        file_name_line = new QLineEdit(centralwidget);
        file_name_line->setObjectName(QString::fromUtf8("file_name_line"));

        verticalLayout->addWidget(file_name_line);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        label_17 = new QLabel(centralwidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_17);

        savepath_line = new QLineEdit(centralwidget);
        savepath_line->setObjectName(QString::fromUtf8("savepath_line"));

        verticalLayout->addWidget(savepath_line);

        save_path_button = new QPushButton(centralwidget);
        save_path_button->setObjectName(QString::fromUtf8("save_path_button"));

        verticalLayout->addWidget(save_path_button);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        to_path_button = new QPushButton(centralwidget);
        to_path_button->setObjectName(QString::fromUtf8("to_path_button"));

        verticalLayout->addWidget(to_path_button);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        create_button = new QPushButton(centralwidget);
        create_button->setObjectName(QString::fromUtf8("create_button"));

        verticalLayout->addWidget(create_button);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"    text-align: center;\n"
"}"));
        progressBar->setMaximum(100);
        progressBar->setValue(0);
        progressBar->setTextDirection(QProgressBar::TopToBottom);

        verticalLayout->addWidget(progressBar);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);


        gridLayout_4->addLayout(verticalLayout, 4, 3, 1, 1);

        line_4 = new QFrame(centralwidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line_4, 2, 1, 1, 1);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line, 0, 1, 2, 3);

        loger = new LogWidget(centralwidget);
        loger->setObjectName(QString::fromUtf8("loger"));
        loger->setMinimumSize(QSize(480, 720));

        gridLayout_4->addWidget(loger, 0, 4, 5, 1);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line_2, 3, 0, 1, 4);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 4, 0, 1, 1);

        label_22 = new QLabel(centralwidget);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout->addWidget(label_22, 12, 0, 1, 1);

        speed_comboBox = new QComboBox(centralwidget);
        speed_comboBox->setObjectName(QString::fromUtf8("speed_comboBox"));
        speed_comboBox->setEditable(true);

        gridLayout->addWidget(speed_comboBox, 10, 1, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 1, 1, 1);

        label_23 = new QLabel(centralwidget);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout->addWidget(label_23, 13, 0, 1, 1);

        label_15 = new QLabel(centralwidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout->addWidget(label_15, 11, 0, 1, 1);

        duration_spinBox = new QSpinBox(centralwidget);
        duration_spinBox->setObjectName(QString::fromUtf8("duration_spinBox"));

        gridLayout->addWidget(duration_spinBox, 13, 1, 1, 1);

        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 7, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 9, 2, 1, 1);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 1, 0, 1, 1);

        checkBox_timer = new QCheckBox(centralwidget);
        checkBox_timer->setObjectName(QString::fromUtf8("checkBox_timer"));

        gridLayout->addWidget(checkBox_timer, 12, 1, 1, 1);

        number_ods_spinBox = new QSpinBox(centralwidget);
        number_ods_spinBox->setObjectName(QString::fromUtf8("number_ods_spinBox"));

        gridLayout->addWidget(number_ods_spinBox, 2, 1, 1, 1);

        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 9, 0, 1, 1);

        focus_doubleSpinBox = new QDoubleSpinBox(centralwidget);
        focus_doubleSpinBox->setObjectName(QString::fromUtf8("focus_doubleSpinBox"));

        gridLayout->addWidget(focus_doubleSpinBox, 7, 1, 1, 1);

        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 9, 1, 1, 1);

        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 5, 0, 1, 1);

        number_spinBox = new QSpinBox(centralwidget);
        number_spinBox->setObjectName(QString::fromUtf8("number_spinBox"));

        gridLayout->addWidget(number_spinBox, 1, 1, 1, 1);

        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 6, 0, 1, 1);

        firmware_line = new QLineEdit(centralwidget);
        firmware_line->setObjectName(QString::fromUtf8("firmware_line"));

        gridLayout->addWidget(firmware_line, 4, 1, 1, 1);

        intensity_doubleSpinBox = new QDoubleSpinBox(centralwidget);
        intensity_doubleSpinBox->setObjectName(QString::fromUtf8("intensity_doubleSpinBox"));

        gridLayout->addWidget(intensity_doubleSpinBox, 5, 1, 1, 1);

        influence_doubleSpinBox = new QDoubleSpinBox(centralwidget);
        influence_doubleSpinBox->setObjectName(QString::fromUtf8("influence_doubleSpinBox"));

        gridLayout->addWidget(influence_doubleSpinBox, 6, 1, 1, 1);

        size_doubleSpinBox = new QDoubleSpinBox(centralwidget);
        size_doubleSpinBox->setObjectName(QString::fromUtf8("size_doubleSpinBox"));

        gridLayout->addWidget(size_doubleSpinBox, 8, 1, 1, 1);

        label_19 = new QLabel(centralwidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout->addWidget(label_19, 2, 0, 1, 1);

        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 11, 1, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 3, 1, 1, 1);

        label_18 = new QLabel(centralwidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout->addWidget(label_18, 3, 0, 1, 1);

        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 8, 0, 1, 1);

        label_14 = new QLabel(centralwidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout->addWidget(label_14, 10, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 9, 3, 1, 1);


        gridLayout_4->addLayout(gridLayout, 4, 0, 1, 1);

        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line_3, 4, 1, 1, 2);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_7, 8, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 5, 0, 1, 1);

        sfx_o = new QCheckBox(centralwidget);
        sfx_o->setObjectName(QString::fromUtf8("sfx_o"));
        sfx_o->setLayoutDirection(Qt::LeftToRight);

        gridLayout_3->addWidget(sfx_o, 6, 1, 1, 1);

        sfx_r1 = new QCheckBox(centralwidget);
        sfx_r1->setObjectName(QString::fromUtf8("sfx_r1"));

        gridLayout_3->addWidget(sfx_r1, 3, 1, 1, 1);

        sfx_r3 = new QCheckBox(centralwidget);
        sfx_r3->setObjectName(QString::fromUtf8("sfx_r3"));

        gridLayout_3->addWidget(sfx_r3, 5, 1, 1, 1);

        sfx_s = new QCheckBox(centralwidget);
        sfx_s->setObjectName(QString::fromUtf8("sfx_s"));

        gridLayout_3->addWidget(sfx_s, 1, 1, 1, 1);

        sfx_all = new QCheckBox(centralwidget);
        sfx_all->setObjectName(QString::fromUtf8("sfx_all"));

        gridLayout_3->addWidget(sfx_all, 7, 1, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_3->addWidget(label_4);


        gridLayout_3->addLayout(verticalLayout_3, 0, 1, 1, 1);

        sfx_ro1 = new QCheckBox(centralwidget);
        sfx_ro1->setObjectName(QString::fromUtf8("sfx_ro1"));

        gridLayout_3->addWidget(sfx_ro1, 2, 1, 1, 1);

        sfx_r2 = new QCheckBox(centralwidget);
        sfx_r2->setObjectName(QString::fromUtf8("sfx_r2"));

        gridLayout_3->addWidget(sfx_r2, 4, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 6, 2, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 1, 2, 1, 2);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_8, 2, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        name_report_line = new QLineEdit(centralwidget);
        name_report_line->setObjectName(QString::fromUtf8("name_report_line"));

        gridLayout_2->addWidget(name_report_line, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 6, 1, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setScaledContents(true);

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setScaledContents(true);

        gridLayout_2->addWidget(label, 3, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setScaledContents(true);

        gridLayout_2->addWidget(label_2, 4, 0, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setScaledContents(true);

        gridLayout_2->addWidget(label_3, 5, 0, 1, 1);

        path_to_file_line = new QLineEdit(centralwidget);
        path_to_file_line->setObjectName(QString::fromUtf8("path_to_file_line"));

        gridLayout_2->addWidget(path_to_file_line, 1, 0, 1, 2);

        management_report_line = new QLineEdit(centralwidget);
        management_report_line->setObjectName(QString::fromUtf8("management_report_line"));

        gridLayout_2->addWidget(management_report_line, 4, 1, 1, 1);

        puth_to_file_button = new QPushButton(centralwidget);
        puth_to_file_button->setObjectName(QString::fromUtf8("puth_to_file_button"));

        gridLayout_2->addWidget(puth_to_file_button, 1, 2, 1, 1);

        management_sky_report_line = new QLineEdit(centralwidget);
        management_sky_report_line->setObjectName(QString::fromUtf8("management_sky_report_line"));

        gridLayout_2->addWidget(management_sky_report_line, 5, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 0, 0, 2, 1);

        line_5 = new QFrame(centralwidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line_5, 5, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "  \320\230\320\274\321\217 \320\276\321\202\321\207\320\265\321\202\320\260 (.pdf)", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\264\320\273\321\217 \321\204\320\276\321\200\320\274\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217 \320\276\321\202\321\207\320\265\321\202\320\260", nullptr));
        save_path_button->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
        to_path_button->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\271\321\202\320\270 \320\262 \320\272\320\260\321\202\320\260\320\273\320\276\320\263", nullptr));
        create_button->setText(QCoreApplication::translate("MainWindow", "\320\241\320\264\320\265\320\273\320\260\321\202\321\214 \320\276\321\202\321\207\320\265\321\202", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\222\320\265\321\200\321\201\320\270\321\217 \320\277\321\200\320\276\321\210\320\270\320\262\320\272\320\270", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\321\200\320\276\320\266\320\265\320\262\320\276\320\271 \321\202\320\260\320\271\320\274\320\265\321\200", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217 \320\264\320\273\321\217 \321\201\320\276\321\201\321\202\320\260\320\262\320\273\320\265\320\275\320\270\321\217 \320\276\321\202\321\207\320\265\321\202\320\260", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "\320\224\320\273\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214 \320\275\320\260\320\272\320\276\320\277\320\273\320\265\320\275\320\270\321\217", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\266\320\270\320\274 \320\261\320\270\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\320\244\320\276\320\272\321\203\321\201 ", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\234\320\227\320\224 \320\220\320\227\320\224\320\232-1.5 \342\204\226", nullptr));
        checkBox_timer->setText(QCoreApplication::translate("MainWindow", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\321\200\321\204\320\265\320\271\321\201", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\320\275\321\201\320\270\320\262\320\275\320\276\321\201\321\202\321\214 ", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\320\222\320\273\320\270\321\217\320\275\320\270\320\265 \320\262\320\265\320\273\320\270\321\207\320\270\320\275\321\213", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\320\236\320\224\320\241 1 \342\204\226", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\201\321\202\320\260\320\262\320\270\321\202\321\214 \320\264\320\260\321\202\321\203", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \320\270\321\201\320\277\321\213\321\202\320\260\320\275\320\270\320\271", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217 \320\267\320\262\320\265\320\267\320\264\321\213 ", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214 \320\270\320\275\321\202\320\265\321\200\321\204\320\265\320\271\321\201\320\260", nullptr));
        sfx_o->setText(QCoreApplication::translate("MainWindow", "o", nullptr));
        sfx_r1->setText(QCoreApplication::translate("MainWindow", "r1", nullptr));
        sfx_r3->setText(QCoreApplication::translate("MainWindow", "r3", nullptr));
        sfx_s->setText(QCoreApplication::translate("MainWindow", "s", nullptr));
        sfx_all->setText(QCoreApplication::translate("MainWindow", "\320\262\321\213\320\261\321\200\320\260\321\202\321\214 \320\262\321\201\320\265", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\242\321\200\320\265\320\261\321\203\320\265\320\274\321\213\320\265 \321\201\321\203\321\204\321\204\320\270\320\272\321\201\321\213 ", nullptr));
        sfx_ro1->setText(QCoreApplication::translate("MainWindow", "r01", nullptr));
        sfx_r2->setText(QCoreApplication::translate("MainWindow", "r2", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\272 \320\277\320\260\320\277\320\272\320\265 \321\201 \320\276\321\202\321\207\320\265\321\202\320\276\320\274", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\276\321\202\321\207\320\265\321\202\320\260 \321\201\320\262\321\217\320\267\320\270", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\276\321\202\321\207\320\265\321\202\320\260 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\276\321\202\321\207\320\265\321\202\320\260 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217 \320\275\320\265\320\261\320\276\320\274", nullptr));
        puth_to_file_button->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
