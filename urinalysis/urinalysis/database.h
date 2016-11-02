#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSqlDatabase>
#include <define.h>

class database
{
public:
    database();
    ~database();

    bool insert(const urinalysisInfo &info);

    bool selectAll(QVector<urinalysisInfo> &infoVec);

    bool deleteData(const urinalysisInfo &info);
private:
    QSqlDatabase m_dbConnect;
};

#endif // DATABASE_H
