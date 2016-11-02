#include "database.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>

dataBase::dataBase()
{
    QSqlDatabase dbConnect;
    dbConnect = QSqlDatabase::addDatabase("QSQLITE");
    dbConnect.setDatabaseName("MTPSQLLITE3.db");
    if (!dbConnect.open())
    {
        qDebug() << "open DB failed";
    }

    QSqlQuery query;

    QString sql = ("select commanderid, name, arms, photo from Commander");
    query.exec(sql);

    while(query.next())
    {
//        commanderStruct info;
//        info.id = query.value(0).toString();
//        info.name = query.value(1).toString();
//        info.arms = query.value(2).toString();
//        info.photo = query.value(3).toString();
//        dataVec.push_back(info);
    }

    dbConnect.commit();
    dbConnect.close();
}
