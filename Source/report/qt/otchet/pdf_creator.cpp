#include "pdf_creator.h"
#include "hpdf.h"
#include <QStandardPaths>
#include <QFontDatabase>
#include <QRegularExpression>



int PDF_creator::count = 1;

PDF_creator* PDF_creator::pdf_ptr = nullptr;

void PDF_creator::error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void* user_data)
{
    Q_UNUSED(user_data);
    /* throw exception when an error has occured */
    std::cout << "ERROR: error_no= " << std::hex << error_no << std::dec << " detail_no = " << detail_no << "/n";
    if(pdf_ptr)
        emit pdf_ptr->log_message(QString::asprintf("%x", error_no));
    throw std::runtime_error("handler_error");
}

 PDF_creator::PDF_creator(const QString& font_name,QObject *parent) :font_name(font_name), QObject(parent)  
 {
     pdf_ptr = this;
 }

 PDF_creator::~PDF_creator()
 {
     //free();
     emit finished();
 }

 void PDF_creator::set_thread_gate(bool val)
 {
     thread_gate = val;
 }

 void PDF_creator::calantitul(int page)
 {


          QString str;

HPDF_Page_BeginText(pages[page]);
HPDF_Page_SetRGBFill(pages[page],0.700,0.700,0.700);
          print_text(page,rus_std,QString::number(page+1).toStdString().c_str(),12,HPDF_Page_GetWidth(pages[page])/2,HPDF_Page_GetHeight(pages[page]) - 15);
HPDF_Page_EndText(pages[page]);

          if(azdk.ver.isEmpty())
              str = "ФИ АЗДК-1.5 №" + azdk.number;
          else
              str = "ФИ "+azdk.ver+" №" + azdk.number;

HPDF_Page_BeginText(pages[page]);
          print_text(page,rus_std,str.toStdString().c_str(),12,HPDF_Page_GetWidth(pages[page])/2+100,HPDF_Page_GetHeight(pages[page]) - 15);
          HPDF_Page_SetRGBFill(pages[page],0,0,0);
HPDF_Page_EndText(pages[page]);



 }

 std::string PDF_creator::minute_validator(int min,bool flag60)
 {
     std::string str;

     QTime time(0,0,0);

     if(flag60)
     time = time.addSecs(min*60);
     else
     time = time.addSecs(min);

     if(time.hour() > 0)
     {
         if(time.hour() >= 20)
         {
             if(time.hour() == 21)
                 str = "21 часу ";
             else
                 str= std::to_string(time.hour()) + " часов ";

         }
         else
         {

             if(time.hour() == 1)
                 str = "1 часу ";
             else if(time.hour() >= 2 && time.hour() < 5)
                 str= std::to_string(time.hour()) + " часа ";
             else
                 str= std::to_string(time.hour()) + " часов ";
         }
     }



     if(time.minute() > 0)
     {
         if(time.minute() >= 20)
         {
             if(time.minute() == 20)
                 str += "20 минут ";
             else if(time.minute() >= 21 && time.minute() < 25)
                 str += std::to_string(time.minute()) + " минуты ";
             else
                 str += std::to_string(time.minute()) + " минут ";

         }
         else
         {

             if(time.minute() == 1)
                 str += "1 минуте ";
             else if(time.minute() >= 2 && time.minute() < 5)
                 str += std::to_string(time.minute()) + " минуты ";
             else
                 str += std::to_string(time.minute()) + " минут ";
         }
     }

     if(time.second() > 0)
     {
         if(time.second() >= 20)
         {
             if(time.second() == 20)
                 str += "20 секунд ";
             else if(time.second() >= 21 && time.second() < 25)
                 str += std::to_string(time.second()) + " секунды ";
             else
                 str += std::to_string(time.second()) + " секунд ";

         }
         else
         {

             if(time.second() == 1)
                 str += "1 секунде ";
             else if(time.second() >= 2 && time.second() < 5)
                 str += std::to_string(time.second()) + " секунды ";
             else
                 str += std::to_string(time.second()) + " секунд ";
         }
     }


     return str;

 }



 void PDF_creator::top_of_graph(int pos,double height,int start_table,int std_cell,int long_cell,int PAGE_HEIGHT,int PAGE_WIDTH , int page)
 {
     int height1 = height-40;
     int height2 = height-20;
    /* Draw vertical lines. */
     HPDF_Page_MoveTo (pages[page], start_table + pos, PAGE_HEIGHT - height1);
     HPDF_Page_LineTo (pages[page], start_table + pos, PAGE_HEIGHT - height);

     HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT - height1);
     HPDF_Page_LineTo (pages[page], start_table+pos, PAGE_HEIGHT - height);

     HPDF_Page_MoveTo (pages[page], (start_table+=long_cell)+pos, PAGE_HEIGHT - height2);
     HPDF_Page_LineTo (pages[page], start_table+pos, PAGE_HEIGHT - height);

     HPDF_Page_MoveTo (pages[page], (start_table+=long_cell)+pos, PAGE_HEIGHT - height2);
     HPDF_Page_LineTo (pages[page], start_table+pos, PAGE_HEIGHT - height);

     HPDF_Page_MoveTo (pages[page], (start_table+=long_cell)+pos, PAGE_HEIGHT - height1);
     HPDF_Page_LineTo (pages[page], start_table+pos, PAGE_HEIGHT - height);

     HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT - height2);
     HPDF_Page_LineTo (pages[page], start_table+pos, PAGE_HEIGHT - height);

     HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT - height2);
     HPDF_Page_LineTo (pages[page], start_table+pos, PAGE_HEIGHT - height);

     HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT - height1);
     HPDF_Page_LineTo (pages[page], start_table+pos, PAGE_HEIGHT - height);

     HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT - height2);
     HPDF_Page_LineTo (pages[page], start_table+pos, PAGE_HEIGHT - height);

     HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT - height2);
     HPDF_Page_LineTo (pages[page], start_table+pos, PAGE_HEIGHT - height);

     HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT - height1);
     HPDF_Page_LineTo (pages[page], start_table+pos, PAGE_HEIGHT - height);

     start_table = 40;

     /* Draw horizontal lines. */

     HPDF_Page_MoveTo (pages[page], start_table+pos, PAGE_HEIGHT - height1);
     HPDF_Page_LineTo (pages[page], PAGE_WIDTH-85, PAGE_HEIGHT - height1);

     HPDF_Page_MoveTo (pages[page], start_table+pos+std_cell, PAGE_HEIGHT - height2);
     HPDF_Page_LineTo (pages[page], PAGE_WIDTH-85, PAGE_HEIGHT - height2);

     HPDF_Page_Stroke (pages[page]);

     std::string str1 = " №                          Углы ориентации,°                            Отклонения                  СКО";
     std::string str2 = "сер.             α                       δ                       φ              Δx,″     Δy,″    Δz,″    Δx,″     Δy,″    Δz,″";

     start_table = 48;

     HPDF_Page_BeginText(pages[page]);
                 print_text(page,rus_std,str1.c_str(),10,start_table+pos,PAGE_HEIGHT -height1-15);
     HPDF_Page_EndText(pages[page]);
     HPDF_Page_BeginText(pages[page]);
                 print_text(page,rus_std,str2.c_str(),10,start_table+pos,PAGE_HEIGHT -height2-15);
     HPDF_Page_EndText(pages[page]);

 }



 void PDF_creator::draw_graph (int page,QVector<QVector<QString>> & vect_value)
 {

      const int PAGE_WIDTH = HPDF_Page_GetWidth(pages[page]);
      const int PAGE_HEIGHT = HPDF_Page_GetHeight(pages[page]);



     HPDF_Page_SetLineWidth (pages[page], 0.5);



     int pos = 50;
     double height = 120.05;
     int start_table = 40;
     int std_cell = 30;
     int long_cell = 70;


 if(vect_value_size == 0)
 {
     top_of_graph(pos,height,start_table,std_cell,long_cell,PAGE_HEIGHT,PAGE_WIDTH,page);

HPDF_Page_BeginText(pages[page]);
     QString text = "Таблица "+QString::number(ris_t++)+" Результаты СКО серий измерений с нулевой угловой скоростью";
     print_text(page_count-1,rus_std,text.toStdString().c_str(),12,90,HPDF_Page_GetHeight(pages[page_count-1]) - 50);
HPDF_Page_EndText(pages[page]);
 }


     /* Draw vertical lines. */
         HPDF_Page_MoveTo (pages[page], start_table + pos, PAGE_HEIGHT - height);
         HPDF_Page_LineTo (pages[page], start_table + pos, height);

         HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT - height);
         HPDF_Page_LineTo (pages[page], start_table+pos, height);

         HPDF_Page_MoveTo (pages[page], (start_table+=long_cell)+pos, PAGE_HEIGHT - height);
         HPDF_Page_LineTo (pages[page], start_table+pos, height);

         HPDF_Page_MoveTo (pages[page], (start_table+=long_cell)+pos, PAGE_HEIGHT - height);
         HPDF_Page_LineTo (pages[page], start_table+pos, height);

         HPDF_Page_MoveTo (pages[page], (start_table+=long_cell)+pos, PAGE_HEIGHT - height);
         HPDF_Page_LineTo (pages[page], start_table+pos, height);

         HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT - height);
         HPDF_Page_LineTo (pages[page], start_table+pos, height);

         HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT - height);
         HPDF_Page_LineTo (pages[page], start_table+pos, height);

         HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT - height);
         HPDF_Page_LineTo (pages[page], start_table+pos, height);

         HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT - height);
         HPDF_Page_LineTo (pages[page], start_table+pos, height);

         HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT - height);
         HPDF_Page_LineTo (pages[page], start_table+pos, height);

         HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT - height);
         HPDF_Page_LineTo (pages[page], start_table+pos, height);





    start_table = 40;

    int y = PAGE_HEIGHT - height;
     /* Draw horizontal lines. */
     for (int i = 0; i <= 30; i++) {


         HPDF_Page_MoveTo (pages[page], start_table+pos, y);
         HPDF_Page_LineTo (pages[page], PAGE_WIDTH-85, y);


        y -= 20;
     }

    HPDF_Page_Stroke (pages[page]);



    if(vect_value_size == 0)
    vect_value_size = vect_value.size();




    y = PAGE_HEIGHT - height-15;
    if(vect_value_size>=30)
    {
        for (int i = 0; i < 30; ++i) // переделат ьвложенным циклом!
        {
            double tw;
            start_table = 117;

HPDF_Page_BeginText(pages[page]);
            print_text(page,rus_std,QString::number(numer_of_line++).toStdString().c_str(),10,51+pos,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][4].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][4].toStdString().c_str(),10,(start_table+=long_cell)-tw,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][5].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][5].toStdString().c_str(),10,(start_table+=long_cell)-tw,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][6].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][6].toStdString().c_str(),10,(start_table+=long_cell)-tw,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][7].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][7].toStdString().c_str(),10,(start_table+=std_cell)-tw,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][8].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][8].toStdString().c_str(),10,(start_table+=std_cell)-tw,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][9].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][9].toStdString().c_str(),10,(start_table+=std_cell)-tw,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][10].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][10].toStdString().c_str(),10,(start_table+=std_cell)-tw,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][11].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][11].toStdString().c_str(),10,(start_table+=std_cell)-tw,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][12].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][12].toStdString().c_str(),10,(start_table+=std_cell)-tw,y);
