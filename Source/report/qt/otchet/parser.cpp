#include <QDirIterator>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QTime>
#include <QDate>
#include <iostream>
#include <algorithm>
#include <QStandardPaths>
#include "parser.h"

Parser::Parser(QObject *parent) : QObject(parent)
{

}

void Parser::to_parse()
{
    if(all_paths.size())
        all_paths.clear();

    QDirIterator it(path,  QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
       all_paths.push_back(it.next());

    emit log_message("Парсинг всех путей");

}

void Parser::to_parse_current_dir()
{
    if(all_paths.size())
        all_paths.clear();

    QDirIterator it(path,  QDir::Files, QDirIterator::QDirIterator::NoIteratorFlags);
    while (it.hasNext())
       all_paths.push_back(it.next());

    emit log_message("Парсинг корневых путей");
}

void Parser::set_path(const QString & path)
{

    this->path = path;
}

 QVector<QVector<QString>> Parser::parse_resulte_table(const QString & error_path)
 {
     emit log_message("Извлечение данных для СКО таблици");

     QString e_path = path + error_path;
     QString all_text;

     QVector<QVector<QString>> SKO;

     QStringList line;
     QStringList file_line;
     QFile error(e_path);


     auto it_e = std::find(all_paths.begin(),all_paths.end(),e_path);
     if(it_e == all_paths.end())
     {
         SKO.resize(30);
         return SKO;
     }

     if(error.open(QIODevice::Text|QIODevice::ReadOnly)) // парсим весь файл ерора
     {
         all_text = error.readAll();
         error.close();
     }
     else
     {
         emit log_message("Ошибка в пути к файлам! Path = " + e_path,qRgb(255,0,0));
         throw std::runtime_error("bad_path");
     }

     file_line = all_text.split('\n'); // разделяем единую строку на лист стрингов по разделителю

     for(int i = 1 ; i < file_line.size() ; i++) // Разделение строки на отдельные значения
     {
              line += file_line[i].split(";");
     }


     int y= 1;
     int x=0;
     for(int i = 1 ; ; i++) // конвертор листа стрингов в двумерный вектор даблов
     {

         if(y == line.size())
             break;

         SKO.push_back(QVector<QString>());

         for(int i = 0; i < 13;i++)
             SKO[x].push_back(line[y++]);
         x++;
         y++;



     }

     emit log_message("Данные извлечены");
     return SKO;

 }

 QVector<int> Parser::parse_resulte_table_2_ver2(const QString & client_path,const QString & server_path)
 {

     emit log_message("Извлечение данных результатов функциональных испытаний МЗД");

     QString c_path = path + client_path;
     QString s_path = path + server_path;
     QString all_text;

     QFile client(c_path);
     QFile server(s_path);

     QVector<QString> client_time;
     QVector<QString> server_time;
     QVector<QVector<int>> vect_value;
     QVector<int> result;
     QVector<int> table_value;

     QStringList file_line;
     bool is_orbital = false;

     auto it_c = std::find(all_paths.begin(),all_paths.end(),c_path);
     auto it_s = std::find(all_paths.begin(),all_paths.end(),s_path);
     if(it_c == all_paths.end() || it_s == all_paths.end())
     {
         table_value.resize(20);
         return table_value;
     }

     if(server.open(QIODevice::Text|QIODevice::ReadOnly)) // парсим весь файл сервера
     {
         all_text = server.readAll();
         server.close();
     }
     else
     {
         emit log_message("Ошибка в пути к файлам! Path = " + s_path, qRgb(255, 0, 0));
         throw std::runtime_error("bad_path");
     }


     file_line = all_text.split('\n'); // разделяем единую строку на лист стрингов по разделителю


     for(int i = 0 ; i < file_line.size() ; i++)  // поиск времени начала испытания в сервере
     {
         if(file_line[i].indexOf("Установлена угловая скорость") != -1||
                 file_line[i].indexOf("orbital quaternion") != -1)
         {
             if(file_line[i].indexOf("orbital quaternion") != -1)
                 is_orbital = true;

             QStringList line = file_line[i].split(";");
             server_time.push_back(line[0]);
             break;
         }

     }

     for(int i = file_line.size()-1 ; i > 0 ; i--) // поиск времени конца испытания в сервере
     {
         if(file_line[i].indexOf("Установлена угловая скорость") != -1||
                 file_line[i].indexOf("orbital quaternion") != -1)
         {
             if(file_line[i].indexOf("orbital quaternion") != -1)
                 is_orbital = true;

             QStringList line = file_line[i].split(";");
             server_time.push_back(line[0]);
             break;
         }

     }
    ////////////////////////////////////////////////////////////////////////////////

     if(client.open(QIODevice::Text|QIODevice::ReadOnly)) // парсим весь файл клиента
     {
         while (!client.atEnd())
         {
             all_text = client.readAll();
             client.close();
         }
     }
     else
     {
         emit log_message("Ошибка в пути к файлам! Path = " + c_path, qRgb(255, 0, 0));
         throw std::runtime_error("bad_path");
     }

     file_line = all_text.split('\n'); // разделяем единую строку на лист стрингов по разделителю


     int x= 0;
     for(int i = 0 ; i < file_line.size() ; i++)  //парс всего файла по строкам клиента  с записью дат и значений в векторы
     {
         int y=0;
         QStringList line = file_line[i].split(';');
         if(line.size()==10)
         {
             vect_value.push_back(QVector<int>());

             client_time.push_back(line[y++]);

             for(int i = 0; i < 9;i++)
                 vect_value[x].push_back(line[y++].toInt());

             x++;
         }
     }

     int it2 = Find_time_on_vector(client_time,server_time[1],0); // ищем индекс последнего схождения


     for(int j = 0 ; j < vect_value.size() ; j++)
     {

         if(vect_value[j][5] == vect_value[j+1][5]) //&& vect_value[j+1][5] == vect_value[j+2][5])
         {

             for(int i = 0 ; i < vect_value[0].size() ; i++)
             {


                 result.push_back( vect_value[it2][i] - vect_value[j][i]); // забиваем новый вектор готовыми результатами
             }
             break;
         }
         else if(j== 10)
         {



             for(int i = 0 ; i < vect_value[0].size() ; i++)
             {


                 result.push_back( vect_value[it2][i] - vect_value[0][i]); // забиваем новый вектор готовыми результатами
             }
             break;


         }
     }

     for(int i = 0 ; i < result.size() ; i++) // превращаем числовой массив в строку для таблици dipracate
     {
         table_value.push_back( result[i] );
     }


      emit log_message("Данные извлечены");
     return table_value;


 }

QTime Parser::Str_to_time(const QString & str)
{
    QStringList S_list = str.split(":");
    QStringList S_list2 = S_list[2].split(".");
    S_list[2] = S_list2[0];
    QTime time(S_list[0].toInt(),S_list[1].toInt(),S_list[2].toInt());
    return time;
}

int Parser::time_step_converter(QTime time,int add)
{
    for(int i = 0 ; i<add ; i++)
    {
      time =  time.addSecs(60);
    }

    return time.minute();
}

int Parser::time_subtraction(QTime time,int sub)
{
    int _time=time.second();


      _time -=sub;

      if(_time<0)
          _time +=60;


    return _time;
}

int Parser::Find_time_on_vector(QVector<QString>& time_vect ,QString time , bool up_or_down_state)
{
    if(up_or_down_state)
    {
        for(int j = 0 ;  ; j++)
        {
            for(int i = 0 ; i < time_vect.size() ; i++)
            {
                if(Str_to_time(time_vect[i]) == Str_to_time(time).addSecs(j))
                    return i;
            }
        }
    }
    else
    {
        for(int j = 0 ;  ; j++)
        {
            for(int i = 0 ; i < time_vect.size() ; i++)
            {
                if(Str_to_time(time_vect[i]) == Str_to_time(time).addSecs(-j))
                    return i;
            }
        }
    }

    return time_vect.size()-1;

}

 QString Parser::Png_path_veryf(const QString & path)
{
    QString png_path = this->path + path;
    QString result;

    auto it_c = std::find(all_paths.begin(),all_paths.end(),png_path);
    if(it_c == all_paths.end())
    {
        result ="error.png";
        emit log_message("Некоторые картинки отсутствовали и были заменены на шаблонный файл.", qRgb(255, 0, 0));
        return result;
    }
    result = png_path;
    std::string str = png_path.toLocal8Bit();
    return result;
}

 QVector<QString> Parser::Frames_count_and_time_ver2(const QString & server_path,const QString & azdk_server_path,const QString & index,const QString & azdk_number)
 {
     emit log_message(tr("Извлечение данных времени испытаний и их количества"));

     QString s_path = path + server_path + index +".txt";
     QFile server(s_path);
     QString azdk_s_path = path + azdk_server_path + index +".txt";
     QFile azdk_server(azdk_s_path);


     QString all_text;
     QStringList file_line;
     int count = 0;
     QVector<QString> vect_str;
     QVector<QTime> vect_time;
     int index_of_start;
     QVector<QString> result;
     bool is_orbital = false;
     QTime last_time;

     if(azdk_server.open(QIODevice::Text|QIODevice::ReadOnly)) // парсим весь файл сервера
     {
         all_text = azdk_server.readAll();
         azdk_server.close();
     }
     else
     {
         emit log_message("Ошибка в пути к файлам! Path = " + azdk_s_path, qRgb(255, 0, 0));
         throw std::runtime_error("bad_path");
     }

     file_line = all_text.split('\n'); // разделяем единую строку на лист стрингов по разделителю


     for (int i = file_line.size()-1;i > 0; i--) {
         if(file_line[i].indexOf("{") != -1)
         {

             QString time;
             int time_length =14;

             for (int j = 0;j<time_length;j++)
             {
                 time += file_line[i][j];
             }


             last_time=Str_to_time(time);
             break;
         }

     }


     if(server.open(QIODevice::Text|QIODevice::ReadOnly)) // парсим весь файл сервера
     {
         all_text = server.readAll();
         server.close();
     }
     else
     {
         emit log_message("Ошибка в пути к файлам! Path = " + s_path, qRgb(255, 0, 0));
     throw std::runtime_error("bad_path");
     }


     file_line = all_text.split('\n'); // разделяем единую строку на лист стрингов по разделителю


     if(index == "s")
     {
         for(int i = 0 ; i < file_line.size() ; i++)  // парсинг всего времени сервера
         {
             if(file_line[i].indexOf("Установлен кватернион") != -1)
             {


                 QString time;
                 int time_length =14;

                 for (int j = 0;j<time_length;j++)
                 {
                     time += file_line[i][j];
                 }

                 vect_str.push_back(time);

                 if(Str_to_time(vect_str.last()) == last_time)
                     break;

             }

         }
     }
     else
     {
         for(int i = 0 ; i < file_line.size() ; i++)  // парсинг всего времени сервера
         {
             if(file_line[i].indexOf("Установлена угловая скорость") != -1 ||
                     file_line[i].indexOf("orbital quaternion") != -1)
             {
                 if(file_line[i].indexOf("orbital quaternion") != -1)
                     is_orbital = true;

                 QString time;
                 int time_length =14;

                 for (int j = 0;j<time_length;j++)
                 {
                     time += file_line[i][j];
                 }

                 vect_str.push_back(time);

             }
         }
     }

     for (int i = 0;i< vect_str.size();i++) // конвертация в QTime
     {
         vect_time.push_back(Str_to_time(vect_str[i]));

     }

     if(!is_orbital)
     {
         for (int j = 1;j< vect_time.size();j++)
         {
             if(count != 0)
                 break;
             for (int i = 0;i< vect_time.size()-3;i++) // подсчет реального количества кадров
             {
                 if(vect_time[i].hour() == vect_time[i+1].hour())
                 {
                     if((vect_time[i].second() == vect_time[i+1].second() ||
                         vect_time[i].second() == time_subtraction(vect_time[i+1],1)||
                         vect_time[i].second() == time_subtraction(vect_time[i+1],2) ||
                         vect_time[i].second() == time_subtraction(vect_time[i+1],3)||
                         vect_time[i].second() == time_subtraction(vect_time[i+1],4)||
                         vect_time[i].second() == time_subtraction(vect_time[i+1],5)||
                         vect_time[i].second() == time_subtraction(vect_time[i+1],6)||
                         vect_time[i].second() == time_subtraction(vect_time[i+1],30))&&
                         vect_time[i].minute() == vect_time[i+1].minute()-j) // требуются тесты
                     {

                         //for (;i < vect_time.size()-1;i++)
                         //{
                         //    count++;
                         //}
                         i++;
                         index_of_start = i;
                         count = vect_time.size()-i;
                         break;
                     }
                 }
                 else{
                     if((vect_time[i].second() == vect_time[i+1].second() ||
                         vect_time[i].second() == time_subtraction(vect_time[i+1],1)||
                         vect_time[i].second() == time_subtraction(vect_time[i+1],2) ||
                         vect_time[i].second() == time_subtraction(vect_time[i+1],3)||
                         vect_time[i].second() == time_subtraction(vect_time[i+1],4)||
                         vect_time[i].second() == time_subtraction(vect_time[i+1],5)||
                         vect_time[i].second() == time_subtraction(vect_time[i+1],6)||
                         vect_time[i].second() == time_subtraction(vect_time[i+1],30))&&
                             time_step_converter( vect_time[i],j) == vect_time[i+1].minute())
                     {

                        // for (;i< vect_time.size()-1;i++)
                         //{
                         //    count++;
                         //}
                         i++;
                         index_of_start = i;
                         count = vect_time.size()-i;
                         break;
                     }
                 }


             }
         }
     }
     else
     {
         index_of_start=0;
         count = vect_time.size();
     }


     //if(index != "s")
    // count -=1;// последний тест не учитывается    дурак придумал не могу сам объяснить ....  кажется из за последнй точки кват. {0.0.0}

     result.push_back(QString::number(error_count("/azdk" + azdk_number + index + "/errors.csv")));

     //if(result[0] == "29")  // костыль
         //result[0] = "30";


     QTime start(vect_time[index_of_start]);
     QTime end(vect_time[vect_time.size()-1]);

     //if(index == "s")
        // end = vect_time[vect_time.size()-1];


     auto time_betwin = [=](QTime start,QTime end,int step) mutable
     {

         int steps;
         for (int i = 0;;i++)
         {
             if(start.hour()==end.hour())
                 if(start.minute()==end.minute())
                 {
                     steps = i;
                     break;
                 }

             start = start.addSecs(step);
         }

         return steps;
     };



     auto time_step = [=](QTime start,QTime end) mutable
     {

        for (int i = 5;;i++)
         {
         if(vect_time[index_of_start].second()  == time_subtraction(vect_time[index_of_start+1],i))
         {
             return i;

         }
         }
     };



   //qint64 mm_time  = start.msecsTo(end);
   //qint64 s_time = mm_time/1000;
   //qint64 m_time = s_time/60;
   int step = time_step(start,end);
   int time = time_betwin(start,end,step);

   QTime s(0,0,0);

   for (int i = 0;i<time;i++)
   {
    s=s.addSecs(step);
   }



   //int time1 = m_time/(vect_time.size()-(index_of_start+2));


   if(!is_orbital)
   {

       if(step>=60)
       {
           int time1 = time/(vect_time.size()-(index_of_start+2));
           result.push_back(QString::number(time1));
           result.push_back(QString::number(1));
        }
       else
       {
           result.push_back(QString::number(step));
           result.push_back(QString::number(0));

       }
   }
   else
   {
       result.push_back(QString::number(s.minute()));

           result.push_back(QString::number(1));


    }

     emit log_message("Данные извлечены");
     return result;


 }

 int Parser::error_count(const QString & error_path)
 {
     QString e_path = path + error_path;
     QString all_text;

     QVector<QVector<QString>> SKO;

     QStringList line;
     QStringList file_line;
     QFile error(e_path);




     if(error.open(QIODevice::Text|QIODevice::ReadOnly)) // парсим весь файл ерора
     {
         all_text = error.readAll();
         error.close();
     }
     else
     {
         emit log_message("Ошибка в пути к файлам! Path = " + e_path, qRgb(255, 0, 0));
         throw std::runtime_error("bad_path");
     }

     file_line = all_text.split('\n'); // разделяем единую строку на лист стрингов по разделителю

       int n = 0;
     for (int i = 0;i<file_line.size();i++)
     {
          if(!file_line[i].isEmpty())
            n++;
     }

     return n-1;
 }

 bool Parser::is_exists(const QString& path)
 {
     QStringList sl = path.split("/");
     QString dir_p;

     for (int i = 0 ; i<sl.size()-1 ; i++)
     {
         if(i==0)
         dir_p += sl[i];
         else
         dir_p += "/"+ sl[i];
     }

     
     QDirIterator it(dir_p, QDir::Files, QDirIterator::NoIteratorFlags);
     while (it.hasNext())
     {
         if (path == it.next())
             return true;
     }
     return false;


 }

 QVector<QString> Parser::font_pars()
 {
     QStringList path = QStandardPaths::standardLocations(QStandardPaths::FontsLocation);
     QVector<QString> all_f;
     QVector<QString> true_p_f;
     QStringList split;
     QVector<QString> names_fonts_b;
     QVector<QString> names_fonts;

     QDirIterator it(path[0], QDir::Files, QDirIterator::NoIteratorFlags);
     while (it.hasNext())
     {
         all_f.push_back(it.next());
     }
     

     for (int i = 0; i < all_f.size(); i++)
     {
         if (all_f[i].indexOf("b.ttf") != -1 || all_f[i].indexOf("bd.ttf") != -1)
             true_p_f.push_back(all_f[i]);
     }

     for (int i = 0; i < true_p_f.size(); i++)
     {
         split += true_p_f[i].split("/");
     }
      
     for (int i = 0; i < split.size(); i++)
     {
         if (split[i].indexOf("b.ttf") != -1 || split[i].indexOf("bd.ttf") != -1)
             names_fonts_b.push_back(split[i]);
     }


     for (int i = 0; i < names_fonts_b.size(); i++)
     {
         int indx_b = names_fonts_b[i].indexOf("b.ttf");
         int indx_bd = names_fonts_b[i].indexOf("bd.ttf");
         int indx = indx_b > indx_bd ? indx_b : indx_bd;

         QString name;
             for (int j = 0; j < indx; j++)
             {
                name += names_fonts_b[i][j];
             }
             names_fonts.push_back(name);
             names_fonts[i][0] = names_fonts[i][0].toUpper();
     }

     


     return names_fonts;



 }

 QVector<QDate> Parser::parse_calendar_date_from_file()
 {
     QVector<QDateTime> date;
     QVector<QDate> result_date;
     QVector<QDateTime> min_max_date;
     

     if (all_paths.size())
         all_paths.clear();

     QDirIterator it(path, QDir::Files, QDirIterator::QDirIterator::NoIteratorFlags);
     while (it.hasNext())
         all_paths.push_back(it.next());

     for (int i = 0; i < all_paths.size(); i++)
     {
         QFileInfo file = all_paths[i];

         if (file.suffix() == "txt")
             date.push_back( file.lastModified());

     }

     if (date.size())
     {
         min_max_date.push_back(date[0]);
         min_max_date.push_back(date[0]);

         for (int i = 0; i < date.size() - 1; i++)
         {

             if (min_max_date[0] > date[i])
                 min_max_date[0] = date[i];

             if (min_max_date[1] < date[i])
                 min_max_date[1] = date[i];

         }

         result_date.push_back(min_max_date[0].date());
         result_date.push_back(min_max_date[1].date());


     }
     return result_date;

 }

 QVector<bool> Parser::parse_for_pict_script(QString azdk_num , QVector<bool> sfx_pressed)
 {
     QVector<QString> presset { "s","r01","r1","r2","r3","o" };
     QVector<bool> result_pack{ 0, 0, 0, 0, 0, 0 };
     QVector<QString> dir_names;

     for (int i = 0; i < presset.size(); i++)
     {
         if (sfx_pressed[i])
         dir_names.push_back("azdk" + azdk_num + presset[i]);
     }




     QVector<QString> temp_path;

     QDirIterator it(path, QDir::Dirs, QDirIterator::NoIteratorFlags);
     while (it.hasNext())
         temp_path.push_back(it.next());


     QVector<QString> path_2d;

     for (int i = 2; i < temp_path.size(); i++)
     {
         path_2d.push_back(temp_path[i].split("/").last());

     }

     for (int j = 0; j < dir_names.size(); j++)
     {


         for (int i = 0; i < path_2d.size(); i++)
         {
             if (path_2d[i] == dir_names[j])
             {
                 if (dir_names[j].indexOf("s") != -1 && dir_names[j].indexOf("ss.txt") == -1)
                     result_pack[0] = 1;
                 else if (dir_names[j].indexOf("r01") != -1)
                     result_pack[1] = 1;
                 else if (dir_names[j].indexOf("r1") != -1)
                     result_pack[2] = 1;
                 else if (dir_names[j].indexOf("r2") != -1)
                     result_pack[3] = 1;
                 else if (dir_names[j].indexOf("r3") != -1)
                     result_pack[4] = 1;
                 else if (dir_names[j].indexOf("o") != -1)
                     result_pack[5] = 1;


             }
         }
     }


     return result_pack;
 }

