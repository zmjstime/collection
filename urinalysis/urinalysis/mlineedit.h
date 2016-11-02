#ifndef MLINEEDIT_H
#define MLINEEDIT_H
#include "QLineEdit"

class mlineEdit: public QLineEdit
{
    Q_OBJECT
public:
    mlineEdit(QWidget* parent);

    void setCompleterFileName(QString fileName);
};

#endif // MLINEEDIT_H
