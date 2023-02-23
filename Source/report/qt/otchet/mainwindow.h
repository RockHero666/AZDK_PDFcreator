#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QApplication>
#include <QMainWindow>
#include <QFileDialog>
#include <QDesktopServices>
#include "parser.h"
#include "pdf_creator.h"
#include "azdk.h"
#include <QDate>
#include <QSettings>
#include "calendar.h"
#include "log/azdklogger.h"

#define ORGANIZATION_NAME "Azmerit"
#define ORGANIZATION_DOMAIN "http://www.azmerit.ru"
#define APPLICATION_NAME "PDF_report"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QThread thread;

    const QString sfx[5]  {"o","r01","r1","r3","s"};
    Parser parser;
    PDF_creator pdf_creator;
    AZDK azdk;

    int progress;

    Calendar calendar;

    int test=0;
    bool start= 1;
    AzdkLogger save_log;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   

    bool checker();

    void check_box_checker();

public slots:
    void error(const QString & massage);
    void message_to_log(const QString & message, QRgb color = QRgb());

private slots:
    void on_sfx_all_stateChanged(int arg1);



    QString setDate();

    void on_firmware_line_textChanged(const QString &arg1);



    void on_comboBox_currentIndexChanged(const QString &arg1);



    void on_checkBox_stateChanged(int arg1);



    void on_create_button_clicked();

    void on_puth_to_file_button_clicked();

    void text_path_line_changed(const QString& arg1);

    void on_path_to_file_line_textChanged(const QString &arg1);

    void on_savepath_line_textChanged(const QString &arg1);

    void text_save_line_changed(const QString& arg1);

    void on_save_path_button_clicked();

    void on_file_name_line_textChanged(const QString &arg1);

    void on_to_path_button_clicked();

    void to_open_path();









    void save_state();







    void on_intensity_doubleSpinBox_valueChanged(const QString &arg1);

    void on_influence_doubleSpinBox_valueChanged(const QString &arg1);

    void on_focus_doubleSpinBox_valueChanged(const QString &arg1);

    void on_size_doubleSpinBox_valueChanged(const QString &arg1);

    void on_number_spinBox_valueChanged(const QString &arg1);

    void on_number_ods_spinBox_valueChanged(const QString &arg1);

    void on_duration_spinBox_valueChanged(const QString &arg1);



    void on_checkBox_timer_stateChanged(int arg1);

    void on_speed_comboBox_currentTextChanged(const QString &arg1);

    void on_speed_comboBox_currentIndexChanged(const QString &arg1);

   // void on_progressBar_valueChanged(int value);

    void on_pushButton_clicked();

    void another_window_close();





private:
    Ui::MainWindow *ui;
    void ui_load_and_config();
    void block_unblock_ui();
};
#endif // MAINWINDOW_H
