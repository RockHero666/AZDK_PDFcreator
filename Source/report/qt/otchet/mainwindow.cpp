#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,progress(0), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RUS");

    this->setWindowTitle("PDF_report");


    ui->name_report_line->setText("azdkclient.tracked.azdk");
    ui->management_report_line->setText("azdkserver.tracked.azdk");
    ui->management_sky_report_line->setText("pdsserver.tracked.azdk");

   // ui->file_name_line->setText("PDF_report.pdf");

    ui->comboBox->addItem("RS485");
    ui->comboBox->addItem("CAN");

    ui->speed_comboBox->addItem("115.2 кбит/с");
    ui->speed_comboBox->addItem("250 кбит/с");
    ui->speed_comboBox->addItem("500 кбит/с");
    ui->speed_comboBox->addItem("1000 кбит/с");
    ui->speed_comboBox->addItem("2000 кбит/с");


    ui->number_spinBox->setRange(0,99999999);
    ui->number_ods_spinBox->setRange(0,99999999);
    ui->focus_doubleSpinBox->setRange(0,99999999);
    ui->influence_doubleSpinBox->setRange(0,99999999);
    ui->intensity_doubleSpinBox->setRange(0,99999999);
    ui->size_doubleSpinBox->setRange(0,99999999);


    QSettings settings("PDF_creator.ini", QSettings::IniFormat);

    ui->number_spinBox->setValue(settings.value("number").toInt());
    ui->size_doubleSpinBox->setValue(settings.value("size").toDouble());
    ui->number_ods_spinBox->setValue(settings.value("number_Ods").toInt());
    ui->focus_doubleSpinBox->setValue(settings.value("focus").toDouble());
    ui->influence_doubleSpinBox->setValue(settings.value("influence").toDouble());
    ui->intensity_doubleSpinBox->setValue(settings.value("intensity").toDouble());
    ui->firmware_line->setText(settings.value("firmware").toString());

    ui->checkBox->setCheckState(Qt::CheckState(settings.value("binar").toInt()));
    on_checkBox_stateChanged(settings.value("binar").toInt());
    ui->checkBox_timer->setCheckState(Qt::CheckState(settings.value("timer").toInt()));
    on_checkBox_timer_stateChanged(settings.value("timer").toInt());

    ui->speed_comboBox->setCurrentIndex(settings.value("speed").toInt());
    ui->comboBox->setCurrentIndex(settings.value("interface_").toInt());

    ui->dateEdit_start->setDate(QDate(settings.value("time_start_y").toInt(),settings.value("time_start_m").toInt(),settings.value("time_start_d").toInt()));
    ui->dateEdit_end->setDate(QDate(settings.value("time_end_y").toInt(),settings.value("time_end_m").toInt(),settings.value("time_end_d").toInt()));


    if(!settings.value("path_to_file_line").toString().isEmpty())
    {


    ui->path_to_file_line->setText(settings.value("path_to_file_line").toString());
    on_path_to_file_line_textChanged(settings.value("path_to_file_line").toString());
    ui->file_name_line->setText(settings.value("file_name_line").toString());
    on_file_name_line_textChanged(settings.value("file_name_line").toString());
    ui->savepath_line->setText(settings.value("savepath_line").toString());
    on_savepath_line_textChanged(settings.value("savepath_line").toString());
    }

   // QWidget *wdg = new QWidget;
    //wdg->show();


}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::error(const QString & massage)
{
     QMessageBox::about(this,"ERROR",massage);
}

bool MainWindow::checker()
{
    if(ui->sfx_all->isChecked()){}
    else if(ui->sfx_o->isChecked()||ui->sfx_ro1->isChecked()||ui->sfx_r1->isChecked()||ui->sfx_r2->isChecked()||ui->sfx_r3->isChecked()||ui->sfx_s->isChecked()){}
    else
        return false;

    if(azdk.size.isEmpty()||azdk.binar.isEmpty()||azdk.focus.isEmpty()||azdk.speed.isEmpty()||
            azdk.number.isEmpty()||azdk.firmware.isEmpty()||azdk.influence.isEmpty()||azdk.intensity.isEmpty()||
            azdk.interface_.isEmpty()||azdk.number_Ods.isEmpty())
        return false;

    if(ui->path_to_file_line->text().isEmpty()||ui->name_report_line->text().isEmpty()||ui->management_report_line->text().isEmpty()||
            ui->management_sky_report_line->text().isEmpty())
        return false;

    if(ui->file_name_line->text().isEmpty()||ui->savepath_line->text().isEmpty())
        return false;

    return true;


}

//////////////////////////////////// SFX menu/////////////////

