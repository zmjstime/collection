#include "serialport.h"
#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QMessageBox>
#include <QTextCodec>

serialPort::serialPort(QWidget *parent) :
    QWidget(parent)
{
    QFile file(QApplication::applicationDirPath() + "/cfg.ini");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        m_portName = file.readLine().trimmed();
    }

    if(m_portName == "")
    {
        m_thread.startSlave("COM2", 3000, "s");
    }
    else
    {
        m_thread.startSlave(m_portName, 3000, "s");
    }
    connect(&m_thread, &SlaveThread::request, this, &serialPort::showRequest);

    QTextCodec *codec = QTextCodec::codecForName("System"); //获取系统编码
    QTextCodec::setCodecForLocale(codec);
}

serialPort::~serialPort()
{
}

void serialPort::showRequest(QByteArray str)
{
    if(str.at(0) == '*' && str.at(1) == 'S' && str.at(2) == '5')
    {
        m_allData.clear();
        m_allData = str;
    }
    else
    {
        m_allData.append(str);
    }

    if(m_allData.length() <= 59)
    {
        return;
    }
    else
    {
        int albIn = QString(m_allData.at(58)).toInt();
        int creIn = QString(m_allData.at(59)).toInt();

        float alb = getAlb(albIn);
        float cre = getCre(creIn);


        emit dataInfo(alb, cre);


        qDebug() << albIn << alb;
        qDebug() << creIn << cre;
    }
}

float serialPort::getAlb(int albIn)
{
    float alb = 0;
    if(albIn == 0)
    {
        alb = 10;
    }
    else if(albIn == 1)
    {
        alb = 30;
    }
    else if(albIn == 2)
    {
        alb = 80;
    }
    else if(albIn == 3)
    {
        alb = 150;
    }
    else
    {
        alb = 0;
    }

    return alb;
}

float serialPort::getCre(int creIn)
{
    float cre = 0;
    if(creIn == 0)
    {
        cre = 10;
    }
    else if(creIn == 1)
    {
        cre = 50;
    }
    else if(creIn == 2)
    {
        cre = 100;
    }
    else if(creIn == 3)
    {
        cre = 200;
    }
    else if(creIn == 4)
    {
        cre = 300;
    }
    else
    {
        cre = 0;
    }

    return cre;
}
