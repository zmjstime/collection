#include "urinalysis.h"
#include "ui_urinalysis.h"
#include "database.h"
#include <QDateTime>
#include <QRegExp>
#include <QValidator>
#include <QPainter>
#include <QPrintPreviewDialog>
#include <QScrollBar>
#include <QTableWidgetItem>
#include <QDebug>
#include <QMessageBox>

urinalysis::urinalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::urinalysis)
{
    ui->setupUi(this);

    //初始化
    init();

    //初始化表单
    clearForms();

    //初始化信号槽
    initConnect();

    //查询所有数据
    selectAllInfo();

    //填充tablewidget
    fillTableWidget();
}

urinalysis::~urinalysis()
{
    delete ui;
}

void urinalysis::init()
{
    this->setWindowTitle("安义县中医院");
    ui->titleLabel->setText("安义县中医院尿液分析ACR检测报告单");
    for(int index = 0; index < 120; ++index)
    {
        ui->ageComboBox->addItem(QString::number(index));
    }

    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, this);
    ui->ALBLineEdit->setValidator(validator);
    ui->CRELineEdit->setValidator(validator);

    ui->tableWidget->setColumnCount(5);

    QStringList headers;
    headers << "姓名" << "性别" << "病员号" << "送检医生" << "报告时间";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    //设置不能多选, 选择行, 不能编辑, 内容自适应表格
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_port = new serialPort(this);

    ui->officeLineEdit->setCompleterFileName(QApplication::applicationDirPath() + "/keshi.txt");
    ui->senderDoctorLineEdit->setCompleterFileName(QApplication::applicationDirPath() + "/songjianyisheng.txt");
    ui->prooferLineEdit->setCompleterFileName(QApplication::applicationDirPath() + "/jianyan.txt");
    ui->auditorLineEdit->setCompleterFileName(QApplication::applicationDirPath() + "/shenhe.txt");
    ui->searchLineEdit->setCompleterFileName(QApplication::applicationDirPath() + "/songjianyisheng.txt");

    ui->autoGetData->setChecked(true);

    ui->remarksLineEdit->setText("本报告仅对此次送检标本负责。");
}

void urinalysis::selectAllInfo()
{
    m_allInfoVec.clear();
    //查询所有数据
    m_dataBase.selectAll(m_allInfoVec);
}

void urinalysis::initConnect()
{
    //从串口获取数据
    connect(m_port, SIGNAL(dataInfo(float,float)), this, SLOT(getPortData(float,float)));

    //给ARC赋值
    connect(ui->ALBLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setARC(QString)));
    connect(ui->CRELineEdit, SIGNAL(textChanged(QString)), this, SLOT(setARC(QString)));

    //清除
    connect(ui->clearPushButton, SIGNAL(clicked()), this, SLOT(clearForms()));

    //查询
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(fillTableWidget()));

    //保存数据
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveData()));

    //显示tablewidget内容
    connect(ui->tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(setForms(int,int)));

    //关闭窗口
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));

    //删除数据
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteData()));

    //打印
    connect(ui->printButton, SIGNAL(clicked()), this, SLOT(print()));
}

bool urinalysis::isEmpty()
{
    return ui->nameLineEdit->text().isEmpty() || ui->patientIDLineEdit->text().isEmpty() ||
            ui->sampleIDLineEdit->text().isEmpty() || ui->sampleTypeLineEdit->text().isEmpty() ||
            ui->officeLineEdit->text().isEmpty() || ui->senderDoctorLineEdit->text().isEmpty() ||
            ui->bedIDLineEdit->text().isEmpty() || ui->ACRLineEdit->text().isEmpty() ||
            ui->ALBLineEdit->text().isEmpty() || ui->CRELineEdit->text().isEmpty() ||
            ui->auditorLineEdit->text().isEmpty() || ui->prooferLineEdit->text().isEmpty();
}

