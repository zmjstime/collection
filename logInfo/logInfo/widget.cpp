#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    qDebug("This is a debug message");
    qWarning("This is a warning messagewwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww");
    qCritical("This is a critical message");
}

Widget::~Widget()
{

}
