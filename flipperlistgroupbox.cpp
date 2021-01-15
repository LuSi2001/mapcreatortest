#include "flipperlistgroupbox.h"
#include "ui_flipperlistgroupbox.h"
#include "stringeditor.h"

FlipperListGroupBox::FlipperListGroupBox(QWidget *parent) :
    ItemBox(parent),
    ui(new Ui::FlipperListGroupBox)
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
    connect(ui->flipperleftBtn, &QPushButton::clicked, [this]()
    {
        QString name = StringEditor::truncatedName(ui->flipperleftBtn);
        emit createItem(name);
    });
    connect(ui->flipperRightBtn, &QPushButton::clicked, [this]()
    {
        QString name = StringEditor::truncatedName(ui->flipperRightBtn);
        emit createItem(name);
    });
}

FlipperListGroupBox::~FlipperListGroupBox()
{
    delete ui;
}
