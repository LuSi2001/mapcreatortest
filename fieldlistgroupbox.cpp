#include "fieldlistgroupbox.h"
#include "ui_fieldlistgroupbox.h"
#include "stringeditor.h"

FieldListGroupBox::FieldListGroupBox(QWidget *parent) :
    ItemBox(parent),
    ui(new Ui::FieldListGroupBox)
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
    connect(ui->ballcounterfieldBtn, &QPushButton::clicked, [this]()
    {
        QString name = StringEditor::truncatedName(ui->ballcounterfieldBtn);
        emit createItem(name);
    });
    connect(ui->pointmultiplierfieldBtn, &QPushButton::clicked, [this]()
    {
        QString name = StringEditor::truncatedName(ui->pointmultiplierfieldBtn);
        emit createItem(name);
    });
    connect(ui->scorefieldBtn, &QPushButton::clicked, [this]()
    {
        QString name = StringEditor::truncatedName(ui->scorefieldBtn);
        emit createItem(name);
    });
    connect(ui->timerfieldBtn, &QPushButton::clicked, [this]()
    {
        QString name = StringEditor::truncatedName(ui->timerfieldBtn);
        emit createItem(name);
    });
}

FieldListGroupBox::~FieldListGroupBox()
{
    delete ui;
}
