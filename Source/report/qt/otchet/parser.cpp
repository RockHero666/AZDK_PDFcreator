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

}




void Parser::set_path(const QString & path)
{
    this->path = path;
}

void Parser::set_serial_num(const QString & serial)
{
    this->serial_num = serial;
}

 QVector<QVector<QString>> Parser::parse_resulte_table(const QString & error_path)
 {

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
         throw std::runtime_error("bad_path");

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

     return SKO;

 }

 QVector<int> Parser::parse_resulte_table_2_ver2(const QString & client_path,const QString & server_path)
 {
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
         throw std::runtime_error("bad_path");


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
         throw std::runtime_error("bad_path");

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

     return table_value;


 }


QVector<int> Parser::parse_resulte_table_2(const QString & client_path,const QString & server_path)
{
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
       throw std::runtime_error("bad_path");;


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


    //////////////////////////////////////////////////////////////////////////////////////////////

    if(client.open(QIODevice::Text|QIODevice::ReadOnly)) // парсим весь файл клиента
    {
        while (!client.atEnd())
        {
            all_text = client.readAll();
            client.close();
        }
    }
    else
        throw std::runtime_error("bad_path");

    file_line = all_text.split('\n'); // разделяем единую строку на лист стрингов по разделителю


    int x= 0;
    for(int i = 0 ; i < file_line.size() ; i++)  //парс всего файла по строкам клиента  с записью дат и значений в векторы
    {
        int y=0;
        QStringList line = file_line[i].split(';');
        if(line.size()==10) // требуется тест!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! сомнения
        {
            vect_value.push_back(QVector<int>());

            client_time.push_back(line[y++]);

            for(int i = 0; i < 9;i++)
                vect_value[x].push_back(line[y++].toInt());

            x++;
        }
    }

    if(!is_orbital)
    {
        int it1 = Find_time_on_vector(client_time,server_time[0],1); // ищем индекс первого схождения
        int it2 = Find_time_on_vector(client_time,server_time[1],0); // ищем индекс последнего схождения


        for(int i = 0 ; i < vect_value[0].size() ; i++)
        {
            result.push_back( vect_value[it2][i] - vect_value[it1][i]); // забиваем новый вектор готовыми результатами
        }
    }
    else
    {
        for(int i = 0 ; i < vect_value[0].size() ; i++)
        {
            result.push_back( vect_value[vect_value.size()-1][i] - vect_value[0][i]); // забиваем новый вектор готовыми результатами
        }
    }



    for(int i = 0 ; i < result.size() ; i++) // превращаем числовой массив в строку для таблици
    {
        table_value.push_back( result[i] );
    }

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

QVector<QString> Parser::Frames_count_and_time(const QString & server_path,const QString & index)
{
    QString s_path = path + server_path + index +".txt";
    QFile server(s_path);
    QString all_text;
    QStringList file_line;

    int count = 0;
    QVector<QString> vect_str;
    QVector<QTime> vect_time;
    int index_of_start;
    QVector<QString> result;
    bool is_orbital=false;


    if(server.open(QIODevice::Text|QIODevice::ReadOnly)) // парсим весь файл сервера
    {
        all_text = server.readAll();
        server.close();
    }
    else
        throw std::runtime_error("bad_path");


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
            for (int i = 0;i< vect_time.size()-3;i++) // подсчет реального количества кадров    не засчитывает первый тест при разнице часов
            {
                if(vect_time[i].hour() == vect_time[i+1].hour())
                {
                    if((vect_time[i].second() == vect_time[i+1].second() ||
                        vect_time[i].second() == vect_time[i+1].second()-1||
                        vect_time[i].second() == vect_time[i+1].second()-2) &&
                            vect_time[i].minute() == vect_time[i+1].minute()-j) // требуются тесты
                    {
                        index_of_start = i;
                        for (;i< vect_time.size();i++)
                        {
                            count++;
                        }
                        break;
                    }
                }
                else{
                    if((vect_time[i].second() == vect_time[i+1].second() ||
                        vect_time[i].second() == vect_time[i+1].second()-1||
                        vect_time[i].second() == vect_time[i+1].second()-2) &&
                            time_step_converter( vect_time[i],j) == vect_time[i+1].minute())
                    {
                        index_of_start = i;
                        for (;i< vect_time.size();i++)
                        {
                            count++;
                        }
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

    if(index != "s")
    count -=1;// последний тест не учитывается    дурак придумал не могу сам объяснить ....  кажется из за последнй точки кват. {0.0.0}

    result.push_back(QString::number(count));

    QTime start(vect_time[index_of_start]);
    QTime end(vect_time[vect_time.size()-2]);

    //if(index == "s")
       // end = vect_time[vect_time.size()-1];


    auto time_betwin = [=](QTime start,QTime end) mutable
    {
        for (int i = 0;;i++)
        {
            if(start.hour()==end.hour())
                if(start.minute()==end.minute())
                    return i;

            start = start.addSecs(60);
        }
    };





  //qint64 mm_time  = start.msecsTo(end);
  //qint64 s_time = mm_time/1000;
  //qint64 m_time = s_time/60;
    int m_time = time_betwin(start,end);
  int time = m_time/(vect_time.size()-(index_of_start+2));

  if(!is_orbital)
      result.push_back(QString::number(time));
  else
      result.push_back(QString::number(m_time));

    return result;
}

 QString Parser::Png_path_veryf(const QString & path)
{

    QString png_path = this->path + path;
    QString result;

    auto it_c = std::find(all_paths.begin(),all_paths.end(),png_path);
    if(it_c == all_paths.end())
    {
        result ="error.png";
        return result;
    }
    result = png_path;
    return result;


}


 QVector<QString> Parser::Frames_count_and_time_ver2(const QString & server_path,const QString & azdk_server_path,const QString & index)
 {
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
     bool is_orbital=false;
     QTime last_time;




     if(azdk_server.open(QIODevice::Text|QIODevice::ReadOnly)) // парсим весь файл сервера
     {
         all_text = azdk_server.readAll();
         azdk_server.close();
     }
     else
         throw std::runtime_error("bad_path");


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
         throw std::runtime_error("bad_path");


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
                         index_of_start = i;
                         //for (;i < vect_time.size()-1;i++)
                         //{
                         //    count++;
                         //}
                         i++;
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
                         index_of_start = i;
                        // for (;i< vect_time.size()-1;i++)
                         //{
                         //    count++;
                         //}
                         i++;
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

     result.push_back(QString::number(count));

     if(result[0] == "29")  // костыль
         result[0] = "30";


     QTime start(vect_time[index_of_start]);
     QTime end(vect_time[vect_time.size()-1]);

     //if(index == "s")
        // end = vect_time[vect_time.size()-1];


     auto time_betwin = [=](QTime start,QTime end) mutable
     {
         for (int i = 0;;i++)
         {
             if(start.hour()==end.hour())
                 if(start.minute()==end.minute())
                     return i;

             start = start.addSecs(60);
         }
     };





   //qint64 mm_time  = start.msecsTo(end);
   //qint64 s_time = mm_time/1000;
   //qint64 m_time = s_time/60;
   int m_time = time_betwin(start,end);
   int time = m_time/(vect_time.size()-(index_of_start+2));

   if(!is_orbital)
       result.push_back(QString::number(time));
   else
       result.push_back(QString::number(m_time));

     return result;


 }

