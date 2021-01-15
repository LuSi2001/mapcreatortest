#include "zonelistgroupbox.h"
#include "ui_zonelistgroupbox.h"
#include "stringeditor.h"

ZoneListGroupBox::ZoneListGroupBox(QWidget *parent) :
    ItemBox(parent),
    ui(new Ui::ZoneListGroupBox)
{
    ui->setupUi(this);

    setFixedWidth(106);

    for(QAbstractButton* btn : ui->buttonGroup->buttons())
    {
        btn->setFixedSize(100, 100);
    }

    connect(ui->prevBtn, &QPushButton::clicked, [this]()
    {
        emit changeItemPage(MAIN_PAGE);
    });
    connect(ui->endzoneBtn, &QPushButton::clicked, [this]()
    {
        QString name = StringEditor::truncatedName(ui->endzoneBtn);
        emit createItem(name);
    });
}

ZoneListGroupBox::~ZoneListGroupBox()
{
    delete ui;
}
