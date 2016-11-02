#include "urinalysis.h"
#include <QApplication>
#include <QDate>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    urinalysis w;
//    QDate time = QDate::currentDate();
//    if((time.month() == 10 && time.day() == 31) ||
//    (time.month() == 11 && (time.day() == 1 || time.day() == 2 || time.day() == 3 || time.day() == 4)))
//    {
//        qDebug() << time.month();
//        w.showFullScreen();
        w.showMaximized();
//        w.show();
//    }
//    else
//    {
//        w.close();
//    }


    return a.exec();
}
