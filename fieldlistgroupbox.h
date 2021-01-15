#ifndef FIELDLISTGROUPBOX_H
#define FIELDLISTGROUPBOX_H

#include "itembox.h"

namespace Ui {
class FieldListGroupBox;
}

class FieldListGroupBox : public ItemBox
{
    Q_OBJECT

public:
    explicit FieldListGroupBox(QWidget *parent = nullptr);
    ~FieldListGroupBox();

private:
    Ui::FieldListGroupBox *ui;

};

#endif // FIELDLISTGROUPBOX_H
