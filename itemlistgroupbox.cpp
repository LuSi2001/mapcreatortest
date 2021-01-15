#include "itemlistgroupbox.h"
#include "ui_itemlistgroupbox.h"

#include <QDebug>

ItemListGroupBox::ItemListGroupBox(QWidget *parent) :
    ItemBox(parent),
    ui(new Ui::ItemListGroupBox)
{
    ui->setupUi(this);

    setFixedWidth(106);

    for(QAbstractButton* btn : ui->buttonGroup->buttons())
    {
        btn->setFixedSize(100, 100);
    }

    connect(ui->boardsBtn, &QPushButton::clicked, [this]()
    {
        emit changeItemPage(BOARD_PAGE);
    });
    connect(ui->itemsBtn, &QPushButton::clicked, [this]()
    {
        emit changeItemPage(ITEM_PAGE);
    });
    connect(ui->fieldsBtn, &QPushButton::clicked, [this]()
    {
        emit changeItemPage(FIELD_PAGE);
    });
    connect(ui->zonesBtn, &QPushButton::clicked, [this]()
    {
        emit changeItemPage(ZONE_PAGE);
    });
}

ItemListGroupBox::~ItemListGroupBox()
{
    delete ui;
}
