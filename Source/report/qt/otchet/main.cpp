#include "mainwindow.h"

#include <QApplication>
#include <QStyle>
#include <Vector>
#include<QMessageBox>
#include <iostream>

QString is_no_gui(int argc, char* argv[], MainWindow& w)
{
    std::vector<QString> args;
    QString ini_path;

    for (int i = 0; i < argc; i++)
    {
        args.push_back(argv[i]);
        
    }
    try
    {
        for (int i = 0; i < args.size(); i++)
        {
            if (args[i].indexOf("-nogui") != -1)
            {
                ini_path = args.at(i + 1);
                break;
            }
        }
    }
    catch (...)
    {
        QMessageBox::about(&w, "ERROR", "Bad argument = -nogui \"empty\"");
    }



    return ini_path;

}



void style_gui(QApplication& app)
{
    QString defaultStyleName = qApp->style()->objectName();
    app.setStyle("Fusion");
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

    app.setPalette(palette);
}




int main(int argc, char* argv[])
{
    
    QApplication app(argc, argv);





	MainWindow w;

  



    style_gui(app);
    
    QString ini_path = is_no_gui(argc,argv,w);


    if (ini_path.isEmpty())
        w.show();
    else
        w.set_ini_file(ini_path);
    

	return app.exec();
	
		
	
}
