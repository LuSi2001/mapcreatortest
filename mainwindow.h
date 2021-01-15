#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "editorscene.h"
#include "binaryreader.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void updateMatrix(const qreal &scale, const qreal &rotation, const QPointF &viewPos);

private:
    Ui::MainWindow *ui;
    EditorScene *m_editorscene;
    bool m_saved;

    BinaryReader m_binReader;

    QString m_fileName;

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;

public slots:
    void on_save_clicked();
    void on_load_clicked();
    void on_saveAs_clicked();
    void on_scenemousepress_event();

signals:
    void itemButtonPressed();
    void itemPlaced();
    void itemRejected();
};

#endif // MAINWINDOW_H
