#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include "constants.h"
#include "pinballitem.h"

#include <map>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class EditorScene : public QGraphicsScene
{
    Q_OBJECT
public:
    EditorScene(QObject *parent = nullptr);
    void createItem(const QString& name);
    void mapLoaded(const QList<PinballItem *> list);
    const qreal& rotation() const;
    const qreal& scale() const;
    void setMode(EditorMode mode);
    void mirrorItemDiagonally(int state);
    void selectItem(const QString& name);

private:
    void changeSelectedItemsPos(int x, int y);
    bool checkForItemLimit(const QString& name);
    bool m_dragged = false;
    bool m_gotItem = false;
    EditorMode m_editorMode;
    qreal m_zoom = 100.0;
    qreal m_scale = 1.0;
    qreal m_rotation = 0.0;
    QPointF m_startpos;
    QPointF m_viewPos;
    QPointF m_mouseScreenPos;
    QRectF m_extendedBoundingRect;
    QGraphicsRectItem   m_cursorRect;
    QGraphicsItem* m_curItem;
    std::map<QString, int> itemAmount;

protected:
    void wheelEvent(QGraphicsSceneWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *e) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * e) override;

public slots:
    void on_selection_changed();
    void on_reset();

signals:
    void viewParamsChanged(const qreal &scale, const qreal &rotation, const QPointF &viewPos);
    void sceneMousePressEvent();
    void itemSelected(const QGraphicsItem* item);
    void noItemSelected();
};

#endif // EDITORSCENE_H
