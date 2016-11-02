#include "mlineedit.h"
#include <QCompleter>
#include <QStringListModel>
#include <QFile>
#include <QDebug>
#include <QApplication>
#include <QTextCodec>

mlineEdit::mlineEdit(QWidget *parent):
    QLineEdit(parent)
{
}

void mlineEdit::setCompleterFileName(QString fileName)
{
    QTextCodec *codec =QTextCodec::codecForName("GBK");

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QStringList strList;
    while(!file.atEnd())
    {
        strList << " " + codec->toUnicode(file.readLine()).trimmed();
    }

    QStringListModel *model = new QStringListModel(strList, this);
    QCompleter *completer = new QCompleter(this);
    completer->setModel(model);
    this->setCompleter(completer);
}
