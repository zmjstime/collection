#include "widget.h"
#include <QApplication>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    Widget w;
    //    w.show();

    QPrinter printer;
    QPrintDialog printDialog(&printer);
    if (printDialog.exec())
    {
        QTextDocument *doc = new QTextDocument("hello print!");
        doc->print(&printer);
    }

    return a.exec();
}