HPDF_Page_EndText(pages[page]);

            y-=20;

        }
        vect_value_size -= 30;
    }
    else
    {
        for (int i = 0; i < vect_value_size; ++i)
        {
            double tw;
            start_table = 118;

HPDF_Page_BeginText(pages[page]);
            print_text(page,rus_std,QString::number(numer_of_line++).toStdString().c_str(),10,51+pos,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][4].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][4].toStdString().c_str(),10,(start_table+=long_cell)-tw,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][5].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][5].toStdString().c_str(),10,(start_table+=long_cell)-tw,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][6].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][6].toStdString().c_str(),10,(start_table+=long_cell)-tw,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][7].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][7].toStdString().c_str(),10,(start_table+=std_cell)-tw,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][8].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][8].toStdString().c_str(),10,(start_table+=std_cell)-tw,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][9].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][9].toStdString().c_str(),10,(start_table+=std_cell)-tw,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][10].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][10].toStdString().c_str(),10,(start_table+=std_cell)-tw,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][11].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][11].toStdString().c_str(),10,(start_table+=std_cell)-tw,y);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
            tw = HPDF_Page_TextWidth(pages[page],vect_value[i][12].toStdString().c_str());
            print_text(page,rus_std,vect_value[i][12].toStdString().c_str(),10,(start_table+=std_cell)-tw,y);