void MainWindow::on_sfx_all_stateChanged(int arg1)
{
    Q_UNUSED(arg1);

    if(!ui->sfx_all->isChecked())
    {
        if(ui->sfx_o->isEnabled())
        ui->sfx_o->setCheckState(Qt::Unchecked);
        if(ui->sfx_ro1->isEnabled())
        ui->sfx_ro1->setCheckState(Qt::Unchecked);
        if(ui->sfx_r1->isEnabled())
        ui->sfx_r1->setCheckState(Qt::Unchecked);
        if(ui->sfx_r2->isEnabled())
        ui->sfx_r2->setCheckState(Qt::Unchecked);
        if(ui->sfx_r3->isEnabled())
        ui->sfx_r3->setCheckState(Qt::Unchecked);
        if(ui->sfx_s->isEnabled())
        ui->sfx_s->setCheckState(Qt::Unchecked);
    }
    else
    {
        if(ui->sfx_o->isEnabled())
        ui->sfx_o->setCheckState(Qt::Checked);
        if(ui->sfx_ro1->isEnabled())
        ui->sfx_ro1->setCheckState(Qt::Checked);
        if(ui->sfx_r1->isEnabled())
        ui->sfx_r1->setCheckState(Qt::Checked);
        if(ui->sfx_r2->isEnabled())
        ui->sfx_r2->setCheckState(Qt::Checked);
        if(ui->sfx_r3->isEnabled())
        ui->sfx_r3->setCheckState(Qt::Checked);
        if(ui->sfx_s->isEnabled())
        ui->sfx_s->setCheckState(Qt::Checked);
    }

}
/////////////////////////////////////////////////////////////

///////////// AZDC PARAM////////////////////////////////////////////

void MainWindow::on_number_spinBox_valueChanged(const QString &arg1)
{
    azdk.number = arg1;
}

void MainWindow::on_number_ods_spinBox_valueChanged(const QString &arg1)
{
    azdk.number_Ods = arg1;
}


QString MainWindow::setDate()
{
  QDate start = ui->dateEdit_start->date();
  QDate end = ui->dateEdit_end->date();

  if(start == end)
  {
      QString str = QString::number(ui->dateEdit_start->date().day()) + "." +
              QString::number(ui->dateEdit_start->date().month()) + "." +
              QString::number(ui->dateEdit_start->date().year()) + ".";
      return str;
  }
  if(start > end)
  {
      return "error date";
  }
  if(start < end)
  {
      QString start = QString::number(ui->dateEdit_start->date().day()) + "." +
              QString::number(ui->dateEdit_start->date().month()) + "." +
              QString::number(ui->dateEdit_start->date().year()) + ".";
      QString end = QString::number(ui->dateEdit_end->date().day()) + "." +
              QString::number(ui->dateEdit_end->date().month()) + "." +
              QString::number(ui->dateEdit_end->date().year()) + ".";
      return start + " - " + end;
  }

  return "error";

}

void MainWindow::on_firmware_line_textChanged(const QString &arg1)
{
    azdk.firmware = ui->firmware_line->text();
}

void MainWindow::on_intensity_doubleSpinBox_valueChanged(const QString &arg1)
{
    azdk.intensity = arg1;
}

void MainWindow::on_influence_doubleSpinBox_valueChanged(const QString &arg1)
{
    azdk.influence = arg1;
}

void MainWindow::on_focus_doubleSpinBox_valueChanged(const QString &arg1)
{
    azdk.focus = arg1;
}

void MainWindow::on_size_doubleSpinBox_valueChanged(const QString &arg1)
{
    azdk.size = arg1;
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    azdk.interface_=arg1;
}

void MainWindow::on_speed_comboBox_currentTextChanged(const QString &arg1)
{
    azdk.speed = arg1;
}

void MainWindow::on_speed_comboBox_currentIndexChanged(const QString &arg1)
{
    azdk.speed = arg1;
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    azdk.binar = "включен";
    else
    azdk.binar = "отключен";
}

void MainWindow::on_checkBox_timer_stateChanged(int arg1)
{
    if(arg1)
    azdk.timer = "сторожевой таймер включен.";
    else
    azdk.timer = "сторожевого таймера нет или отключен.";
}


/////////////////////////////////////////////////////////////////////////



void MainWindow::on_create_button_clicked()
{

    if(checker())
    {
        try
        {

            pdf_creator.set_template_files(ui->name_report_line->text(),ui->management_report_line->text(),ui->management_sky_report_line->text());
            pdf_creator.set_sfx_state(ui->sfx_s->checkState(),ui->sfx_ro1->checkState(),ui->sfx_r1->checkState(),ui->sfx_r2->checkState(),ui->sfx_r3->checkState(),ui->sfx_o->checkState());
            azdk.time = setDate();
            pdf_creator.set_AZDK(azdk);
            pdf_creator.set_parser(parser);



            connect(&pdf_creator, SIGNAL(progress(int)), ui->progressBar, SLOT(setValue(int)));
            connect(&pdf_creator, SIGNAL(error(const QString &)),this, SLOT(error(const QString &)));

            connect(&thread, &QThread::started, &pdf_creator, &PDF_creator::start);
            connect(&pdf_creator, &PDF_creator::finished, &thread, &QThread::terminate);
            pdf_creator.moveToThread(&thread);

            pdf_creator.set_thread_gate(true);
            thread.start();









            save_state();

        }
        catch (std::runtime_error& ex) {
            throw(ex);
        }
    }
    else
    {
        QMessageBox::about(this,"ERROR","Все поля обязательны к заполнению!");
    }
}

