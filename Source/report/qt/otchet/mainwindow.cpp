#include <iostream>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QDate>
#include <QSettings>
#include <QDesktopWidget>
#include <iomanip>
#include<QTextCodec>
#include "mainwindow.h"
#include "ui_mainwindow3.h"
#include "ngts/filepathedit.h"

const QString dateFormat = "yyyy.MM.dd";

MainWindow::MainWindow(QWidget* parent)
	: proc(this), QWidget(parent),
	progress(0),
	ui(new Ui::MainForm),
	pdf_creator(PDF_creator::get_instance())
{
	ui->setupUi(this);
	connects();

	this->setWindowFlags(Qt::Window);
	qApp->setWindowIcon(QIcon(":/res/icon.ico"));

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RUS");
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("CP 1251"));

	this->setWindowTitle("PDF_report");

	ui_load_and_config();

	
	
	
	
	
	setFocus();

	
	
}

MainWindow::~MainWindow()
{
	save_log.close(0);
	delete ui;
}

//////////////////////////////////// SFX menu/////////////////

void MainWindow::on_sfx_all_stateChanged(int arg1)
{
	Q_UNUSED(arg1);

	if (!ui->sfx_all->isChecked())
	{
		if (ui->sfx_o->isEnabled())
			ui->sfx_o->setCheckState(Qt::Unchecked);
		if (ui->sfx_ro1->isEnabled())
			ui->sfx_ro1->setCheckState(Qt::Unchecked);
		if (ui->sfx_r1->isEnabled())
			ui->sfx_r1->setCheckState(Qt::Unchecked);
		if (ui->sfx_r2->isEnabled())
			ui->sfx_r2->setCheckState(Qt::Unchecked);
		if (ui->sfx_r3->isEnabled())
			ui->sfx_r3->setCheckState(Qt::Unchecked);
		if (ui->sfx_s->isEnabled())
			ui->sfx_s->setCheckState(Qt::Unchecked);
	}
	else
	{
		if (ui->sfx_o->isEnabled())
			ui->sfx_o->setCheckState(Qt::Checked);
		if (ui->sfx_ro1->isEnabled())
			ui->sfx_ro1->setCheckState(Qt::Checked);
		if (ui->sfx_r1->isEnabled())
			ui->sfx_r1->setCheckState(Qt::Checked);
		if (ui->sfx_r2->isEnabled())
			ui->sfx_r2->setCheckState(Qt::Checked);
		if (ui->sfx_r3->isEnabled())
			ui->sfx_r3->setCheckState(Qt::Checked);
		if (ui->sfx_s->isEnabled())
			ui->sfx_s->setCheckState(Qt::Checked);
	}
}

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

	for (int i = 0; i < parser.all_paths.size(); ++i)
	{
		if (parser.all_paths[i].indexOf("s.txt") != -1 && parser.all_paths[i].indexOf("ss.txt") == -1)
		{
			ui->sfx_s->setDisabled(false);
			break;
		}
	}
	for (int i = 0; i < parser.all_paths.size(); ++i)
	{
		if (parser.all_paths[i].indexOf("r01.txt") != -1)
		{
			ui->sfx_ro1->setDisabled(false);
			break;
		}
	}
	for (int i = 0; i < parser.all_paths.size(); ++i)
	{
		if (parser.all_paths[i].indexOf("r1.txt") != -1)
		{ 
			ui->sfx_r1->setDisabled(false);
			break;
		}
	}
	for (int i = 0; i < parser.all_paths.size(); ++i)
	{
		if (parser.all_paths[i].indexOf("r2.txt") != -1)
		{
			ui->sfx_r2->setDisabled(false);
			break;
		}
	}
	for (int i = 0; i < parser.all_paths.size(); ++i)
	{
		if (parser.all_paths[i].indexOf("r3.txt") != -1)
		{ 
			ui->sfx_r3->setDisabled(false);
			break;
		}
	}
	for (int i = 0; i < parser.all_paths.size(); ++i)
	{
		if (parser.all_paths[i].indexOf("o.txt") != -1)
		{ 
			ui->sfx_o->setDisabled(false);
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////

////////////////////////////////// AZDC PARAM /////////////////////////

void MainWindow::on_number_spinBox_valueChanged(const QString& arg1)
{
	azdk.number = arg1;
}

void MainWindow::on_number_ods_spinBox_valueChanged(const QString& arg1)
{
	azdk.number_Ods = arg1;
}

void MainWindow::on_Calendar_button_clicked()
{
	calendar.close();
	calendar.show();
	ui->create_button->setDisabled(true);
}

void MainWindow::another_window_close()
{
	ui->create_button->setDisabled(false);
	ui->Calendar_button->setText(setDate());
}

void MainWindow::on_firmware_line_textChanged(const QString& arg1)
{
	azdk.firmware = ui->firmware_line->text();
}

void MainWindow::on_intensity_doubleSpinBox_valueChanged(const QString& arg1)
{
	azdk.intensity = arg1;
}

void MainWindow::on_influence_doubleSpinBox_valueChanged(const QString& arg1)
{
	azdk.influence = arg1;
}

void MainWindow::on_focus_doubleSpinBox_valueChanged(const QString& arg1)
{
	azdk.focus = arg1;
}

void MainWindow::on_size_doubleSpinBox_valueChanged(const QString& arg1)
{
	azdk.size = arg1;
}

void MainWindow::on_comboBox_currentIndexChanged(const QString& arg1)
{
	azdk.interface_ = arg1;
}

void MainWindow::on_speed_comboBox_currentTextChanged(const QString& arg1)
{
	azdk.speed = arg1;
}

void MainWindow::on_speed_comboBox_currentIndexChanged(const QString& arg1)
{
	azdk.speed = arg1;
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
	if (arg1)
		azdk.binar = "включен";
	else
		azdk.binar = "отключен";
}

void MainWindow::on_checkBox_timer_stateChanged(int arg1)
{
	if (arg1)
		azdk.timer = "сторожевой таймер включен";
	else
		azdk.timer = "сторожевого таймера нет или отключен";
}

void MainWindow::on_duration_spinBox_valueChanged(const QString& arg1)
{
	azdk.duration = arg1;
}

///////////////////////////////////////////////////////////////////////

////////////////////////////////// PARSER menu ////////////////////////

void MainWindow::text_path_line_changed(const QString& arg1)
{
	if (!arg1.isEmpty())
	{
		parser.set_path(arg1);
		parser.to_parse_current_dir();
		auto date = parser.parse_calendar_date_from_file();

		if (date.size())
		{
			calendar.set_date_begin(date[0]);
			calendar.set_date_end(date[1]);
			another_window_close();// Первоначальная надпись на кнопке в слоте закрытия календаря
		}
		else
			ui->Calendar_button->setText("Выставить дату");

	}
	check_box_checker();

	QString number;

	for (int i = 0; i < parser.all_paths.size(); i++) // автозаполнения номера отчета
	{
		if (parser.all_paths[i].indexOf(ui->name_report_line->text()) != -1)
		{
			QStringList sl = parser.all_paths[i].split("/");
			std::string str = sl.last().toStdString();


			for (int j = 0; j < str.size(); j++)
			{
				if (isdigit(str[j]))
				{
					number += str[j];
					continue;
				}
				else if (!number.isEmpty())
					break;
			}

			int x = number.toInt();
			ui->number_spinBox->setValue(x);
		}
	}

	


}

///////////////////////////////////////////////////////////////////////

////////////////////////////////// SAVE param /////////////////////////

void MainWindow::text_save_line_changed(const QString& arg1)
{
	pdf_creator->set_save_path(ui->fpe_2->getPath());

	QStringList sl = ui->fpe_2->getPath().split("/");

	pdf_creator->set_file_name(sl.last());

	if (ui->fpe_2->getPath().indexOf(".pdf") == -1)
		ui->fpe_2->setPath(ui->fpe_2->getPath() + ".pdf");
}

void MainWindow::on_to_path_button_clicked()
{
	QString p;
	QStringList sl = ui->fpe_2->getPath().split("/");
	for (int i = 0; i < sl.size()-1; i++) // Реконструирование пути без имени файла
	{
		p += sl[i] + "/";
	}
	QDesktopServices::openUrl(QUrl::fromLocalFile(p));
}

void MainWindow::to_open_path()
{
	QDesktopServices::openUrl(QUrl::fromLocalFile(ui->fpe_2->getPath()));
}

///////////////////////////////////////////////////////////////////////

////////////////////////////////// SUPPORT FUNC ///////////////////////

void MainWindow::ui_load_and_config()
{
	timer.start(1000);
	save_log.open("log.json", LogType::Common, "json");


	ui->open_file->setDisabled(true);
	ui->loger->hide();
	ui->progressBar->hide();

	ui->loger_button->setIcon(QIcon(":/res/res/r.png"));


	

	QVector<QString> fonts = parser.font_pars();
	for (int i = 0; i < fonts.size(); i++)
	{
		ui->comboBox_fonts->addItem(fonts[i]);
	}
	
	
	change_style();// первичная инициализация стиля




	ui->name_report_line->setText("azdkclient.tracked.azdk");
	ui->management_report_line->setText("azdkserver.tracked.azdk");
	ui->management_sky_report_line->setText("pdsserver.tracked.azdk");

	ui->comboBox->addItem("RS485");
	ui->comboBox->addItem("CAN");

	ui->speed_comboBox->addItem("115.2 кбит/с");
	ui->speed_comboBox->addItem("250 кбит/с");
	ui->speed_comboBox->addItem("500 кбит/с");
	ui->speed_comboBox->addItem("1000 кбит/с");
	ui->speed_comboBox->addItem("2000 кбит/с");

	ui->number_spinBox->setRange(0, 99999999);
	ui->number_ods_spinBox->setRange(0, 99999999);
	ui->focus_doubleSpinBox->setRange(0, 99999999);
	ui->influence_doubleSpinBox->setRange(0, 99999999);
	ui->intensity_doubleSpinBox->setRange(0, 99999999);
	ui->size_doubleSpinBox->setRange(0, 99999999);
	ui->duration_spinBox->setRange(0, 99999999);

	ui->intensity_doubleSpinBox->setSingleStep(0.1);
	ui->influence_doubleSpinBox->setSingleStep(0.05);
	ui->focus_doubleSpinBox->setSingleStep(0.05);
	ui->size_doubleSpinBox->setSingleStep(0.25);
	ui->duration_spinBox->setSingleStep(10);

	load_ini(ini_path);


	
}

void MainWindow::load_ini(QString & path)
{
	QSettings settings(path, QSettings::IniFormat);
	settings.setIniCodec("UTF-8");

	QVector<QString> fonts = parser.font_pars();
	for (int i = 0; i < fonts.size(); i++)
	{
		QString temp = settings.value("PDF_font").toString();

		temp[0] = settings.value("PDF_font").toString()[0].toLower();
		QString d_case = temp;

		temp[0] = settings.value("PDF_font").toString()[0].toUpper();
		QString u_case = temp;

		if (fonts[i].indexOf(d_case) != -1 || fonts[i].indexOf(u_case) != -1)
		{
			ui->comboBox_fonts->setCurrentIndex(i);
			break;
		}
	}

	ui->number_spinBox->setValue(settings.value("azdk_number").toInt());
	ui->size_doubleSpinBox->setValue(settings.value("image_size").toDouble());
	ui->number_ods_spinBox->setValue(settings.value("ods_number").toInt());
	ui->focus_doubleSpinBox->setValue(settings.value("focus").toDouble());
	ui->influence_doubleSpinBox->setValue(settings.value("mag_factor").toDouble());
	ui->intensity_doubleSpinBox->setValue(settings.value("image_intensity").toDouble());
	ui->firmware_line->setText(settings.value("firmware_ver").toString());
	ui->duration_spinBox->setValue(settings.value("exp_duration").toInt());

	ui->checkBox->setChecked(settings.value("binary_mode").toBool());
	//on_checkBox_stateChanged(settings.value("binary_mode").toBool());
	ui->checkBox_timer->setChecked(settings.value("watchdog").toBool());
	//on_checkBox_timer_stateChanged(settings.value("timer").toInt());

	//ui->speed_comboBox->setCurrentIndex(settings.value("speed").toInt());
	ui->speed_comboBox->setCurrentText(settings.value("speed").toString());
	//ui->comboBox->setCurrentIndex(settings.value("comm_interface").toInt());
	ui->comboBox->setCurrentText(settings.value("comm_interface").toString());

	//if (settings.value("time_start_y").toBool() && settings.value("time_start_m").toBool() && settings.value("time_start_d").toBool() &&
	//	settings.value("time_end_y").toBool() && settings.value("time_end_m").toBool(), settings.value("time_end_d").toBool())
	//{
	//	calendar.set_date_begin(settings.value("time_start_y").toInt(), settings.value("time_start_m").toInt(), settings.value("time_start_d").toInt());
	//	calendar.set_date_end(settings.value("time_end_y").toInt(), settings.value("time_end_m").toInt(), settings.value("time_end_d").toInt());
	//	another_window_close();// Первоначальная надпись на кнопке в слоте закрытия календаря
	//}

	auto startDate = QDate::fromString(settings.value("time_start").toString(), dateFormat);
	auto endDate = QDate::fromString(settings.value("time_end").toString(), dateFormat);
	calendar.set_date_begin(startDate);
	calendar.set_date_end(endDate);
	another_window_close();

	if (settings.value("AZDK_ver").toBool())
		azdk.ver = settings.value("AZDK_ver").toString();

	if (!settings.value("data_dir").toString().isEmpty())
	{
		ui->fpe->setPath(settings.value("data_dir").toString());
		ui->fpe_2->setPath(settings.value("output_file").toString());
	}

}

void MainWindow::save_state()
{
	QSettings settings("PDF_creator.ini", QSettings::IniFormat);
	settings.setIniCodec("UTF-8");
	settings.setValue("azdk_number", azdk.number);
	settings.setValue("image_size", ui->size_doubleSpinBox->value());
	settings.setValue("ods_number", azdk.number_Ods);
	settings.setValue("focus", ui->focus_doubleSpinBox->value());
	settings.setValue("speed", ui->speed_comboBox->currentText());
	settings.setValue("firmware_ver", azdk.firmware);
	settings.setValue("mag_factor", ui->influence_doubleSpinBox->value());
	settings.setValue("image_intensity", ui->intensity_doubleSpinBox->value());
	settings.setValue("exp_duration", ui->duration_spinBox->value());
	settings.setValue("comm_interface", ui->comboBox->currentText());

	settings.setValue("binary_mode", ui->checkBox->isChecked());
	settings.setValue("watchdog", ui->checkBox_timer->isChecked());

	//int d = calendar.get_date_begin().day();
	//int m = calendar.get_date_begin().month();
	//int y = calendar.get_date_begin().year();
	//
	//settings.setValue("time_start_d", d);
	//settings.setValue("time_start_m", m);
	//settings.setValue("time_start_y", y);
	//
	//d = calendar.get_date_end().day();
	//m = calendar.get_date_end().month();
	//y = calendar.get_date_end().year();
	//
	//settings.setValue("time_end_d", d);
	//settings.setValue("time_end_m", m);
	//settings.setValue("time_end_y", y);

	settings.setValue("time_start", calendar.get_date_begin().toString(dateFormat));
	settings.setValue("time_end", calendar.get_date_end().toString(dateFormat));

	settings.setValue("data_dir", ui->fpe->getPath());

	settings.setValue("output_file", ui->fpe_2->getPath());

	settings.setValue("AZDK_ver", azdk.ver);

	settings.setValue("PDF_font", ui->comboBox_fonts->currentText());
}

void MainWindow::connects()
{

	connect(&proc, &QProcess::readyReadStandardOutput, this, &MainWindow::reed_script);
	connect(&proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &MainWindow::script_end_work);

	connect(this, &MainWindow::style_change, ui->loger, &LogWidget::style_changed);

	connect(ui->style_button, &QPushButton::clicked, this, &MainWindow::change_style);

	connect(&timer, SIGNAL(timeout()), this, SLOT(timer_slot()));

	connect(ui->Calendar_button, &QPushButton::clicked, this, &MainWindow::on_Calendar_button_clicked);
	connect(ui->open_file, &QPushButton::clicked, this, &MainWindow::to_open_path);
	connect(ui->fpe, &FilePathEdit::pathChanged, this, &MainWindow::text_path_line_changed);
	connect(ui->fpe_2, &FilePathEdit::pathChanged, this, &MainWindow::text_save_line_changed);
	connect(ui->loger_button, &QPushButton::clicked, this, &MainWindow::open_close_logger_button_click);

	connect(pdf_creator, SIGNAL(progress(int)), ui->progressBar, SLOT(setValue(int)));
	connect(pdf_creator, SIGNAL(error(const QString&)), this, SLOT(error(const QString&)));

	connect(&thread, &QThread::started, pdf_creator, &PDF_creator::start);
	connect(pdf_creator, &PDF_creator::finished, &thread, &QThread::terminate);
	connect(pdf_creator, &PDF_creator::finished, this, &MainWindow::exit);
	connect(pdf_creator, &PDF_creator::unblock_ui, this, &MainWindow::block_unblock_ui);

	connect(&calendar, &Calendar::finished, this, &MainWindow::another_window_close);


	connect(pdf_creator, &PDF_creator::log_message, 
		[&](auto& message, auto color) 
		{
			ui->loger->addLog(message, 0, color);
			save_log.log(message); 
			
		});
	connect(&parser, &Parser::log_message, 
		[&](auto& message, auto color) 
		{
			ui->loger->addLog(message, 0, color);
			save_log.log(message); 
			
		});
}

bool MainWindow::checker()
{
	if (ui->sfx_o->isChecked() || ui->sfx_ro1->isChecked() || ui->sfx_r1->isChecked() || ui->sfx_r2->isChecked() || ui->sfx_r3->isChecked() || ui->sfx_s->isChecked()) {}
	else
		return false;

	if (azdk.size.isEmpty() || azdk.binar.isEmpty() || azdk.focus.isEmpty() || azdk.speed.isEmpty() ||
		azdk.number.isEmpty() || azdk.firmware.isEmpty() || azdk.influence.isEmpty() || azdk.intensity.isEmpty() ||
		azdk.interface_.isEmpty() || azdk.number_Ods.isEmpty() || azdk.duration.isEmpty())
		return false;

	if (ui->fpe->getPath().isEmpty() || ui->name_report_line->text().isEmpty() || ui->management_report_line->text().isEmpty() ||
		ui->management_sky_report_line->text().isEmpty())
		return false;

	if (ui->fpe_2->getPath().isEmpty())
		return false;

	return true;
}

QString MainWindow::setDate()
{
	QDate start = calendar.get_date_begin();
	QDate end = calendar.get_date_end();

	if (start == end)
	{
		QString st = calendar.get_date_begin().toString("dd. MMMM. yyyy.");
		return st;
	}
	if (start < end)
	{
		QString st = calendar.get_date_begin().toString("dd. MMMM. yyyy.");
		QString en = calendar.get_date_end().toString("dd. MMMM. yyyy.");
		return st + " - " + en;
	}
	return "error";
}

void MainWindow::block_unblock_ui()
{
	block_ui = 1;
	
	if (ui->progressBar->isHidden())
	{
		ui->progressBar->show();
		if (style)
		{
			ui->indicator->setPixmap(QPixmap(":/res/res/indicator_off.png"));
			ui->open_file->setDisabled(true);
		}
		else
		{
			ui->indicator->setPixmap(QPixmap(":/res/res/indicator_off_white_style.png"));
			ui->open_file->setDisabled(true);
		}
	}
	else
	{
		ui->progressBar->hide();
		ui->indicator->setPixmap(QPixmap(":/res/res/indicator_on.png"));
		ui->open_file->setDisabled(false);
	}

	bool state;
	if (ui->fpe->isEnabled())
		state = 1;
	else
		state = 0;

	ui->fpe->setDisabled(state);
	ui->name_report_line->setDisabled(state);
	ui->management_report_line->setDisabled(state);
	ui->management_sky_report_line->setDisabled(state);
	ui->number_spinBox->setDisabled(state);
	ui->number_ods_spinBox->setDisabled(state);
	ui->size_doubleSpinBox->setDisabled(state);
	ui->focus_doubleSpinBox->setDisabled(state);
	ui->influence_doubleSpinBox->setDisabled(state);
	ui->intensity_doubleSpinBox->setDisabled(state);
	ui->firmware_line->setDisabled(state);
	ui->duration_spinBox->setDisabled(state);
	ui->checkBox->setDisabled(state);
	ui->checkBox_timer->setDisabled(state);
	ui->comboBox->setDisabled(state);
	ui->speed_comboBox->setDisabled(state);
	ui->Calendar_button->setDisabled(state);
	ui->fpe->setDisabled(state);
	ui->fpe_2->setDisabled(state);
	
	ui->fpe_2->setDisabled(state);

	ui->create_button->setDisabled(state);

	if (state)
	{
		ui->sfx_o->setDisabled(state);
		ui->sfx_s->setDisabled(state);
		ui->sfx_r1->setDisabled(state);
		ui->sfx_r2->setDisabled(state);
		ui->sfx_r3->setDisabled(state);
		ui->sfx_ro1->setDisabled(state);
		ui->sfx_all->setDisabled(state);
	}
	else
	{
		check_box_checker();
		ui->sfx_all->setDisabled(state);
	}
}

void MainWindow::error(const QString& massage)
{
	QMessageBox::about(this, "ERROR", massage);
}

void MainWindow::on_create_button_clicked()
{
	if (checker())
	{

		QVector<bool> sfx_state{ ui->sfx_s->isChecked() ,ui->sfx_ro1->isChecked(),ui->sfx_r1->isChecked()
		,ui->sfx_r2->isChecked(),ui->sfx_r3->isChecked(),ui->sfx_o->isChecked() };
		QVector<bool> result_pack = parser.parse_for_pict_script(azdk.number, sfx_state);

		if (sfx_state[0] != result_pack[0]|| sfx_state[1] != result_pack[1] || sfx_state[2] != result_pack[2]
			|| sfx_state[3] != result_pack[3] || sfx_state[4] != result_pack[4] || sfx_state[5] != result_pack[5])
			pict_creator_script(sfx_state, result_pack);
		else
		{


			try
			{


				pdf_creator->set_template_files(ui->name_report_line->text(), ui->management_report_line->text(), ui->management_sky_report_line->text());
				pdf_creator->set_sfx_state(ui->sfx_s->checkState(), ui->sfx_ro1->checkState(), ui->sfx_r1->checkState(), ui->sfx_r2->checkState(), ui->sfx_r3->checkState(), ui->sfx_o->checkState());
				azdk.time = setDate();
				pdf_creator->set_AZDK(azdk);
				pdf_creator->set_parser(parser);
				pdf_creator->set_font_name(ui->comboBox_fonts->currentText());

				pdf_creator->moveToThread(&thread);
				pdf_creator->set_thread_gate(true);
				thread.start();

				if(block_ui)
				block_unblock_ui();

				save_state();




			}
			catch (std::runtime_error& ex) {
				throw(ex);
			}
		}
	}
	else
	{
		QMessageBox::about(this, "ERROR", "Все поля обязательны к заполнению!");
	}
}

void MainWindow::timer_slot()
{
	QSettings settings("PDF_creator.ini", QSettings::IniFormat);
	settings.setIniCodec("UTF-8");

	if (settings.value("AZDK_ver").toBool())
		azdk.ver = settings.value("AZDK_ver").toString();
}

void MainWindow::open_close_logger_button_click()
{
	if (ui->loger_button->isChecked())
		ui->loger_button->setIcon(QIcon(":/res/res/l.png"));
	else
		ui->loger_button->setIcon(QIcon(":/res/res/r.png"));
}

void MainWindow::change_style()
{

	if (style)
	{
		emit style_change(style);

		QPalette palette = qApp->style()->standardPalette();
		palette.setColor(palette.Text, Qt::black);
		
		qApp->setPalette(palette);

		ui->sfx_o->setStyleSheet("");
		ui->sfx_ro1->setStyleSheet("");
		ui->sfx_r1->setStyleSheet("");
		ui->sfx_r2->setStyleSheet("");
		ui->sfx_r3->setStyleSheet("");
		ui->sfx_s->setStyleSheet("");
		ui->sfx_all->setStyleSheet("");


		ui->open_file->setStyleSheet("");
		ui->create_button->setStyleSheet("");
		

		style = 0;
	}
	else
	{
		emit style_change(style);

		QPalette palette;
		palette.setColor(palette.Window, QColor(53, 53, 53));
		palette.setColor(palette.WindowText, Qt::white);
		palette.setColor(palette.Base, QColor(25, 25, 25));
		palette.setColor(palette.AlternateBase, QColor(53, 53, 53));
		palette.setColor(palette.ToolTipBase, Qt::black);
		palette.setColor(palette.ToolTipText, Qt::white);
		palette.setColor(palette.Text, Qt::white);
		palette.setColor(palette.Button, QColor(53, 53, 53));
		palette.setColor(palette.ButtonText, Qt::white);
		palette.setColor(palette.BrightText, Qt::red);
		palette.setColor(palette.Link, QColor(42, 130, 218));
		palette.setColor(palette.Highlight, QColor(42, 130, 218));
		palette.setColor(palette.HighlightedText, Qt::black);

		qApp->setPalette(palette);

		QString sheet = "QCheckBox::disabled {color: darkgray;}";

		ui->sfx_o->setStyleSheet(sheet);
		ui->sfx_ro1->setStyleSheet(sheet);
		ui->sfx_r1->setStyleSheet(sheet);
		ui->sfx_r2->setStyleSheet(sheet);
		ui->sfx_r3->setStyleSheet(sheet);
		ui->sfx_s->setStyleSheet(sheet);
		ui->sfx_all->setStyleSheet(sheet);

		sheet = "QPushButton::disabled {color: darkgray;}";

		ui->open_file->setStyleSheet(sheet);
		ui->create_button->setStyleSheet(sheet);

		style = 1;
	}
}

void MainWindow::pict_creator_script(QVector<bool> sfx_state, QVector<bool> parse_resulte)
{
	block_unblock_ui();
	block_ui = 0;
	ui->progressBar->setValue(0);
	ui->loger->addLog("Запущен скрипт создания графиков",0, qRgb(90, 200, 90));

	QVector<QString> presset{ "s","r01","r1","r2","r3","o" };
	//QVector<bool> result_pack{ 0, 0, 0, 0, 0, 0 };
	QVector<QString> arg_names;

	for (int i = 0; i < presset.size(); i++)
	{
			arg_names.push_back("azdk" + azdk.number + presset[i] );
	}
	

	QStringList arguments;
	arguments << (("-w" + ui->fpe->getPath() + "/"));

	for (int i = 0; i < arg_names.size(); i++)
	{
		if ( parse_resulte[i] == 0 && sfx_state[i])
			arguments << ("-p" + arg_names[i]);

	}
	

	proc.start("pdsstats.exe", arguments);

	

}

void MainWindow::reed_script()
{

	QString str = proc.readAll();
	save_log.log(str);

	if(str.indexOf("%") != -1)
	{
		int pos = str.lastIndexOf(QChar('%'));
		ui->progressBar->setValue(str.left(pos).toInt());
		std::cout << str.left(pos).toStdString() << std::endl;
	}
}

void MainWindow::script_end_work(int exit_code, QProcess::ExitStatus exitStatus)
{
	save_log.log("Script exit code = " + QString::number(exit_code));
	proc.close();

	ui->loger->addLog("Скрипт успешно завершил работу",0, qRgb(90, 200, 90));
	on_create_button_clicked();
}

void MainWindow::exit()
{
	if (no_gui_finish)
		qApp->exit();
}

void MainWindow::set_ini_file(QString& path)
{
	ini_path = path;
	load_ini(ini_path);

	QSettings settings(ini_path, QSettings::IniFormat);
	settings.setIniCodec("UTF-8");

	ui->sfx_s->setChecked(settings.value("sfx_s").toBool());
	ui->sfx_ro1->setChecked(settings.value("sfx_ro1").toBool());
	ui->sfx_r1->setChecked(settings.value("sfx_r1").toBool());
	ui->sfx_r2->setChecked(settings.value("sfx_r2").toBool());
	ui->sfx_r3->setChecked(settings.value("sfx_r3").toBool());
	ui->sfx_o->setChecked(settings.value("sfx_o").toBool());

	on_create_button_clicked();

	no_gui_finish = 1;


}