HPDF_Page_EndText(pages[page]);

            y-=20;
        }
        vect_value_size = 0;

    }

        if(vect_value_size == 0)
        {
            numer_of_line = 0;
            both_of_graph(pos,height,start_table,std_cell,long_cell,105,PAGE_WIDTH,page,vect_value);

        }

 }


 void PDF_creator::both_of_graph(int pos,double height,int start_table,int std_cell,int long_cell,int PAGE_HEIGHT,int PAGE_WIDTH , int page,QVector<QVector<QString>> & vect_value)
 {
    start_table = 40;
    PAGE_HEIGHT+=20;
    double tw;
    Q_UNUSED(height);


    HPDF_Page_MoveTo (pages[page], start_table+pos, PAGE_HEIGHT);
    HPDF_Page_LineTo (pages[page], start_table+pos, PAGE_HEIGHT-20);



    HPDF_Page_MoveTo (pages[page], (start_table+=long_cell*3+std_cell)+pos, PAGE_HEIGHT);
    HPDF_Page_LineTo (pages[page], start_table+pos,PAGE_HEIGHT-20 );

    HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT);
    HPDF_Page_LineTo (pages[page], start_table+pos,PAGE_HEIGHT-20 );

    HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT);
    HPDF_Page_LineTo (pages[page], start_table+pos,PAGE_HEIGHT-20 );

    HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT);
    HPDF_Page_LineTo (pages[page], start_table+pos,PAGE_HEIGHT-20 );

    HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT);
    HPDF_Page_LineTo (pages[page], start_table+pos,PAGE_HEIGHT-20 );

    HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT);
    HPDF_Page_LineTo (pages[page], start_table+pos,PAGE_HEIGHT-20 );

    HPDF_Page_MoveTo (pages[page], (start_table+=std_cell)+pos, PAGE_HEIGHT);
    HPDF_Page_LineTo (pages[page], start_table+pos,PAGE_HEIGHT-20 );

    HPDF_Page_MoveTo (pages[page], 40+pos, PAGE_HEIGHT-20);
    HPDF_Page_LineTo (pages[page], PAGE_WIDTH-85, PAGE_HEIGHT-20);

    HPDF_Page_Stroke (pages[page]);



    start_table = 329;



    double sum_del_x = 0 ;
    double sum_del_y = 0;
    double sum_del_z = 0;
    double sum_om_x = 0;
    double sum_om_y = 0;
    double sum_om_z = 0;


    for (int i = 0; i < vect_value.size(); ++i)
    {

      sum_del_x += std::abs(vect_value[i][7].toDouble());
      sum_del_y += std::abs(vect_value[i][8].toDouble());
      sum_del_z += std::abs(vect_value[i][9].toDouble());
      sum_om_x += std::pow(vect_value[i][10].toDouble(),2);
      sum_om_y += std::pow(vect_value[i][11].toDouble(),2);
      sum_om_z += std::pow(vect_value[i][12].toDouble(),2);

    }

    double av_del_x = sum_del_x / vect_value.size();
    double av_del_y = sum_del_y / vect_value.size();
    double av_del_z = sum_del_z / vect_value.size();
    double av_om_x = std::sqrt(sum_om_x/ vect_value.size());
    double av_om_y = std::sqrt(sum_om_y/ vect_value.size());
    double av_om_z = std::sqrt(sum_om_z/ vect_value.size());

    QString result = "среднии значения                       " + QString::number(av_del_x,'f',1) + "    " + QString::number(av_del_y,'f',1) + "   " +
            QString::number(av_del_z,'f',1) + "  " + QString::number(av_om_x,'f',1) + "    " + QString::number(av_om_y,'f',1) + "      " +
            QString::number(av_om_z,'f',1);



    HPDF_Page_BeginText(pages[page]);

                print_text(page,rus_std,QString("среднии значения").toStdString().c_str(),10,start_table-long_cell*3-std_cell+5,PAGE_HEIGHT-16);
    HPDF_Page_EndText(pages[page]);
    HPDF_Page_BeginText(pages[page]);
                tw = HPDF_Page_TextWidth(pages[page],QString::number(av_del_x,'f',1).toStdString().c_str());
                print_text(page,rus_std,QString::number(av_del_x,'f',1).toStdString().c_str(),10,(start_table+=std_cell)-tw,PAGE_HEIGHT-16);
    HPDF_Page_EndText(pages[page]);
    HPDF_Page_BeginText(pages[page]);
                tw = HPDF_Page_TextWidth(pages[page],QString::number(av_del_y,'f',1).toStdString().c_str());
                print_text(page,rus_std,QString::number(av_del_y,'f',1).toStdString().c_str(),10,(start_table+=std_cell)-tw,PAGE_HEIGHT-16);
    HPDF_Page_EndText(pages[page]);
    HPDF_Page_BeginText(pages[page]);
                tw = HPDF_Page_TextWidth(pages[page],QString::number(av_del_z,'f',1).toStdString().c_str());
                print_text(page,rus_std,QString::number(av_del_z,'f',1).toStdString().c_str(),10,(start_table+=std_cell)-tw,PAGE_HEIGHT-16);
    HPDF_Page_EndText(pages[page]);
    HPDF_Page_BeginText(pages[page]);
                tw = HPDF_Page_TextWidth(pages[page],QString::number(av_om_x,'f',1).toStdString().c_str());
                print_text(page,rus_std,QString::number(av_om_x,'f',1).toStdString().c_str(),10,(start_table+=std_cell)-tw,PAGE_HEIGHT-16);
    HPDF_Page_EndText(pages[page]);
    HPDF_Page_BeginText(pages[page]);
                tw = HPDF_Page_TextWidth(pages[page],QString::number(av_om_y,'f',1).toStdString().c_str());
                print_text(page,rus_std,QString::number(av_om_y,'f',1).toStdString().c_str(),10,(start_table+=std_cell)-tw,PAGE_HEIGHT-16);
    HPDF_Page_EndText(pages[page]);
    HPDF_Page_BeginText(pages[page]);
                tw = HPDF_Page_TextWidth(pages[page],QString::number(av_om_z,'f',1).toStdString().c_str());
                print_text(page,rus_std,QString::number(av_om_z,'f',1).toStdString().c_str(),10,(start_table+=std_cell)-tw,PAGE_HEIGHT-16);
    HPDF_Page_EndText(pages[page]);

 }

  void PDF_creator::draw_graph_2(int page,QVector<int> & vect_value,int frames, const QString & sfx)
  {
      emit log_message("Формирование МЗД таблици");

     double tw;
     font = HPDF_GetFont (pdf, rus_std, "UTF-8");
     HPDF_Page_SetFontAndSize(pages[page], font, 10);
     int x_pos = 422;

     if(sfx != "o")
     {
     image = HPDF_LoadPngImageFromFile(pdf,"table2.png");
     HPDF_Page_DrawImage (pages[page], image, 175, HPDF_Page_GetHeight(pages[page_count-1]) /2+20, 250,150);

HPDF_Page_BeginText(pages[page]);
     tw = HPDF_Page_TextWidth(pages[page],QString::number(vect_value[0]).toStdString().c_str());
     print_text(page,rus_std,QString::number(vect_value[0]).toStdString().c_str(),10,x_pos-tw,559);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
     tw = HPDF_Page_TextWidth(pages[page],QString::number(vect_value[1]).toStdString().c_str());
     print_text(page,rus_std,QString::number(vect_value[1]).toStdString().c_str(),10,x_pos-tw,560-16);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
     tw = HPDF_Page_TextWidth(pages[page],QString::number(vect_value[2]).toStdString().c_str());
     print_text(page,rus_std,QString::number(vect_value[2]).toStdString().c_str(),10,x_pos-tw,560-32);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
     tw = HPDF_Page_TextWidth(pages[page],QString::number(vect_value[4]).toStdString().c_str());
     print_text(page,rus_std,QString::number(vect_value[4]).toStdString().c_str(),10,x_pos-tw,559-48);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
     tw = HPDF_Page_TextWidth(pages[page],QString::number(vect_value[5]).toStdString().c_str());
     print_text(page,rus_std,QString::number(vect_value[5]).toStdString().c_str(),10,x_pos-tw,560-65);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
     tw = HPDF_Page_TextWidth(pages[page],QString::number(vect_value[6]).toStdString().c_str());
     print_text(page,rus_std,QString::number(vect_value[6]).toStdString().c_str(),10,x_pos-tw,560-81);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
     QString text = QString::number(((vect_value[5] - 2 * frames)/2));
     tw = HPDF_Page_TextWidth(pages[page],text.toStdString().c_str());
     print_text(page,rus_std,text.toStdString().c_str(),10,x_pos-tw,560-98);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
     tw = HPDF_Page_TextWidth(pages[page],QString::number(vect_value[8]).toStdString().c_str());
     print_text(page,rus_std,QString::number(vect_value[8]).toStdString().c_str(),10,x_pos-tw,560-115);
HPDF_Page_EndText(pages[page]);
      }
      else
      {
          image = HPDF_LoadPngImageFromFile(pdf,"table2.png");
          HPDF_Page_DrawImage (pages[page], image, 175, HPDF_Page_GetHeight(pages[page_count-1]) /2+100, 250,150);

HPDF_Page_BeginText(pages[page]);
     tw = HPDF_Page_TextWidth(pages[page],QString::number(vect_value[0]).toStdString().c_str());
     print_text(page,rus_std,QString::number(vect_value[0]).toStdString().c_str(),10,x_pos-tw,580+60);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
     tw = HPDF_Page_TextWidth(pages[page],QString::number(vect_value[1]).toStdString().c_str());
     print_text(page,rus_std,QString::number(vect_value[1]).toStdString().c_str(),10,x_pos-tw,580-16+60);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
     tw = HPDF_Page_TextWidth(pages[page],QString::number(vect_value[2]).toStdString().c_str());
     print_text(page,rus_std,QString::number(vect_value[2]).toStdString().c_str(),10,x_pos-tw,580-32+60);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
     tw = HPDF_Page_TextWidth(pages[page],QString::number(vect_value[4]).toStdString().c_str());
     print_text(page,rus_std,QString::number(vect_value[4]).toStdString().c_str(),10,x_pos-tw,579-48+60);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
     tw = HPDF_Page_TextWidth(pages[page],QString::number(vect_value[5]).toStdString().c_str());
     print_text(page,rus_std,QString::number(vect_value[5]).toStdString().c_str(),10,x_pos-tw,580-65+60);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
     tw = HPDF_Page_TextWidth(pages[page],QString::number(vect_value[6]).toStdString().c_str());
     print_text(page,rus_std,QString::number(vect_value[6]).toStdString().c_str(),10,x_pos-tw,580-81+60);
HPDF_Page_EndText(pages[page]);
     if(sfx != "o")
     {
HPDF_Page_BeginText(pages[page]);
     QString text = QString::number(((vect_value[5] - 2 * frames)/2));
     tw = HPDF_Page_TextWidth(pages[page],text.toStdString().c_str());
     print_text(page,rus_std,text.toStdString().c_str(),10,x_pos-tw,580-98+60);
HPDF_Page_EndText(pages[page]);
      }
     else
     {
HPDF_Page_BeginText(pages[page]);
     QString text = QString::number(((vect_value[5] - 2 * 1)/2));
     tw = HPDF_Page_TextWidth(pages[page],text.toStdString().c_str());
     print_text(page,rus_std,text.toStdString().c_str(),10,x_pos-tw,580-98+60);
HPDF_Page_EndText(pages[page]);
     }
HPDF_Page_BeginText(pages[page]);
     tw = HPDF_Page_TextWidth(pages[page],QString::number(vect_value[8]).toStdString().c_str());
     print_text(page,rus_std,QString::number(vect_value[8]).toStdString().c_str(),10,x_pos-tw,580-115+60);
HPDF_Page_EndText(pages[page]);
      }


     QString text;


if(sfx == "r1")
{
HPDF_Page_BeginText(pages[page]);
     text = "Таблица "+QString::number(ris_t++)+" Статистические результаты функциональных испытаний МЗД ";
     print_text(page,rus_std,text.toStdString().c_str(),10,100, HPDF_Page_GetHeight(pages[page_count-1]) /2+200);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
     print_text(page,rus_std,"              АЗДК-1 при скоростях вращения 1°/сек.",10,100, HPDF_Page_GetHeight(pages[page_count-1]) /2+180);
HPDF_Page_EndText(pages[page]);
}
if(sfx == "o")
{
HPDF_Page_BeginText(pages[page]);
     text = "Таблица "+QString::number(ris_t++)+" Статистические результаты испытаний МЗД АЗДК-1.";
     print_text(page,rus_std,text.toStdString().c_str(),10,100, HPDF_Page_GetHeight(pages[page_count-1]) /2+270);
HPDF_Page_EndText(pages[page]);
}
if(sfx == "r3")
{
HPDF_Page_BeginText(pages[page]);
     text = "Таблица "+QString::number(ris_t++)+" Статистические результаты функциональных испытаний МЗД ";
     print_text(page,rus_std,text.toStdString().c_str(),10,100, HPDF_Page_GetHeight(pages[page_count-1]) /2+203);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
     print_text(page,rus_std,"              АЗДК-1 при скоростях вращения 3°/сек.",10,100, HPDF_Page_GetHeight(pages[page_count-1]) /2+183);
HPDF_Page_EndText(pages[page]);
}
if(sfx == "r2")
{
HPDF_Page_BeginText(pages[page]);
     text = "Таблица "+QString::number(ris_t++)+" Статистические результаты функциональных испытаний МЗД ";
     print_text(page,rus_std,text.toStdString().c_str(),10,100, HPDF_Page_GetHeight(pages[page_count-1]) /2+203);
HPDF_Page_EndText(pages[page]);
HPDF_Page_BeginText(pages[page]);
     print_text(page,rus_std,"              АЗДК-1 при скоростях вращения 2°/сек.",10,100, HPDF_Page_GetHeight(pages[page_count-1]) /2+183);
HPDF_Page_EndText(pages[page]);
}

emit log_message("Таблица успешно сформированна");


  }



  

 void PDF_creator::create_pdf()
 {
     pdf = HPDF_New(error_handler, NULL);

     if (!pdf)
     {
         throw std::runtime_error("cannot create PdfDoc object");
     }
 }

 void PDF_creator::set_font_name(const QString& font_name)
 {
     this->font_name = font_name;
 }

 void PDF_creator::create_page()
 {
      pages.push_back(HPDF_AddPage(pdf));
      page_count++;
 }

 void PDF_creator::free()
 {
     HPDF_Free(pdf);
     pages.clear();
 }

 void PDF_creator::save()
 {

     emit log_message("Сохранение pdf файла");

     QString path = save_path;


     if (path.indexOf(".pdf") == -1)
         path += ".pdf";
    
     if (QFile::exists(path))
     {
         QFile file(path);
         
         
         
         if (!file.open(QIODevice::WriteOnly))
         {
             emit log_message("Файл с выбранным названием в данный", qRgb(255, 170, 0));
             emit log_message("момент используется, закройте", qRgb(255, 170, 0));
             emit log_message("файл и повторите попытку", qRgb(255, 170, 0));
             return;
         }
         file.remove();
     }
     


    // while(true)
    // {
     //    if(QFile::exists (path))
     //    {
     //        path.insert(path.size()-4,"(" + QString::number(count++) +")");
     //    }
     //    else
     //        break;
    // }

     QByteArray ba = path.toLocal8Bit();
     const char *c_str = ba.data();
     HPDF_SaveToFile(pdf, c_str);

     emit log_message("Сохранение завершено");

 }