void MainWindow::save_state()
{

    QSettings settings("PDF_creator.ini", QSettings::IniFormat);
    settings.setValue("number",azdk.number);
    settings.setValue("size",ui->size_doubleSpinBox->value());
    settings.setValue("number_Ods",azdk.number_Ods);
    settings.setValue("focus",ui->focus_doubleSpinBox->value());
    settings.setValue("speed",ui->speed_comboBox->currentIndex());
    settings.setValue("firmware",azdk.firmware);
    settings.setValue("influence",ui->influence_doubleSpinBox->value());
    settings.setValue("intensity",ui->intensity_doubleSpinBox->value());

    settings.setValue("interface_",ui->comboBox->currentIndex());

    settings.setValue("binar",ui->checkBox->checkState());
    settings.setValue("timer",ui->checkBox_timer->checkState());


    int d = ui->dateEdit_start->date().day();
    int m = ui->dateEdit_start->date().month();
    int y = ui->dateEdit_start->date().year();

    settings.setValue("time_start_d",d);
    settings.setValue("time_start_m",m);
    settings.setValue("time_start_y",y);


    d = ui->dateEdit_end->date().day();
    m = ui->dateEdit_end->date().month();
    y = ui->dateEdit_end->date().year();

    settings.setValue("time_end_d",d);
    settings.setValue("time_end_m",m);
    settings.setValue("time_end_y",y);


    settings.setValue("path_to_file_line",ui->path_to_file_line->text());
    settings.setValue("file_name_line",ui->file_name_line->text());
    settings.setValue("savepath_line",ui->savepath_line->text());


}

////////////////////////////////////////// PARSER menu////////////////

void MainWindow::on_puth_to_file_button_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this);
    parser.set_path(temp);
    ui->path_to_file_line->setText(temp);
}

void MainWindow::on_path_to_file_line_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty())
    {
    parser.set_path(arg1);
    parser.to_parse();
    }
    check_box_checker();
}

//////////////////////////////////////////////////////////////////////

////////////////////////////////// SAVE param /////////////////////////

void MainWindow::on_save_path_button_clicked()
{
    QString temp = QFileDialog::getExistingDirectory(this);
    pdf_creator.set_save_path(temp);
    ui->savepath_line->setText(temp);
}

void MainWindow::on_savepath_line_textChanged(const QString &arg1)
{
    pdf_creator.set_save_path(arg1);
}

void MainWindow::on_file_name_line_textChanged(const QString &arg1)
{
    pdf_creator.set_file_name(arg1);
}

void MainWindow::on_to_path_button_clicked()
{
    QDesktopServices::openUrl(ui->savepath_line->text());
}
//////////////////////////////////////////////////////////////////////


void MainWindow::check_box_checker()
{


    ui->sfx_s->setDisabled(true);
    ui->sfx_ro1->setDisabled(true);
    ui->sfx_r1->setDisabled(true);
    ui->sfx_r2->setDisabled(true);
    ui->sfx_r3->setDisabled(true);
    ui->sfx_o->setDisabled(true);



    ui->sfx_o->setCheckState(Qt::Unchecked);

    ui->sfx_ro1->setCheckState(Qt::Unchecked);

    ui->sfx_r1->setCheckState(Qt::Unchecked);

    ui->sfx_r2->setCheckState(Qt::Unchecked);

    ui->sfx_r3->setCheckState(Qt::Unchecked);

    ui->sfx_s->setCheckState(Qt::Unchecked);

    ui->sfx_all->setCheckState(Qt::Unchecked);


    for (int i = 0; i <  parser.all_paths.size(); ++i)
    {
         if(parser.all_paths[i].indexOf("s.txt") != -1)
             ui->sfx_s->setDisabled(false);
    }
    for (int i = 0; i <  parser.all_paths.size(); ++i)
    {
         if(parser.all_paths[i].indexOf("r01.txt") != -1)
             ui->sfx_ro1->setDisabled(false);
    }
    for (int i = 0; i <  parser.all_paths.size(); ++i)
    {
         if(parser.all_paths[i].indexOf("r1.txt") != -1)
             ui->sfx_r1->setDisabled(false);
    }
    for (int i = 0; i <  parser.all_paths.size(); ++i)
    {
         if(parser.all_paths[i].indexOf("r2.txt") != -1)
             ui->sfx_r2->setDisabled(false);
    }
    for (int i = 0; i <  parser.all_paths.size(); ++i)
    {
         if(parser.all_paths[i].indexOf("r3.txt") != -1)
             ui->sfx_r3->setDisabled(false);
    }
    for (int i = 0; i <  parser.all_paths.size(); ++i)
    {
         if(parser.all_paths[i].indexOf("o.txt") != -1)
             ui->sfx_o->setDisabled(false);
    }





}









//void MainWindow::on_progressBar_valueChanged(int value)
//{
//    progress +=value;
//    qDebug()<<progress;
    //ui->progressBar->setValue(progress);

//}
