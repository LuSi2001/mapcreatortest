#ifndef ITEMSGROUPBOX_H
#define ITEMSGROUPBOX_H

#include "itembox.h"

namespace Ui {
class ItemsGroupBox;
}

class ItemsGroupBox : public ItemBox
{
    Q_OBJECT

public:
    explicit ItemsGroupBox(QWidget *parent = nullptr);
    ~ItemsGroupBox();

private:
    Ui::ItemsGroupBox *ui;

};

#endif // ITEMSGROUPBOX_H