void PDF_creator::set_parser(Parser & parser)
{
    this->parser = &parser;
}

 void PDF_creator::set_save_path(const QString & path)
 {
    this->save_path = path;
 }

 void PDF_creator::set_file_name(const QString & name)
 {
    this->fname = name;
 }

 void PDF_creator::set_template_files(const QString & file1,const QString & file2,const QString & file3)
 {
     template_files.push_back(file1);
     template_files.push_back(file2);
     template_files.push_back(file3);
 }

 void PDF_creator::set_sfx_state(bool s1,bool s2,bool s3,bool s4,bool s5,bool s6)
 {
     sfx_state.push_back(s1);
     sfx_state.push_back(s2);
     sfx_state.push_back(s3);
     sfx_state.push_back(s4);
     sfx_state.push_back(s5);
     sfx_state.push_back(s6);
 }

  void PDF_creator::set_AZDK(const AZDK & azdk)
  {
      this->azdk = azdk;
  }


   void PDF_creator::print_text(int page,const char * font_setting,const char * text,int size_text,float x_pos = 0,float y_pos = 0)
   {

       font = HPDF_GetFont (pdf, font_setting, "UTF-8");
       HPDF_Page_SetFontAndSize(pages[page], font, size_text);



       if(x_pos != 0 && y_pos != 0)
       HPDF_Page_MoveTextPos(pages[page], x_pos, y_pos);
       HPDF_Page_ShowText(pages[page], text);

   }



 void PDF_creator::start()
 {

     emit log_message("Начало работы",qRgb(90,200,90));
     if(thread_gate)
     {
         parser->to_parse();

         emit progress(0);

         create_pdf();
         create_page();

         HPDF_SetCompressionMode (pdf, HPDF_COMP_ALL);

       

        


         if (!font_setting())
         {
             end_work();
             return;
         }

         //rus_bold = HPDF_LoadTTFontFromFile(pdf, "C:\Work\Azdk_PDFCreator\AZDK_PDFcreator\Release\fonts\arialbd.ttf", HPDF_TRUE);
         //rus_std = HPDF_LoadTTFontFromFile(pdf, "C:\Work\Azdk_PDFCreator\AZDK_PDFcreator\Release\fonts\arial.ttf", HPDF_TRUE);//
                                   



         titul_list();


        try{


         try {

             if(sfx_state[0]) // s
             {
                 s_otchet();
                 emit progress(20);

             }

         }
         catch (std::runtime_error& ex)
         {
             QApplication::beep();
             emit error(QString(ex.what()));
         }

         try{

             if(sfx_state[1]) // r01
             {
                 r01_otchet();
                 emit progress(40);

             }

         }

         catch (std::runtime_error& ex)
         {
             QApplication::beep();
             emit error(QString(ex.what()));
         }


         try{

             if(sfx_state[2]) // r1
             {
                 r1_otchet();
                 emit progress(60);

             }

         }

         catch (std::runtime_error& ex)
         {
             QApplication::beep();
             emit error(QString(ex.what()));
         }

         try {



         if(sfx_state[3]) // r2
         {
             r2_otchet();
             emit progress(70);

         }

         }

         catch (std::runtime_error& ex)
         {
             QApplication::beep();
             emit error(QString(ex.what()));
         }

         try{

         if(sfx_state[4]) // r3
         {
             r3_otchet();
             emit progress(80);

         }

         }

         catch (std::runtime_error& ex)
         {
             QApplication::beep();
             emit error(QString(ex.what()));
         }

         try {



         if(sfx_state[5]) // o
         {
             o_otchet();
             emit progress(95);
         }

         }

         catch (std::runtime_error& ex)
         {
             QApplication::beep();
             emit error(QString(ex.what()));
         }


         }

         catch (...)
         {
             QApplication::beep();
             emit error(QString("crash algorithm"));
         }




         end_work();

     }



 }

 bool PDF_creator::font_setting()
 {

     HPDF_UseUTFEncodings(pdf); // ЕНКОДИНГ НА РУССКИЙ ТЕКСТ
     HPDF_SetCurrentEncoder(pdf, "UTF-8");
     QString bold;
     QString std;

    bold = QStandardPaths::displayName(QStandardPaths::FontsLocation) + "/" + font_name + "bd.ttf";
    std = QStandardPaths::displayName(QStandardPaths::FontsLocation) + "/" + font_name + ".ttf";

     if (parser->is_exists(bold) && parser->is_exists(std))
     {
         rus_bold = HPDF_LoadTTFontFromFile(pdf, bold.toStdString().c_str(), HPDF_TRUE);
         rus_std = HPDF_LoadTTFontFromFile(pdf, std.toStdString().c_str(), HPDF_TRUE);
         emit log_message("Шрифт установлен");
         return true;
     }
     
     bold = QString("C:/Windows/Fonts") + QString("/") + font_name + QString("bd.ttf");
     std  = QString("C:/Windows/Fonts") + QString("/") + font_name + QString(".ttf");

     if (parser->is_exists(bold) && parser->is_exists(std))
     {
         rus_bold = HPDF_LoadTTFontFromFile(pdf, bold.toStdString().c_str(), HPDF_TRUE);
         rus_std = HPDF_LoadTTFontFromFile(pdf, std.toStdString().c_str(), HPDF_TRUE);
         emit log_message("Шрифт установлен");
         return true;
     }
     else
     {
         emit log_message("Указанный шрифт не был найден, работа программы остановленна!",qRgb(250,0,0));
         return false;
     }
     
 }

 void PDF_creator::end_work()
 {
     vect_value_size = 0;
     page_count = 0;
     numer_of_line = 1;
     ris_g = 1;
     ris_n = 1;
     ris_t = 1;
     test = 1;

     save();
     free();
     sfx_state.clear();
     template_files.clear();
     emit progress(100);
     QApplication::beep();
     thread_gate = false;
     emit unblock_ui();
     emit log_message("Конец работы",qRgb(90,200,90));
     emit finished();
 }




 void PDF_creator::titul_list()
 {





     float tw;
     std::string text;


     font = HPDF_GetFont (pdf, rus_bold, "UTF-8");
     if(azdk.ver.isEmpty())
        text= "Отчет о функциональных испытаниях МЗД АЗДК-1.5 №";//Заголовок////////
     else
        text= "Отчет о функциональных испытаниях МЗД "+azdk.ver.toStdString() +" №";

     text+=azdk.number.toStdString();
     HPDF_Page_SetFontAndSize(pages[0], font, 16);
     tw = HPDF_Page_TextWidth(pages[0], text.c_str());
HPDF_Page_BeginText(pages[0]);
     HPDF_Page_MoveTextPos(pages[0], (HPDF_Page_GetWidth(pages[0]) - tw) / 2,
             HPDF_Page_GetHeight(pages[0]) - 50);
     HPDF_Page_ShowText(pages[0], text.c_str());
HPDF_Page_EndText(pages[0]);


     font = HPDF_GetFont (pdf, rus_std, "UTF-8");
     HPDF_Page_SetFontAndSize(pages[0], font, 14);
     tw = HPDF_Page_TextWidth(pages[0], "ООО «Азмерит»");
HPDF_Page_BeginText(pages[0]);
     HPDF_Page_MoveTextPos(pages[0], (HPDF_Page_GetWidth(pages[0]) - tw) / 2,
             HPDF_Page_GetHeight(pages[0]) - 70);
     HPDF_Page_ShowText(pages[0], "ООО «Азмерит»");
HPDF_Page_EndText(pages[0]);/////////////////////////////////////////////////


HPDF_Page_BeginText(pages[0]);
     print_text(0,rus_bold,"Объект испытаний: ",12,50,HPDF_Page_GetHeight(pages[0]) - 150-28*0);

     if(azdk.ver.isEmpty())
         print_text(0,rus_std,"малогабаритный звездный датчик АЗДК-1.5 (АЗДК-1).",12);
     else
     {
         text = QString("малогабаритный звездный датчик " + azdk.ver + " (АЗДК-1).").toStdString();
         print_text(0,rus_std,text.c_str(),12);
     }
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     print_text(0,rus_bold,"Метка изделия МЗД АЗДК-1: ",12,50,HPDF_Page_GetHeight(pages[0]) - 150-28*1);
     if(azdk.ver.isEmpty())
        text = "АЗДК-1.5 №"+azdk.number.toStdString()+'.';
     else
         text = azdk.ver.toStdString() + " №" + azdk.number.toStdString()+'.';

     print_text(0,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     print_text(0,rus_bold,"Цель испытаний: ",12,50,HPDF_Page_GetHeight(pages[0]) - 150-28*2);
     print_text(0,rus_std,"выполнить проверку функциональности МЗД АЗДК-1 с ",12);
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     text = "версией прошивки "+azdk.firmware.toStdString() + " с частотой работы процессора 80 МГц.";
     print_text(0,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - 150-28*3);
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     print_text(0,rus_bold,"Место испытаний: ",12,50,HPDF_Page_GetHeight(pages[0]) - 150-28*4);
     print_text(0,rus_std,"Москва, Красная Пресня.",12);
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     print_text(0,rus_bold,"Время испытаний: ",12,50,HPDF_Page_GetHeight(pages[0]) - 150-28*5);
     text = azdk.time.toStdString();
     print_text(0,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     print_text(0,rus_std,"    Функциональные испытания МЗД АЗДК 1 проводились с использованием ",12,50,HPDF_Page_GetHeight(pages[0]) - 150-28*6);
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     text = "имитатора звездного неба ОДС 1 №" + azdk.number_Ods.toStdString() + ", проецировавшего на матрицу МЗД ";
     print_text(0,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - 150-28*7);
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     print_text(0,rus_std,"АЗДК 1 динамичные и статичные кадры звездного неба.",12,50,HPDF_Page_GetHeight(pages[0]) - 150-28*8);
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     print_text(0,rus_bold,"Условия:",12,50,HPDF_Page_GetHeight(pages[0]) - 150-28*9);
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     print_text(0,rus_bold,"—  ",12,60,HPDF_Page_GetHeight(pages[0]) - 150-28*10);
     text = "настройки ПО ОДС: интенсивность " + azdk.intensity.toStdString() + "; влияние величины "
             +azdk.influence.toStdString() + "; фокус ";
     print_text(0,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     text = azdk.focus.toStdString() + " мм; размер изображения звезды "+azdk.size.toStdString() + " пикс;";
     print_text(0,rus_std,text.c_str(),12,70,HPDF_Page_GetHeight(pages[0]) - 150-28*11);
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     print_text(0,rus_bold,"—  ",12,60,HPDF_Page_GetHeight(pages[0]) - 150-28*12);
     print_text(0,rus_std,"ОДС: каталог звезд до 7.5 звездной величины;",12);
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     print_text(0,rus_bold,"—  ",12,60,HPDF_Page_GetHeight(pages[0]) - 150-28*13);
     text = "версия прошивки АЗДК-1: " + azdk.firmware.toStdString()+";";
     print_text(0,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     print_text(0,rus_bold,"—  ",12,60,HPDF_Page_GetHeight(pages[0]) - 150-28*14);
     text = "взаимодействие по интерфейсу " + azdk.interface_.toStdString() + " на скорости " + azdk.speed.toStdString()+";";
     print_text(0,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     print_text(0,rus_bold,"—  ",12,60,HPDF_Page_GetHeight(pages[0]) - 150-28*15);
     text = "длительность накопления сигнала в МЗД: " + azdk.duration.toStdString()+" мс"+";";
     print_text(0,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     print_text(0,rus_bold,"—  ",12,60,HPDF_Page_GetHeight(pages[0]) - 150-28*16);
     text = "режим бинирования кадров в АЗДК-1 " + azdk.binar.toStdString()+";";
     print_text(0,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[0]);

HPDF_Page_BeginText(pages[0]);
     print_text(0,rus_bold,"—  ",12,60,HPDF_Page_GetHeight(pages[0]) - 150-28*17);
     print_text(0,rus_std,azdk.timer.toStdString().c_str(),12);
     print_text(0,rus_std,";",12);
HPDF_Page_EndText(pages[0]);


 }

 void PDF_creator::s_otchet()
 {
     auto sko_otchet = parser->parse_resulte_table("/azdk" + azdk.number +"s" + "/errors.csv" );
     //auto ct = parser->Frames_count_and_time("/"+template_files[2]+azdk.number,"s");
     auto ct = parser->Frames_count_and_time_ver2("/"+template_files[2]+azdk.number,"/"+template_files[1]+azdk.number,"s",azdk.number);
     std::string text = "Тест-"+ std::to_string(test) + " (точностной)";

    emit log_message("создание s отчета");

     create_page();
     calantitul(page_count-1);
     int x=0;

     float tw = HPDF_Page_TextWidth(pages[page_count-1], text.c_str());

HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,text.c_str(),16,(HPDF_Page_GetWidth(pages[page_count-1]) - tw-50) / 2,
     HPDF_Page_GetHeight(pages[page_count-1]) - 50);
HPDF_Page_EndText(pages[page_count-1]);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "          Задачей теста-"+std::to_string(test++)+" являлось измерение точностных характеристик МЗД АЗДК-1.";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"В ходе теста посредством имитатора звездного неба ОДС-1 было подано ",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     text = ct[0].toStdString();
     print_text(page_count-1,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"случайных статичных кадра звездного неба длительностью по ",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     text = minute_validator(ct[1].toInt(),ct[2].toInt()) + " каждый";
     print_text(page_count-1,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          В результате теста выполнены следующие измерения:",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Компонент кватерниона w, измеренного в МЗД (красные точки) и" ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "компонент кватерниона, установленного в ОДС (синяя линия) – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Компонент кватерниона x, измеренного в МЗД (красные точки) и " ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "компонент кватерниона, установленного в ОДС (синяя линия) – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Компонент кватерниона y, измеренного в МЗД (красные точки) и " ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "компонент кватерниона, установленного в ОДС (синяя линия) – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Компонент кватерниона z, измеренного в МЗД (красные точки) и  " ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "компонент кватерниона, установленного в ОДС (синяя линия) – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Отклонения углов ориентации между измерениями и установкой в ОДС по " ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "временной шкале показаны на Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Результаты измерений ошибок ориентации Δx, Δy, Δz, представленные в",12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "системе координат прибора, показаны на Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Отклонения углов ориентации от средних значений по временной шкале  " ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "показаны на Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Результаты измерений ошибок ориентации Δx, Δy, Δz, представленные в   " ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
      text = "системе координат прибора, показаны на Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," В таблице 1 приведены средние значения отклонений кватернионов для " ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"всех серий измерений.",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);


     create_page();
     calantitul(page_count-1);
     x=0;

     QString p;

     p = parser->Png_path_veryf("/azdk" + azdk.number + "s/quats-azdk"+ azdk.number +"s.w.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 340, 2339/4.6,1235/4.6);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона w, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 360);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия). ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 375);
HPDF_Page_EndText(pages[page_count-1]);

     p = parser->Png_path_veryf("/azdk" + azdk.number + "s/quats-azdk"+ azdk.number +"s.x.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 740+70, 2339/4.6,1235/4.6);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона x, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 760+70);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия).",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 775+70);
HPDF_Page_EndText(pages[page_count-1]);

     create_page();
     calantitul(page_count-1);
     x=0;

     p = parser->Png_path_veryf("/azdk" + azdk.number + "s/quats-azdk"+ azdk.number +"s.y.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 340, 2339/4.6,1235/4.6);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона y, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 360);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия). ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 375);
HPDF_Page_EndText(pages[page_count-1]);

     p = parser->Png_path_veryf("/azdk" + azdk.number + "s/quats-azdk"+ azdk.number +"s.z.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 740+70, 2339/4.6,1235/4.6);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона z, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 760+70);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия).",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 775+70);
HPDF_Page_EndText(pages[page_count-1]);

     create_page();
     calantitul(page_count-1);
     x=0;

     p = parser->Png_path_veryf("/azdk" + azdk.number + "s/xyz-azdk"+ azdk.number +"s-angles.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 340+100, 4703/9.2,1857/9.2);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Разница углов ориентации между измерениями в МЗД и установкой в ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 360+100);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          ОДС в приборной системе координат. ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 375+100);
HPDF_Page_EndText(pages[page_count-1]);

     p = parser->Png_path_veryf("/azdk" + azdk.number + "s/xyz-azdk"+ azdk.number +"s.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 125-60, HPDF_Page_GetHeight(pages[page_count-1]) - 740, 536/1.1,489/1.1);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Гистограммы измерений ошибок ориентации Δx, Δy, Δz, ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 760);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          представленные в системе координат прибора.",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 775);
HPDF_Page_EndText(pages[page_count-1]);

     create_page();
     calantitul(page_count-1);
     x=0;

     p = parser->Png_path_veryf("/azdk" + azdk.number + "s/xyz-azdk"+ azdk.number +"s-mm-angles.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 340+100, 4703/9.2,1857/9.2);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Разница углов ориентации между измерениями в МЗД вычисленными ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 360+100);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          средними значениями в приборной системе координат.",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 375+100);
HPDF_Page_EndText(pages[page_count-1]);

     p = parser->Png_path_veryf("/azdk" + azdk.number + "s/xyz-azdk"+ azdk.number +"s-mm.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 125-60, HPDF_Page_GetHeight(pages[page_count-1]) - 740, 536/1.1,489/1.1);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Гистограммы измерений ошибок ориентации Δx, Δy, Δz, ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 760);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          представленные в системе координат прибора.",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 775);
HPDF_Page_EndText(pages[page_count-1]);


     emit log_message("Формирование СКО таблици");
     int y;
     if(sko_otchet.size()<=30)
         y = 1;//sko_otchet.size()/30;
     else
         y = sko_otchet.size()/30+1;

     for (int i = 0; i < y ; ++i) {

         create_page();
         calantitul(page_count-1);

         HPDF_Page_SetFontAndSize(pages[page_count-1], font, 16);
         draw_graph(page_count-1,sko_otchet);
     }

     emit log_message("Таблица сформированна");
     emit log_message("s отчет создан");

 }

 void PDF_creator::r01_otchet()
 {
     //auto ct = parser->Frames_count_and_time("/"+template_files[2]+azdk.number,"r01");
     auto ct = parser->Frames_count_and_time_ver2("/"+template_files[2]+azdk.number,"/"+template_files[1]+azdk.number,"r01",azdk.number);
     std::string text = "Тест-"+ std::to_string(test) + " (точностной)";

     emit log_message("Создание r01 отчета");

     create_page();
     calantitul(page_count-1);
     int x=0;

     float tw = HPDF_Page_TextWidth(pages[page_count-1], text.c_str());

HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,text.c_str(),16,(HPDF_Page_GetWidth(pages[page_count-1]) - tw-50) / 2,
     HPDF_Page_GetHeight(pages[page_count-1]) - 50);
HPDF_Page_EndText(pages[page_count-1]);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "          Задачей теста-"+std::to_string(test++)+" являлось измерение точностных характеристик МЗД АЗДК-1.";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"В ходе теста посредством имитатора звездного неба ОДС-1 было подано ",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     text = ct[0].toStdString();
     print_text(page_count-1,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"случайных ориентаций кадра звездного неба длительностью по ",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     text = minute_validator(ct[1].toInt(),ct[2].toInt()) + " каждый";
     print_text(page_count-1,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"с включенной случайной скоростью вращения 0.1 °/с.",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          В результате теста выполнены следующие измерения:",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Компонент кватерниона w, измеренного в МЗД (красные точки) и" ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "компонент кватерниона, установленного в ОДС (синяя линия) – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Компонент кватерниона x, измеренного в МЗД (красные точки) и" ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "компонент кватерниона, установленного в ОДС (синяя линия) – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Компонент кватерниона y, измеренного в МЗД (красные точки) и" ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "компонент кватерниона, установленного в ОДС (синяя линия) – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Компонент кватерниона z, измеренного в МЗД (красные точки) и" ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "компонент кватерниона, установленного в ОДС (синяя линия) – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Отклонения углов ориентации между измерениями и установкой в ОДС по" ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "временной шкале показаны на Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Результаты измерений ошибок ориентации Δx, Δy, Δz, представленные в" ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "системе координат прибора, показаны на Рис. " + std::to_string(ris_n++)+".";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);

     create_page();
     calantitul(page_count-1);
     x=0;

     QString p;

     p = parser->Png_path_veryf("/azdk" + azdk.number + "r01/quats-azdk"+ azdk.number +"r01.w.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 340, 2339/4.6,1235/4.6);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона w, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 360);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия). ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 375);
HPDF_Page_EndText(pages[page_count-1]);

     p = parser->Png_path_veryf("/azdk" + azdk.number + "r01/quats-azdk"+ azdk.number +"r01.x.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 740, 2339/4.6,1235/4.6);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона x, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 760);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия).",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 775);
HPDF_Page_EndText(pages[page_count-1]);

     create_page();
     calantitul(page_count-1);
     x=0;

     p = parser->Png_path_veryf("/azdk" + azdk.number + "r01/quats-azdk"+ azdk.number +"r01.y.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 340, 2339/4.6,1235/4.6);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона y, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 360);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия). ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 375);
HPDF_Page_EndText(pages[page_count-1]);

     p = parser->Png_path_veryf("/azdk" + azdk.number + "r01/quats-azdk"+ azdk.number +"r01.z.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 740, 2339/4.6,1235/4.6);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона z, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 760);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия).",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 775);
HPDF_Page_EndText(pages[page_count-1]);

     create_page();
     calantitul(page_count-1);
     x=0;

     p = parser->Png_path_veryf("/azdk" + azdk.number + "r01/xyz-azdk"+ azdk.number +"r01-angles.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 340+100, 4703/9.2,1857/9.2);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Разница углов ориентации между измерениями в МЗД и установкой в  ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 360+100);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          ОДС в приборной системе координат. ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 375+100);
HPDF_Page_EndText(pages[page_count-1]);

     p = parser->Png_path_veryf("/azdk" + azdk.number + "r01/xyz-azdk"+ azdk.number +"r01.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 125-60, HPDF_Page_GetHeight(pages[page_count-1]) - 740, 536/1.1,489/1.1);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Гистограммы измерений ошибок ориентации Δx, Δy, Δz,  ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 760);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          представленные в системе координат прибора.",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 775);
HPDF_Page_EndText(pages[page_count-1]);

     emit log_message("ro1 отчет создан");

 }

 void PDF_creator::r1_otchet()
 {
     //auto ct = parser->Frames_count_and_time("/"+template_files[2]+azdk.number,"r1");
     auto ct = parser->Frames_count_and_time_ver2("/"+template_files[2]+azdk.number,"/"+template_files[1]+azdk.number,"r1",azdk.number);
     auto val_vect = parser->parse_resulte_table_2_ver2("/"+template_files[0]+azdk.number + "r1.txt","/"+template_files[2]+azdk.number + "r1.txt");
     std::string text = "Тест-"+ std::to_string(test) + " (статистический)";

     emit log_message("Создание r1 отчета");

     create_page();
     calantitul(page_count-1);
     int x=0;

     float tw = HPDF_Page_TextWidth(pages[page_count-1], text.c_str());

HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,text.c_str(),16,(HPDF_Page_GetWidth(pages[page_count-1]) - tw-50) / 2,
     HPDF_Page_GetHeight(pages[page_count-1]) - 50);
HPDF_Page_EndText(pages[page_count-1]);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "          Задачей теста-"+std::to_string(test++)+" являлся набор статистики количества отождествленных";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"кадров и количество срывов ведений МЗД АЗДК-1 на случайных участках неба",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"при скорости вращения КА 1°/сек. Данные получены на основе ",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     text = ct[0].toStdString() + " случайных";
     print_text(page_count-1,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"треков длительностью по ",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     text = minute_validator(ct[1].toInt(),ct[2].toInt()) +"." ;
     print_text(page_count-1,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[page_count-1]);

     draw_graph_2(page_count-1,val_vect,ct[0].toInt(),"r1");

     x+=8;

HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          В результате теста выполнены следующие измерения:",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Компонент кватерниона w, измеренного в МЗД (красные точки) и" ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "компонент кватерниона, установленного в ОДС (синяя линия) – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Компонент кватерниона x, измеренного в МЗД (красные точки) и" ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "компонент кватерниона, установленного в ОДС (синяя линия) – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Компонент кватерниона y, измеренного в МЗД (красные точки) и" ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "компонент кватерниона, установленного в ОДС (синяя линия) – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Компонент кватерниона z, измеренного в МЗД (красные точки) и" ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "компонент кватерниона, установленного в ОДС (синяя линия) – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Отклонения углов ориентации между измерениями в МЗД и установкой в " ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "ОДС в приборной системе координат показаны см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     text = " Частота выдачи МЗД АЗДК-1 кадров по статистическим данным – см. Рис. " + std::to_string(ris_n++)+".";
     print_text(page_count-1,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[page_count-1]);

     create_page();
     calantitul(page_count-1);
     x=0;

     QString p;

     p = parser->Png_path_veryf("/azdk" + azdk.number + "r1/quats-azdk"+ azdk.number +"r1.w.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 340, 2339/4.6,1235/4.6);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона w, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 360);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия). ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 375);
HPDF_Page_EndText(pages[page_count-1]);

     p = parser->Png_path_veryf("/azdk" + azdk.number + "r1/quats-azdk"+ azdk.number +"r1.x.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 740, 2339/4.6,1235/4.6);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона x, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 760);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия).",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 775);
HPDF_Page_EndText(pages[page_count-1]);

     create_page();
     calantitul(page_count-1);
     x=0;

     p = parser->Png_path_veryf("/azdk" + azdk.number + "r1/quats-azdk"+ azdk.number +"r1.y.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 340, 2339/4.6,1235/4.6);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона y, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 360);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия). ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 375);
HPDF_Page_EndText(pages[page_count-1]);

     p = parser->Png_path_veryf("/azdk" + azdk.number + "r1/quats-azdk"+ azdk.number +"r1.z.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 740, 2339/4.6,1235/4.6);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона z, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 760);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия).",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 775);
HPDF_Page_EndText(pages[page_count-1]);

     create_page();
     calantitul(page_count-1);
     x=0;

     p = parser->Png_path_veryf("/azdk" + azdk.number + "r1/xyz-azdk"+ azdk.number +"r1-angles.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 340, 4703/9.2,1857/9.2);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Отклонения углов ориентации между измерениями в МЗД и  ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 360);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          установкой в ОДС в приборной системе координат. ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 375);
HPDF_Page_EndText(pages[page_count-1]);

     p = parser->Png_path_veryf("/azdk" + azdk.number + "r1/stats-frequency-azdk"+ azdk.number +"r1.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 740, 4678/9.2,2423/9.2);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Частота выдачи МЗД АЗДК-1 кадров по статистическим данным.  ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 760);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          Красными точками обозначены «плохие» кадры, синими – ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 775);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          прочитанные кадры, зелеными – кадры с успешными  ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 790);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          отождествлениями  ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 805);
HPDF_Page_EndText(pages[page_count-1]);

    emit log_message("r1 отчет создан");

 }

 void PDF_creator::r2_otchet()
 {
     //auto ct = parser->Frames_count_and_time("/"+template_files[2]+azdk.number,"r2");
     auto ct = parser->Frames_count_and_time_ver2("/"+template_files[2]+azdk.number,"/"+template_files[1]+azdk.number,"r2",azdk.number);
     auto val_vect = parser->parse_resulte_table_2_ver2("/"+template_files[0]+azdk.number + "r2.txt","/"+template_files[2]+azdk.number + "r2.txt");
     std::string text = "Тест-"+ std::to_string(test) + " (статистический)";

     emit log_message("Создание r2 отчета");

     create_page();
     calantitul(page_count-1);
     int x=0;

     float tw = HPDF_Page_TextWidth(pages[page_count-1], text.c_str());

HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,text.c_str(),16,(HPDF_Page_GetWidth(pages[page_count-1]) - tw-50) / 2,
     HPDF_Page_GetHeight(pages[page_count-1]) - 50);
HPDF_Page_EndText(pages[page_count-1]);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "          Задачей теста-"+std::to_string(test++)+" являлся набор статистики количества отождествленных ";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"кадров и количество срывов ведений МЗД АЗДК-1 на случайных участках неба ",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"при скорости вращения КА 2°/сек. Данные получены на основе ",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     text = ct[0].toStdString() + " случайных";
     print_text(page_count-1,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"звездных треков длительностью по ",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     text = minute_validator(ct[1].toInt(),ct[2].toInt()) +"." ;
     print_text(page_count-1,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[page_count-1]);

     draw_graph_2(page_count-1,val_vect,ct[0].toInt(),"r2");

     x+=8;

HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          В результате теста выполнены следующие измерения:",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Отклонения углов ориентации между измерениями в МЗД и установкой в  " ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "ОДС в приборной системе координат – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     text = " Частота выдачи МЗД АЗДК-1 кадров по статистическим данным – см. Рис. " + std::to_string(ris_n++)+".";
     print_text(page_count-1,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[page_count-1]);

create_page();
calantitul(page_count-1);
x=0;

QString p;

     p = parser->Png_path_veryf("/azdk" + azdk.number + "r2/xyz-azdk"+ azdk.number +"r2-angles.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 340, 4703/9.2,1857/9.2);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Отклонения углов ориентации между измерениями в МЗД и  ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 360);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          установкой в ОДС в приборной системе координат. ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 375);
HPDF_Page_EndText(pages[page_count-1]);

     p = parser->Png_path_veryf("/azdk" + azdk.number + "r2/stats-frequency-azdk"+ azdk.number +"r2.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 740, 4678/9.2,2423/9.2);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Частота выдачи МЗД АЗДК-1 кадров по статистическим данным.  ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 760);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          Красными точками обозначены «плохие» кадры, синими – ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 775);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          прочитанные кадры, зелеными – кадры с успешными  ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 790);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          отождествлениями  ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 805);
HPDF_Page_EndText(pages[page_count-1]);

     emit log_message("r2 отчет создан");

 }

 void PDF_creator::r3_otchet()
 {
     //auto ct = parser->Frames_count_and_time("/"+template_files[2]+azdk.number,"r3");
     auto ct = parser->Frames_count_and_time_ver2("/"+template_files[2]+azdk.number,"/"+template_files[1]+azdk.number,"r3",azdk.number);
     auto val_vect = parser->parse_resulte_table_2_ver2("/"+template_files[0]+azdk.number + "r3.txt","/"+template_files[2]+azdk.number + "r3.txt");
     std::string text = "Тест-"+ std::to_string(test) + " (статистический)";

     emit log_message("Создание ro3 отчета");

     create_page();
     calantitul(page_count-1);
     int x=0;

     float tw = HPDF_Page_TextWidth(pages[page_count-1], text.c_str());

HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,text.c_str(),16,(HPDF_Page_GetWidth(pages[page_count-1]) - tw-50) / 2,
     HPDF_Page_GetHeight(pages[page_count-1]) - 50);
HPDF_Page_EndText(pages[page_count-1]);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "          Задачей теста-"+std::to_string(test++)+" являлся набор статистики количества отождествленных ";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"кадров и количество срывов ведений МЗД АЗДК-1 на случайных участках неба ",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"при скорости вращения КА 3°/сек. Данные получены на основе ",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     text = ct[0].toStdString() + " случайных";
     print_text(page_count-1,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"звездных треков длительностью по ",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     text = minute_validator(ct[1].toInt(),ct[2].toInt()) +"." ;
     print_text(page_count-1,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[page_count-1]);

     draw_graph_2(page_count-1,val_vect,ct[0].toInt(),"r3");

     x+=8;

HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          В результате теста выполнены следующие измерения:",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Отклонения углов ориентации между измерениями в МЗД и установкой в  " ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "ОДС в приборной системе координат – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     text = " Частота выдачи МЗД АЗДК-1 кадров по статистическим данным – см. Рис. " + std::to_string(ris_n++)+".";
     print_text(page_count-1,rus_std,text.c_str(),12);
HPDF_Page_EndText(pages[page_count-1]);

create_page();
calantitul(page_count-1);
x=0;

QString p;

     p = parser->Png_path_veryf("/azdk" + azdk.number + "r3/xyz-azdk"+ azdk.number +"r3-angles.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 340, 4703/9.2,1857/9.2);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Отклонения углов ориентации между измерениями в МЗД и  ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 360);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          установкой в ОДС в приборной системе координат. ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 375);
HPDF_Page_EndText(pages[page_count-1]);

     p = parser->Png_path_veryf("/azdk" + azdk.number + "r3/stats-frequency-azdk"+ azdk.number +"r3.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 740, 4678/9.2,2423/9.2);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Частота выдачи МЗД АЗДК-1 кадров по статистическим данным.  ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 760);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          Красными точками обозначены «плохие» кадры, синими – ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 775);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          прочитанные кадры, зелеными – кадры с успешными  ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 790);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          отождествлениями  ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 805);
HPDF_Page_EndText(pages[page_count-1]);

    emit log_message("r3 отчет создан");
 }

 void PDF_creator::o_otchet()
 {
     //auto ct = parser->Frames_count_and_time("/"+template_files[2]+azdk.number,"o");
     auto ct = parser->Frames_count_and_time_ver2("/"+template_files[2]+azdk.number,"/"+template_files[1]+azdk.number,"o",azdk.number);
     auto val_vect = parser->parse_resulte_table_2_ver2("/"+template_files[0]+azdk.number + "o.txt","/"+template_files[2]+azdk.number + "o.txt");
     std::string text = "Тест-"+ std::to_string(test) + " (орбитальный)";

     emit log_message("Создание о отчета");

     create_page();
     calantitul(page_count-1);
     int x=0;

     float tw = HPDF_Page_TextWidth(pages[page_count-1], text.c_str());

HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,text.c_str(),16,(HPDF_Page_GetWidth(pages[page_count-1]) - tw-50) / 2,
     HPDF_Page_GetHeight(pages[page_count-1]) - 50);
HPDF_Page_EndText(pages[page_count-1]);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "          Тест-"+std::to_string(test++)+" служит для проверки работы прибора при имитации движения по";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "орбите. Продолжительность теста составила " + minute_validator(ct[1].toInt(),ct[2].toInt()) + ".";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);

     draw_graph_2(page_count-1,val_vect,ct[0].toInt(),"o");

     x+=8;

HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          В результате теста выполнены следующие измерения:",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Компонент кватерниона w, измеренного в МЗД (красные точки) и" ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "компонент кватерниона, установленного в ОДС (синяя линия) – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Компонент кватерниона x, измеренного в МЗД (красные точки) и" ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "компонент кватерниона, установленного в ОДС (синяя линия) – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Компонент кватерниона y, измеренного в МЗД (красные точки) и" ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "компонент кватерниона, установленного в ОДС (синяя линия) – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Компонент кватерниона z, измеренного в МЗД (красные точки) и" ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "компонент кватерниона, установленного в ОДС (синяя линия) – см. Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Частота выдачи МЗД АЗДК-1 кадров по статистическим данным показана " ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "на Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Разница углов ориентации между измерениями в МЗД и установкой в ОДС " ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "в приборной системе координат – Рис. " + std::to_string(ris_n++)+";";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_bold,"—",12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
     print_text(page_count-1,rus_std," Гистограммы измерений ошибок ориентации Δx, Δy, Δz, представленные в " ,12);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     text = "системе координат прибора – Рис. " + std::to_string(ris_n++)+".";
     print_text(page_count-1,rus_std,text.c_str(),12,50,HPDF_Page_GetHeight(pages[0]) - x_start_pos-28*x++);
HPDF_Page_EndText(pages[page_count-1]);

     create_page();
     calantitul(page_count-1);
     x=0;

QString p;

     p = parser->Png_path_veryf("/azdk" + azdk.number + "o/quats-azdk"+ azdk.number +"o.w.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 340, 2339/4.6,1235/4.6);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона w, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 360);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия). ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 375);
HPDF_Page_EndText(pages[page_count-1]);

     p = parser->Png_path_veryf("/azdk" + azdk.number + "o/quats-azdk"+ azdk.number +"o.x.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 740, 2339/4.6,1235/4.6);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона x, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 760);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия).",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 775);
HPDF_Page_EndText(pages[page_count-1]);

     create_page();
     calantitul(page_count-1);
     x=0;

     p = parser->Png_path_veryf("/azdk" + azdk.number + "o/quats-azdk"+ azdk.number +"o.y.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 340, 2339/4.6,1235/4.6);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона y, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 360);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия). ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 375);
HPDF_Page_EndText(pages[page_count-1]);

     p = parser->Png_path_veryf("/azdk" + azdk.number + "o/quats-azdk"+ azdk.number +"o.z.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 740, 2339/4.6,1235/4.6);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона z, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 760);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия).",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 775);
HPDF_Page_EndText(pages[page_count-1]);

     create_page();
     calantitul(page_count-1);
     x=0;

     p = parser->Png_path_veryf("/azdk" + azdk.number + "o/stats-frequency-azdk"+ azdk.number +"o.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 340, 4678/9.2,2423/9.2);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Частота выдачи МЗД АЗДК-1 кадров по статистическим данным.  ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 360);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          Красными точками обозначены «плохие» кадры, синими – ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 375);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          прочитанные кадры, зелеными – кадры с успешными  ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 390);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          отождествлениями  ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 405);
HPDF_Page_EndText(pages[page_count-1]);


     p = parser->Png_path_veryf("/azdk" + azdk.number + "o/xyz-azdk"+ azdk.number +"o-angles.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 40, HPDF_Page_GetHeight(pages[page_count-1]) - 740, 4703/9.2,1857/9.2);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Разница углов ориентации между измерениями в МЗД и установкой в  ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 760);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          ОДС в приборной системе координат.",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 775);
HPDF_Page_EndText(pages[page_count-1]);

     create_page();
     calantitul(page_count-1);
     x=0;

     p = parser->Png_path_veryf("/azdk" + azdk.number + "o/xyz-azdk"+ azdk.number +"o.png");
     image = HPDF_LoadPngImageFromFile(pdf,p.toStdString().c_str());
     HPDF_Page_DrawImage (pages[page_count-1], image, 125-60, HPDF_Page_GetHeight(pages[page_count-1]) - 360-150, 536/1.1,489/1.1);

HPDF_Page_BeginText(pages[page_count-1]);
     text = "Рис. " + std::to_string(ris_g++) + " Компонент кватерниона y, измеренного в МЗД (красные точки) и ";
     print_text(page_count-1,rus_std,text.c_str(),10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 380-150);
HPDF_Page_EndText(pages[page_count-1]);
HPDF_Page_BeginText(pages[page_count-1]);
     print_text(page_count-1,rus_std,"          компонент кватерниона, установленного в ОДС (синяя линия). ",10,x_start_pos,HPDF_Page_GetHeight(pages[page_count-1]) - 395-150);
HPDF_Page_EndText(pages[page_count-1]);

     emit log_message("о отчет создан");
 }
