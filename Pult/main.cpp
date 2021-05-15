#include "pultwidget.h"
//#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PultWidget w;
    w.show();
    w.setWindowTitle("Пульт");
    SU_ROV su;

    return a.exec();
}
