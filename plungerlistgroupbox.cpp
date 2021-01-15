#include "plungerlistgroupbox.h"
#include "ui_plungerlistgroupbox.h"
#include "stringeditor.h"

PlungerListGroupBox::PlungerListGroupBox(QWidget *parent) :
    ItemBox(parent),
    ui(new Ui::PlungerListGroupBox)
{
    ui->setupUi(this);

    setFixedWidth(106);

    for(QAbstractButton* btn : ui->buttonGroup->buttons())
    {
        btn->setFixedSize(100, 100);
    }

    connect(ui->prevBtn, &QPushButton::clicked, [this]()
    {
        emit changeItemPage(ITEM_PAGE);
    });
    connect(ui->manualplunger, &QPushButton::clicked, [this]()
    {
        QString name = StringEditor::truncatedName(ui->manualplunger);
        emit createItem(name);
    });
    connect(ui->autoplungerBtn, &QPushButton::clicked, [this]()
    {
        QString name = StringEditor::truncatedName(ui->autoplungerBtn);
        emit createItem(name);
    });
}

PlungerListGroupBox::~PlungerListGroupBox()
{
    delete ui;
}
