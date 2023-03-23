#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QThread>
#include <QTimer>
#include <QProcess>
#include "parser.h"
#include "pdf_creator.h"
#include "azdk.h"
#include "calendar.h"
#include "log/azdklogger.h"



#define ORGANIZATION_NAME "Azmerit"
#define ORGANIZATION_DOMAIN "http://www.azmerit.ru"
#define APPLICATION_NAME "PDF_report"

QT_BEGIN_NAMESPACE
namespace Ui { class MainForm; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

    QTimer timer;
    QThread thread;
    Parser parser;
    PDF_creator *pdf_creator;
    AZDK azdk;
    int progress;
    bool start= 1;
    bool block_ui = 1;
    AzdkLogger save_log;
    Calendar calendar;
    Ui::MainForm* ui;
    bool style = 0;
    QProcess proc;

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

    void style_change(bool style);
    
private slots:

    //////////////////////////////////// SFX menu /////////////////

    void on_sfx_all_stateChanged(int arg1);

    void check_box_checker();

    ///////////////////////////////////////////////////////////////////////

    ////////////////////////////////// PARSER menu ////////////////////////

    void text_path_line_changed(const QString& arg1);

    ///////////////////////////////////////////////////////////////////////

    ////////////////////////////////// SAVE param /////////////////////////

    void text_save_line_changed(const QString& arg1);

    void on_to_path_button_clicked();

    void to_open_path();

    ///////////////////////////////////////////////////////////////////////

    ////////////////////////////////// AZDC PARAM /////////////////////////

    void on_number_spinBox_valueChanged(const QString& arg1);

    void on_number_ods_spinBox_valueChanged(const QString& arg1);

    void on_Calendar_button_clicked();

    void another_window_close();

    void on_firmware_line_textChanged(const QString& arg1);

    void on_intensity_doubleSpinBox_valueChanged(const QString &arg1);

    void on_influence_doubleSpinBox_valueChanged(const QString &arg1);

    void on_focus_doubleSpinBox_valueChanged(const QString &arg1);

    void on_size_doubleSpinBox_valueChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(const QString& arg1);

    void on_speed_comboBox_currentIndexChanged(const QString& arg1);

    void on_speed_comboBox_currentTextChanged(const QString &arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_timer_stateChanged(int arg1);

    void on_duration_spinBox_valueChanged(const QString& arg1);

    ///////////////////////////////////////////////////////////////////////

    ////////////////////////////////// SUPPORT FUNC ///////////////////////

    void ui_load_and_config();
    void save_state();
    void connects();
    bool checker();
    QString setDate();
    void block_unblock_ui();
    void error(const QString& massage);
    void on_create_button_clicked();
    void timer_slot();
    void open_close_logger_button_click();
    void change_style();
    void pict_creator_script(QVector<bool> sfx_state, QVector<bool> parse_resulte);
    void reed_script();
    void script_end_work(int exit_code, QProcess::ExitStatus exitStatus);

    ///////////////////////////////////////////////////////////////////////

};
#endif // MAINWINDOW_H
