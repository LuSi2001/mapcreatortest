#include "boardlistgroupbox.h"
#include "ui_boardlistgroupbox.h"

BoardListGroupBox::BoardListGroupBox(QWidget *parent) :
    ItemBox(parent),
    ui(new Ui::BoardListGroupBox)
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
    connect(ui->type1Btn, &QPushButton::clicked, [this]()
    {

    });
}

BoardListGroupBox::~BoardListGroupBox()
{
    delete ui;
}
