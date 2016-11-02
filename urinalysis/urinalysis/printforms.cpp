#include "printforms.h"
#include "ui_printforms.h"
#include <QPainter>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QApplication>
#include <QDesktopWidget>

printForms::printForms(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::printForms)
{
    ui->setupUi(this);
}

printForms::~printForms()
{
    delete ui;
}

void printForms::printView()
{
    QPrinter printer(QPrinter::HighResolution);
    //自定义纸张大小
    printer.setPageSize(QPrinter::A5);
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::NativeFormat);
    printer.setPaperSize(QSizeF(this->width(), this->height()), QPrinter::Point);
    QPrintPreviewDialog preview(&printer, this);\
    preview.setMinimumSize(QApplication::desktop()->size());
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreviewSlot(QPrinter*)));
    preview.exec();
}

void printForms::setForms(const urinalysisInfo &info)
{
    ui->nameLabel->setText(info.name);
    ui->ageLabel->setText(QString::number(info.age));
    ui->patientLabel->setText(info.patientID);
    ui->sampleTypeLabel->setText(info.sampleType);
    ui->sampleID->setText(QString::number(info.sampleID));
    ui->sexLabel->setText(info.sex);
    ui->bedIdLabel->setText(QString::number(info.bedID));
    ui->officeLable->setText(info.administrativeOffice);
    ui->senderDoctorLabel->setText(info.senderDoctor);
    ui->sampleDateLabel->setText(info.sampleDate);
    ui->albLabel->setText(QString::number(info.ALB));
    ui->creLabel->setText(QString::number(info.CRE));
    ui->acrLabel->setText(QString::number(info.ALB*100 / info.CRE, 'f', 4));
    ui->detectinDateLabel->setText(info.detectionDate);
    ui->reportDate->setText(info.reportDate);
    ui->prooferLabel->setText(info.proofer);
    ui->auditorLabel->setText(info.auditor);
    ui->remarksLabel->setText(info.remarks);
}

void printForms::printPreviewSlot(QPrinter *printerPixmap)
{
    //获取界面的图片
    printerPixmap->setPageSize(QPrinter::A4);
//    printerPixmap->setOrientation(QPrinter::Portrait);
    this->resize(1000, 700);
    QPixmap pixmap = QWidget::grab(this->rect());

    QPainter painterPixmap(this);
    painterPixmap.begin(printerPixmap);
    QRect rect = painterPixmap.viewport();
    int x = rect.width() / pixmap.width();
    int y = rect.height() / 2 / pixmap.height();
    painterPixmap.scale(x, y);
    painterPixmap.drawPixmap(100, 20, pixmap);
    painterPixmap.end();
}
