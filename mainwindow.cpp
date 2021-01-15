#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "itembox.h"

#include <QDebug>
#include <QKeyEvent>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setFixedWidth(106);

    const QIcon CLOSE_BUTTON_STYLE = STYLE.standardIcon(QStyle::SP_TitleBarCloseButton);
    const QIcon RESET_BUTTON_STYLE = STYLE.standardIcon(QStyle::SP_DialogResetButton);
    const QIcon PLAY_BUTTON_STYLE = STYLE.standardIcon(QStyle::SP_MediaPlay);
    const QIcon SAVE_BUTTON_STYLE = STYLE.standardIcon(QStyle::SP_DialogSaveButton);
    const QIcon SAVE_AS_BUTTON_STYLE = STYLE.standardIcon(QStyle::SP_DirOpenIcon);
    const QIcon LOAD_BUTTON_STYLE = STYLE.standardIcon(QStyle::SP_BrowserReload);

    ui->closeBtn->setIcon(CLOSE_BUTTON_STYLE);
    ui->saveBtn->setIcon(SAVE_BUTTON_STYLE);
    ui->saveAsBtn->setIcon(SAVE_AS_BUTTON_STYLE);
    ui->resetBtn->setIcon(RESET_BUTTON_STYLE);
    ui->testPlayBtn->setIcon(PLAY_BUTTON_STYLE);
    ui->loadBtn->setIcon(LOAD_BUTTON_STYLE);

    setWindowTitle("BattlePinball 3000");

    m_editorscene = new EditorScene(ui->editorSceneView);

    ui->editorSceneView->setScene(m_editorscene);
    ui->editorSceneView->setMouseTracking(true);

    m_editorscene->setSceneRect(m_editorscene->sceneRect());

    connect(ui->saveBtn, &QPushButton::clicked, this, &MainWindow::on_save_clicked);
    connect(ui->saveAsBtn, &QPushButton::clicked, this, &MainWindow::on_saveAs_clicked);
    connect(ui->loadBtn, &QPushButton::clicked, this, &MainWindow::on_load_clicked);
    connect(ui->resetBtn, &QPushButton::clicked, [this]()
    {
        m_editorscene->on_reset();
        ui->rotationEdit->setText("0");
    });
    connect(m_editorscene, &EditorScene::viewParamsChanged, this, &MainWindow::updateMatrix);
    connect(m_editorscene, &EditorScene::sceneMousePressEvent, this, &MainWindow::on_scenemousepress_event);
    connect(m_editorscene, &EditorScene::noItemSelected, [this]()
    {
        //ui->propertyBox->on_noItemSelected();
    });
    connect(m_editorscene, &EditorScene::itemSelected, [this](const QGraphicsItem* item)
    {
        //ui->propertyBox->on_itemSelected(item);
    });
    QList<QGroupBox*> boxList = {ui->mainBox, ui->boardBox, ui->fieldBox,
                                 ui->itemBox, ui->flipperBox, ui->plungerBox,
                                 ui->zoneBox};
    for(QGroupBox* box : boxList)
    {
        ItemBox* cBox = static_cast<ItemBox*>(box);
        connect(cBox, &ItemBox::changeItemPage, [this](ItemPage page)
        {
            ui->stackedWidget->setCurrentIndex(page);
        });
        connect(cBox, &ItemBox::createItem, [this](const QString& name)
        {
            qDebug() << name;
        });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    QMainWindow::mousePressEvent(e);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    QMainWindow::keyPressEvent(e);
}

void MainWindow::on_save_clicked()
{
    if(not m_saved)
    {
        on_saveAs_clicked();
        return;
    }
    QFile file(m_fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "Unable to open file.";
        return;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_9);
    QPixmap pixi = ui->editorSceneView->snapshot(m_editorscene->scale());
    out << pixi;
    for(const QGraphicsItem* item : ui->editorSceneView->scene()->items())
    {
        static_cast<const PinballItem *>(item)->write(out);
    }
    file.close();
}

void MainWindow::on_saveAs_clicked()
{
    m_fileName = QFileDialog::getSaveFileName(this,
                 tr("Save Scene"), "", tr("Binary File (*.bin);;AllFiles(*)"));
    if(m_fileName.isEmpty())
    {
        return;
    }
    QFile file(m_fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Unable to open file.";
        return;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_9);
    QPixmap pixi = ui->editorSceneView->snapshot(m_editorscene->scale());
    out << pixi;
    for(const QGraphicsItem* item : ui->editorSceneView->scene()->items())
    {
        static_cast<const PinballItem *>(item)->write(out);
    }
    file.close();
    m_saved = true;
}

void MainWindow::on_load_clicked()
{
    m_fileName = "";
    m_fileName = QFileDialog::getOpenFileName(this,
                 tr("Load Scene"), "", tr("Binary File (*.bin);;AllFiles(*)"));
    if(m_fileName.isEmpty()) return;
    m_binReader.setFilename(m_fileName);
    m_editorscene->mapLoaded(m_binReader.readAll());
    m_binReader.close();
}

void MainWindow::updateMatrix(const qreal &scale, const qreal &rotation, const QPointF &viewPos)
{
//    ui->editorSceneView->resetTransform();
//    ui->editorSceneView->translate(viewPos.x(), viewPos.y());
    ui->editorSceneView->scale(scale, scale);
    ui->editorSceneView->rotate(rotation);

    ui->rotationEdit->setText(QString::number(m_editorscene->rotation()) + "°");
    ui->zoomEdit->setText(QString::number(100 * m_editorscene->scale()) + "%");
}

void MainWindow::on_scenemousepress_event()
{
    this->setCursor(Qt::ArrowCursor);
}
