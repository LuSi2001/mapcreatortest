#ifndef ZONELISTGROUPBOX_H
#define ZONELISTGROUPBOX_H

#include "itembox.h"

namespace Ui {
class ZoneListGroupBox;
}

class ZoneListGroupBox : public ItemBox
{
    Q_OBJECT

public:
    explicit ZoneListGroupBox(QWidget *parent = nullptr);
    ~ZoneListGroupBox();

private:
    Ui::ZoneListGroupBox *ui;

};

#endif // ZONELISTGROUPBOX_H
