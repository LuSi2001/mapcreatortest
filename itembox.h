#ifndef ITEMBOX_H
#define ITEMBOX_H

#include "constants.h"

#include <QGroupBox>

class ItemBox : public QGroupBox
{
    Q_OBJECT
public:
    ItemBox(QWidget *parent = nullptr);
    ~ItemBox();

signals:
    void changeItemPage(ItemPage page);
    void createItem(const QString& name);
};

#endif // ITEMBOX_H
