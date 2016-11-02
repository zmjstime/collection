#include "widget.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
//    -	Baud Rate : 38400 bps
//    -	Data Bit : 8
//    -	Stop Bit : 1
//    -	Parity Bit : None
//    -	Flow Control : None

    m_serialport = new QSerialPort;
    m_serialport->setPortName("ComName");
    m_serialport->setBaudRate(38400);
    m_serialport->setDataBits(QSerialPort::Data8);
    m_serialport->setParity(QSerialPort::NoParity);
    m_serialport->setStopBits(QSerialPort::OneStop);
    m_serialport->setFlowControl(QSerialPort::NoFlowControl);
}

Widget::~Widget()
{

}
