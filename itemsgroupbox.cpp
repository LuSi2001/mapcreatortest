#include "itemsgroupbox.h"
#include "ui_itemsgroupbox.h"
#include "stringeditor.h"

ItemsGroupBox::ItemsGroupBox(QWidget *parent) :
    ItemBox(parent),
    ui(new Ui::ItemsGroupBox)
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
    connect(ui->ballBtn, &QPushButton::clicked, [this]()
    {
        QString name = StringEditor::truncatedName(ui->ballBtn);
        emit createItem(name);
    });
    connect(ui->coinBtn, &QPushButton::clicked, [this]()
    {
        QString name = StringEditor::truncatedName(ui->coinBtn);
        emit createItem(name);
    });
    connect(ui->bumperBtn, &QPushButton::clicked, [this]()
    {
        QString name = StringEditor::truncatedName(ui->bumperBtn);
        emit createItem(name);
    });
    connect(ui->flipperBtn, &QPushButton::clicked, [this]()
    {
        emit changeItemPage(FLIPPER_PAGE);
    });
    connect(ui->plungerBtn, &QPushButton::clicked, [this]()
    {
        emit changeItemPage(PLUNGER_PAGE);
    });
    connect(ui->slingshotBtn, &QPushButton::clicked, [this]()
    {
        QString name = StringEditor::truncatedName(ui->slingshotBtn);
        emit createItem(name);
    });
}

ItemsGroupBox::~ItemsGroupBox()
{
    delete ui;
}
