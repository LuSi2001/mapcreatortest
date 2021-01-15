#ifndef PLUNGERLISTGROUPBOX_H
#define PLUNGERLISTGROUPBOX_H

#include "itembox.h"

namespace Ui {
class PlungerListGroupBox;
}

class PlungerListGroupBox : public ItemBox
{
    Q_OBJECT

public:
    explicit PlungerListGroupBox(QWidget *parent = nullptr);
    ~PlungerListGroupBox();

private:
    Ui::PlungerListGroupBox *ui;

};

#endif // PLUNGERLISTGROUPBOX_H