void urinalysis::fillTableWidget()
{
    m_currentTableIndexInAll.clear();
    ui->tableWidget->setRowCount(0);
    for(int index = 0; index < m_allInfoVec.size(); ++index)
    {
        urinalysisInfo info = m_allInfoVec[index];
        QString beginDate = ui->beginDateEdit->text();
        QString endDate = ui->endDateEdit->text();

        QString dateStr = info.reportDate.replace('-', '/');
        dateStr = dateStr.split(' ').at(0);

        //起始日期大于info日期 或者 info日期大于结束日期
        if(compareDateString(beginDate, dateStr) || compareDateString(dateStr, endDate))
        {
            continue;
        }

        QString inputName = ui->searchLineEdit->text().trimmed();
        if(inputName == "" || info.name.contains(inputName) || info.senderDoctor.contains(inputName))
        {
            int rowCount = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowCount);
            ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(info.name));
            ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(info.sex));
            ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(info.patientID));
            ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(info.senderDoctor));
            ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(info.reportDate));
            m_currentTableIndexInAll.push_back(index);
        }
    }
}

void urinalysis::setForms(int row, int)
{
    if(row < 0 || row >= m_currentTableIndexInAll.size())
    {
        return;
    }

    int index = m_currentTableIndexInAll[row];
    urinalysisInfo &info = m_allInfoVec[index];
    ui->nameLineEdit->setText(info.name);
    if(info.sex == "男")
    {
        ui->maleRadioButton->setChecked(true);
    }
    else
    {
        ui->femaleRadioButton->setChecked(true);
    }

    ui->ageComboBox->setCurrentText(QString::number(info.age));

    ui->patientIDLineEdit->setText(info.patientID);
    ui->sampleIDLineEdit->setText(QString::number(info.sampleID));
    ui->sampleTypeLineEdit->setText(info.sampleType);

    ui->officeLineEdit->setText(info.administrativeOffice.trimmed());
    ui->senderDoctorLineEdit->setText(info.senderDoctor.trimmed());

    ui->sampleDateEdit->setDateTime(getDateTime(info.sampleDate));
    ui->detectionDateEdit->setDateTime(getDateTime(info.detectionDate));

    ui->bedIDLineEdit->setText(QString::number(info.bedID));

    ui->ALBLineEdit->setText(QString::number(info.ALB));
    ui->CRELineEdit->setText(QString::number(info.CRE));

    ui->prooferLineEdit->setText(info.proofer.trimmed());
    ui->auditorLineEdit->setText(info.auditor.trimmed());

    ui->reportDateEdit->setDateTime(getDateTime(info.reportDate));

    ui->remarksLineEdit->setText("本报告仅对此次送检标本负责。");
}

void urinalysis::getForms(urinalysisInfo &info)
{
    info.name = ui->nameLineEdit->text();
    if(ui->maleRadioButton->isChecked())
    {
        info.sex = "男";
    }
    else
    {
        info.sex = "女";
    }
    info.age = ui->ageComboBox->itemText(ui->ageComboBox->currentIndex()).toInt();

    info.patientID = ui->patientIDLineEdit->text();
    info.sampleID = ui->sampleIDLineEdit->text().toInt();
    info.sampleType = ui->sampleTypeLineEdit->text();

    info.administrativeOffice = ui->officeLineEdit->text().trimmed();
    info.senderDoctor = ui->senderDoctorLineEdit->text().trimmed();

    info.sampleDate = ui->sampleDateEdit->dateTime().toString("yyyy/MM/dd hh:mm:ss");
    info.detectionDate = ui->detectionDateEdit->dateTime().toString("yyyy/MM/dd hh:mm:ss");

    info.bedID = ui->bedIDLineEdit->text().toInt();

    info.ALB = ui->ALBLineEdit->text().toFloat();
    info.CRE = ui->CRELineEdit->text().toFloat();

    info.proofer = ui->prooferLineEdit->text().trimmed();
    info.auditor = ui->auditorLineEdit->text().trimmed();
    info.reportDate = ui->reportDateEdit->dateTime().toString("yyyy/MM/dd hh:mm:ss");

    info.remarks = ui->remarksLineEdit->text();
}

