#ifndef PRINTFORMS_H
#define PRINTFORMS_H

#include <QWidget>
#include "define.h"

class QPrinter;

namespace Ui {
class printForms;
}

class printForms : public QWidget
{
    Q_OBJECT

public:
    explicit printForms(QWidget *parent = 0);
    ~printForms();

    //打印预览
    void printView();

    void setForms(const urinalysisInfo &info);
private:

private slots:
    void printPreviewSlot(QPrinter *printerPixmap);

private:
    Ui::printForms *ui;
};

#endif // PRINTFORMS_H
