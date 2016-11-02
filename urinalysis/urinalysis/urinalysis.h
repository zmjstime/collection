#ifndef URINALYSIS_H
#define URINALYSIS_H

#include <QWidget>
#include <QPrinter>
#include <QTableWidget>
#include <database.h>
#include "printforms.h"
#include "serialport.h"

namespace Ui {
class urinalysis;
}

class urinalysis : public QWidget
{
    Q_OBJECT

public:
    explicit urinalysis(QWidget *parent = 0);
    ~urinalysis();
private:
    void init();
    void initConnect();
    bool isEmpty();

private slots:
    void clearForms();

    void setARC(QString);

    void selectAllInfo();

    void fillTableWidget();

    void setForms(int row, int);

    void getForms(urinalysisInfo &info);

    void saveData();

    void deleteData();

    void print();

    void getPortData(float alb, float cre);
private:
    bool compareDateString(QString date1, QString date2);

    QDateTime getDateTime(QString dateTime);

    Ui::urinalysis *ui;
    database m_dataBase;

    serialPort *m_port;

    QVector<urinalysisInfo> m_allInfoVec;
    QVector<int> m_currentTableIndexInAll;
};

#endif // URINALYSIS_H
