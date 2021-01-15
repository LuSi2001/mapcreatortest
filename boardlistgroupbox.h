#ifndef BOARDLISTGROUPBOX_H
#define BOARDLISTGROUPBOX_H

#include "itembox.h"

namespace Ui {
class BoardListGroupBox;
}

class BoardListGroupBox : public ItemBox
{
    Q_OBJECT

public:
    explicit BoardListGroupBox(QWidget *parent = nullptr);
    ~BoardListGroupBox();

private:
    Ui::BoardListGroupBox *ui;
};

#endif // BOARDLISTGROUPBOX_H
