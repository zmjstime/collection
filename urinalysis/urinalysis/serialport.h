#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QWidget>
#include <QSerialPort>
#include "slavethread.h"

class serialPort : public QWidget
{
    Q_OBJECT
public:
    explicit serialPort(QWidget *parent = 0);
    ~serialPort();
signals:
    dataInfo(float, float);
private slots:
    void showRequest(QByteArray str);
private:
    float getAlb(int albIn);
    float getCre(int creIn);

    QSerialPort *m_port;
    SlaveThread m_thread;
    QString m_portName;
    QByteArray m_allData;
};

#endif // SERIALPORT_H
