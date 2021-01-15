#ifndef ITEMLISTGROUPBOX_H
#define ITEMLISTGROUPBOX_H

#include "itembox.h"

namespace Ui {
class ItemListGroupBox;
}

class ItemListGroupBox : public ItemBox
{
    Q_OBJECT

public:
    explicit ItemListGroupBox(QWidget *parent = nullptr);
    ~ItemListGroupBox();

private:
    Ui::ItemListGroupBox *ui;

};

#endif // ITEMLISTGROUPBOX_H