void urinalysis::saveData()
{
    if(isEmpty())
    {
        return;
    }
    urinalysisInfo info;
    getForms(info);
    m_dataBase.insert(info);

    //重新读取所有数据
    selectAllInfo();
    //更新tablewidget
    fillTableWidget();
}

void urinalysis::deleteData()
{
    int index = ui->tableWidget->currentRow();
    if(index < 0 || index >= m_currentTableIndexInAll.size())
    {
        return;
    }
    urinalysisInfo info = m_allInfoVec[m_currentTableIndexInAll[index]];

    m_dataBase.deleteData(info);

    selectAllInfo();

    fillTableWidget();
}

void urinalysis::print()
{
    urinalysisInfo info;
    getForms(info);
    printForms print;
    print.setForms(info);
    print.printView();
}

void urinalysis::getPortData(float alb, float cre)
{
    if(ui->autoGetData->isChecked())
    {
        ui->ALBLineEdit->setText(QString::number(alb));
        ui->CRELineEdit->setText(QString::number(cre));
    }
}

//返回date1 > date2, 相等返回false
bool urinalysis::compareDateString(QString date1, QString date2)
{
    date1 = date1.replace('-', '/');
    date2 = date2.replace('-', '/');

    QStringList dateList1 = date1.split('/');
    QStringList dateList2 = date2.split('/');

    //年
    if(QString(dateList1.at(0)).toInt() == QString(dateList2.at(0)).toInt())
    {
        //月
        if(QString(dateList1.at(1)).toInt() == QString(dateList2.at(1)).toInt())
        {
            //日
            return QString(dateList1.at(2)).toInt() > QString(dateList2.at(2)).toInt();
        }
        else
        {
            return QString(dateList1.at(1)).toInt() > QString(dateList2.at(1)).toInt();
        }
    }
    else
    {
        return QString(dateList1.at(0)).toInt() > QString(dateList2.at(0)).toInt();
    }
}

QDateTime urinalysis::getDateTime(QString dateTime)
{
    dateTime = dateTime.replace('-', '/');

    return QDateTime::fromString(dateTime, "yyyy/MM/dd hh:mm:ss");
}

void urinalysis::clearForms()
{
    ui->nameLineEdit->clear();
    ui->maleRadioButton->setChecked(true);

    ui->patientIDLineEdit->clear();
    ui->sampleIDLineEdit->clear();
    ui->sampleTypeLineEdit->clear();

    ui->officeLineEdit->clear();
    ui->senderDoctorLineEdit->clear();

    ui->sampleDateEdit->setDateTime(QDateTime::currentDateTime());
    ui->detectionDateEdit->setDateTime(QDateTime::currentDateTime());

    ui->bedIDLineEdit->clear();

    ui->ALBLineEdit->clear();
    ui->CRELineEdit->clear();
    ui->ACRLineEdit->clear();

    ui->prooferLineEdit->clear();
    ui->auditorLineEdit->clear();
    ui->reportDateEdit->setDateTime(QDateTime::currentDateTime());

//    ui->remarksLineEdit->clear();

    QDate currentDate = QDate::currentDate();
    int year = currentDate.year();
    int month = currentDate.month();
    int day = currentDate.day();
    if(month == 1)
    {
        month = 12;
        year--;
    }
    else
    {
        month--;
    }

    ui->beginDateEdit->setDate(QDate(year, month, day));
    ui->endDateEdit->setDate(QDate::currentDate());
}

void urinalysis::setARC(QString)
{
    if(ui->ALBLineEdit->text() == "" || ui->CRELineEdit->text() == ""
            || ui->CRELineEdit->text().toFloat() == 0)
    {
        return;
    }
    float alb = ui->ALBLineEdit->text().toFloat();
    float cre = ui->CRELineEdit->text().toFloat();

    //alb单位mg/L  cre单位mg/dL  1mg/L = 100mg/dL
    //acr = alb / cre 单位为mg/g
    ui->ACRLineEdit->setText(QString::number(alb*100 / cre, 'f', 0));
}



