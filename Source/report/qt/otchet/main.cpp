#include "mainwindow.h"

#include <QApplication>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;


    try {



    w.show();
    return a.exec();

    }
    catch (std::runtime_error& ex) {
            std::cout << ex.what()<<"\n";
             w.error(ex.what());
            return 1;
        }
}
