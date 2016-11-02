#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QSerialPort;
class QSerialPortInfo;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QSerialPort *m_serialport;
};

#endif // WIDGET_H
