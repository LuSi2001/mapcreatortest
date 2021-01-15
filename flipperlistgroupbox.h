#ifndef FLIPPERLISTGROUPBOX_H
#define FLIPPERLISTGROUPBOX_H

#include "itembox.h"

namespace Ui {
class FlipperListGroupBox;
}

class FlipperListGroupBox : public ItemBox
{
    Q_OBJECT

public:
    explicit FlipperListGroupBox(QWidget *parent = nullptr);
    ~FlipperListGroupBox();

private:
    Ui::FlipperListGroupBox *ui;

};

#endif // FLIPPERLISTGROUPBOX_H
