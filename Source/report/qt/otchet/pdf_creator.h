#ifndef PDF_CREATOR_H
#define PDF_CREATOR_H

#include <QObject>
#include <QVector>
#include <Windows.h>
#include "azdk.h"
#include "parser.h"
#include "hpdf.h"


class PDF_creator: public QObject
{
     Q_OBJECT
private:

    QString fname;
    QString save_path; 
    QVector<QString> template_files; // ��������� ����� ������ ����������� ��� ������������ �����
    QVector<bool> sfx_state; // ������ ��������� ��������� ��� ������ ���������� �������
    AZDK azdk;
    Parser *parser;
    int vect_value_size = 0; // ������� ��� ������ ���������� ������������� ������� ��� � ������ n>30
    int page_count = 0;// ������� �������
    int numer_of_line = 1; // ������� ����� ��� ������� ���
    int ris_n = 1;// ������� ��� ������(��������) � ��������� ����������
    int ris_g = 1;// ������� ��� ������(��������) � ���������� ����� �������
    int ris_t = 1;// ������� ��� ������� ���
    int test = 1;// ������� ������ �����
    int x_start_pos = 90;// ������� ������
    bool thread_gate = 0;// ���������� �������
    QString font_name;
    HPDF_Image image;
    HPDF_Doc pdf;
    HPDF_Font font;
    std::vector<HPDF_Page> pages;
    const char* rus_bold; // ���� ������� ������
    const char* rus_std; // ���� ������������ ������
    bool is_no_gui = 0;

    static PDF_creator* pdf_ptr;// ������� ���������
    PDF_creator(const QString& font_name = "arial", QObject* parent = nullptr);

public:

    ~PDF_creator();
    PDF_creator(PDF_creator& other) = delete;
    void operator=(PDF_creator& other) = delete;
    static PDF_creator* get_instance(const QString& font_name = "arial", QObject* parent = nullptr);

    static void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void* user_data); // �������� ������� �������

    void create_pdf();
    void set_font_name(const QString& font_name);
    void create_page();
    void set_thread_gate(bool val);
    void save();
    void free();
    void start();
    bool font_setting();
    void end_work();// restart
    void set_parser(Parser & parser);
    void set_save_path(const QString & path);
    void set_file_name(const QString & name);
    void set_template_files(const QString & file1,const QString & file2,const QString & file3);
    void set_sfx_state(bool s1,bool s2,bool s3,bool s4,bool s5,bool s6);
    void set_AZDK(const AZDK & azdk);
    void set_gui_mod(bool mode);

    std::string minute_validator(int min,bool flag60);// ��������� �� 10 � 60 �������
    void print_text(int page,const char * font_setting,const char * text,int size_text,float x_pos,float y_pos);
    void draw_graph(int page,QVector<QVector<QString>> & vect_value);// �������� ����� ������� ���
    void top_of_graph(int pos,double height,int start_table,int std_cell,
        int long_cell,int PAGE_HEIGHT,int PAGE_WIDTH , int page);// ����� ������� ���
    void both_of_graph(int pos,double height,int start_table,int std_cell,
        int long_cell,int PAGE_HEIGHT,int PAGE_WIDTH , int page,
        QVector<QVector<QString>> & vect_value);// ��� ������� ���
    void draw_graph_2(int page,QVector<int> & vect_value,int frames,const QString & sfx); // ������� ���
    void calantitul(int page);
    


    
    void titul_list();
    void s_otchet();
    void r01_otchet();
    void r1_otchet();
    void r2_otchet();
    void r3_otchet();
    void o_otchet();

signals:
    void finished();
    void progress(int val);  // ��� ������� ����
    void error(const QString & message);
    void unblock_ui();
    void log_message(const QString & message,QRgb color = qRgb(255, 255, 255));
};


#endif // PDF_CREATOR_H
