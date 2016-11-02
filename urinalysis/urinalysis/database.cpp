#include "database.h"
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>

database::database()
{
    m_dbConnect = QSqlDatabase::addDatabase("QSQLITE");
    m_dbConnect.setDatabaseName(QApplication::applicationDirPath() + "/data.db");
    if (!m_dbConnect.open())
    {
        qDebug() << "open DB failed!";
        QMessageBox::warning(NULL, "warn", "open DB failed");
    }
    else
    {
        qDebug() << "open DB sucess!";
    }
}

database::~database()
{
    m_dbConnect.close();
}

bool database::insert(const urinalysisInfo &info)
{
    QSqlQuery query;
    query.exec(info.insertStr());

    qDebug() << info.insertStr();

    return m_dbConnect.commit();
}

bool database::selectAll(QVector<urinalysisInfo> &infoVec)
{
    infoVec.clear();
    QSqlQuery query;
    if(query.exec("select *from urinalysisInfo"))
    {
        while(query.next())
        {
            urinalysisInfo info;
            info.name = query.value(0).toString();
            info.sex = query.value(1).toString();
            info.age = query.value(2).toInt();
            info.patientID = query.value(3).toString();
            info.sampleID = query.value(4).toInt();
            info.sampleDate = query.value(5).toString();
            info.administrativeOffice = query.value(6).toString();
            info.bedID = query.value(7).toInt();
            info.sampleType = query.value(8).toString();
            info.senderDoctor = query.value(9).toString();
            info.ALB = query.value(10).toFloat();
            info.CRE = query.value(11).toFloat();
            info.detectionDate = query.value(12).toString();
            info.reportDate = query.value(13).toString();
            info.proofer = query.value(14).toString();
            info.auditor = query.value(15).toString();
            info.remarks = query.value(16).toString();

            infoVec.push_back(info);
        }
    }
    else
    {
        return false;
    }

    return m_dbConnect.commit();
}

bool database::deleteData(const urinalysisInfo &info)
{
    QSqlQuery query;
    query.exec(info.deleteStr());

    qDebug() << info.deleteStr();

    return m_dbConnect.commit();
}
