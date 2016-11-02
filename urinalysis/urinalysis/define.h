#ifndef DEFINE_H
#define DEFINE_H
#include <QString>

struct urinalysisInfo
{
//    姓名		name
//    性别		sex
//    年龄		age
//    病员号		patientID
//    标本号		sampleID
//    采样时间	sampleDate
//    科室		administrativeOffice
//    床号		bedID
//    标本类型	sampleType
//    送检医生	senderDoctor
//    微蛋白		ALB
//    尿肌酐		CRE
//    ACR = 微蛋白/尿肌酐
//    检测时间	detectionDate
//    报告时间	reportDate
//    检验者		proofer
//    审核者		auditor
//    备注		remarks

    QString name;
    QString sex;
    int age;
    QString patientID;
    int sampleID;
    QString sampleDate;
    QString administrativeOffice;
    int bedID;
    QString sampleType;
    QString senderDoctor;
    float ALB;
    float CRE;
//    float ACR;
    QString detectionDate;
    QString reportDate;
    QString proofer;
    QString auditor;
    QString remarks;

    QString insertStr() const
    {
        return QString("insert into urinalysisInfo values('%1', '%2', %3, '%4', %5, '%6', '%7', %8, '%9', '%10',"
                              " %11, %12, '%13', '%14', '%15', '%16', '%17')")
                .arg(name)
                .arg(sex)
                .arg(age)
                .arg(patientID)
                .arg(sampleID)
                .arg(sampleDate)
                .arg(administrativeOffice)
                .arg(bedID)
                .arg(sampleType)
                .arg(senderDoctor)
                .arg(ALB)
                .arg(CRE)
                .arg(detectionDate)
                .arg(reportDate)
                .arg(proofer)
                .arg(auditor)
                .arg(remarks);
    }

    QString deleteStr() const
    {
        return QString("delete from urinalysisInfo where (name = '%1' and sex ='%2' and age = %3 "
                       "and patientID = '%4' and sampleID = %5 and bedID = %6 "
                       "and sampleType = '%7' and ALB = %8 and CRE = %9 "
                       "and remarks = '%10')")
                .arg(name)
                .arg(sex)
                .arg(age)
                .arg(patientID)
                .arg(sampleID)
                .arg(bedID)
                .arg(sampleType)
                .arg(ALB)
                .arg(CRE)
                .arg(remarks);
//        return QString("delete from urinalysisInfo where (name = '%1' and sex ='%2' and age = %3 "
//                       "and patientID = '%4' and sampleID = %5 and sampleDate = '%6' "
//                       "and administrativeOffice = '%7' and bedID = %8 and sampleType = '%9' "
//                       "and senderDoctor = '%10' and ALB = %11 and CRE = %12"
//                       "and detectionDate = '%13' and reportDate = '%14' and proofer = '%15' "
//                       "and auditor = '%16' and remarks = '%17')")
//                .arg(name)
//                .arg(sex)
//                .arg(age)
//                .arg(patientID)
//                .arg(sampleID)
//                .arg(sampleDate)
//                .arg(administrativeOffice)
//                .arg(bedID)
//                .arg(sampleType)
//                .arg(senderDoctor)
//                .arg(ALB)
//                .arg(CRE)
//                .arg(detectionDate)
//                .arg(reportDate)
//                .arg(proofer)
//                .arg(auditor)
//                .arg(remarks);
    }
};

#endif // DEFINE_H
