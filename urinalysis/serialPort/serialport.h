#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QWidget>


class serialPort : public QWidget
{
public:
    explicit serialPort(QWidget *parent = 0);
    ~serialPort();
};

#endif // SERIALPORT_H
