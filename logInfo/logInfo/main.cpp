#include "widget.h"
#include <QApplication>
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>
#include <QTextStream>
#include <QDateTime>
#include <QFile>

#define LOGFILEMAX 10000


void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;
    case QtWarningMsg:
        text = QString("Warning:");
        break;
    case QtCriticalMsg:
        text = QString("Critical:");
        break;
    case QtFatalMsg:
        text = QString("Fatal:");
    }

    QString message = QString("%1 File:(%2) Line:(%3) %4 %5")
            .arg(text)
            .arg(QString(context.file))
            .arg(context.line)
            .arg(msg)
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));

    QFile file(QApplication::applicationDirPath()+ "/log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //注册MessageHandler
    qInstallMessageHandler(outputMessage);

    //打印日志到文件中
    qDebug("哈克多发路段发生地方");
    qWarning("This is a warning message");
    qCritical("This is a critical message");
    Widget w;
    w.show();

    return a.exec();
}
