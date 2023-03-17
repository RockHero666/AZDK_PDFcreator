#include "mainwindow.h"

#include <QApplication>
#include <QStyle>


int WINAPI wWinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    PWSTR       lpCmdLine,
    int         nCmdShow
)
{
    
	QApplication app(__argc, __argv);
	MainWindow w;

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



	
		w.show();
		return app.exec();
	
		
	
}
