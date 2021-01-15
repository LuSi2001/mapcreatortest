#include "editorscene.h"
#include "itemfactory.h"
#include "wallitem.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QKeyEvent>

EditorScene::EditorScene(QObject *parent) :
    QGraphicsScene(parent)
{
    connect(this, &EditorScene::selectionChanged, this, &EditorScene::on_selection_changed);
}

void EditorScene::mirrorItemDiagonally(int state)
{
    if(selectedItems().size() == 1)
    {
        PinballItem* item = static_cast<PinballItem *>(selectedItems().at(0));
        if(state == 0)
        {
            selectedItems().at(0)->setScale(1);
            item->setDiagonallyFlipped(false);
            return;
        }
        selectedItems().at(0)->setScale(-1);
        item->setDiagonallyFlipped(true);
    }
}

void EditorScene::createItem(const QString &name)
{
    if(name == "ball" or name == "board")
    {
        emit sceneMousePressEvent();
        selectItem(name);
        return;
    }
    if(checkForItemLimit(name))
    {
        m_curItem = ItemFactory::inst().item(name);
        m_curItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        m_curItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        m_curItem->setOpacity(0.75);
        m_curItem->hide();
        addItem(m_curItem);
        m_gotItem = true;
        return;
    }
    emit sceneMousePressEvent();
}

void EditorScene::selectItem(const QString &name)
{
    int counter = 0;
    QListIterator<QGraphicsItem *> i(items());
    while(i.hasNext())
    {
        QString compName = static_cast<PinballItem *>(items().at(counter))->name();
        items().at(counter)->setSelected(false);
        if(compName == name)
        {
            items().at(counter)->setSelected(true);
        }
        i.next();
        counter++;
    }
}

void EditorScene::mapLoaded(const QList<PinballItem *> list)
{
    on_reset();
    std::map<QString, int>::iterator it;
    for(it = itemAmount.begin(); it != itemAmount.end(); it++)
    {
        itemAmount.erase(it);
    }
    for(auto item : items())
    {
        delete item;
    }
    for(auto item : list)
    {
        checkForItemLimit(item->name());
        if(item->name() != "wall")
        {
            item->setFlag(QGraphicsItem::ItemIsSelectable, true);
        }
        if(item->name() != "board" and item->name() != "ball" and item->name() != "wall")
        {
            item->setFlag(QGraphicsItem::ItemIsMovable, true);
            item->setZValue(item->zValue() + 3);
        }
        if(item->name() == "ball")
        {
            item->setZValue(item->zValue() + 1);
        }
        if(item->name() == "wall")
        {
            item->setZValue(item->zValue() + 2);
        }
        addItem(item);
    }
}

void EditorScene::changeSelectedItemsPos(int x, int y)
{
    int counter = 0;
    QListIterator<QGraphicsItem *> i(selectedItems());
    while(i.hasNext())
    {
        QString name = static_cast<PinballItem *>(selectedItems().at(counter))->name();
        if(name == "ball" or name == "board")
        {
            i.next();
            counter++;
            continue;
        }
        selectedItems().at(counter)->setPos(
                    selectedItems().at(counter)->x() + x,
                    selectedItems().at(counter)->y() + y
                    );
        counter++;
        i.next();
    }
}

bool EditorScene::checkForItemLimit(const QString &name)
{
    int limit;
    if(name == "flipper" or name.right(7) == "plunger")
    {
        limit = 1;
    }
    else
    {
        limit = 5;
    }
    std::map<QString, int>::iterator it;
    for(it = itemAmount.begin(); it != itemAmount.end(); it++)
    {
        if(it->first == name or (it->first.right(7) == "plunger" and name.right(7) == "plunger"))
        {
            if(it->second < limit)
            {
                it->second += 1;
                return true;
            }
            return false;
        }
    }
    itemAmount.insert({name, 1});
    return true;
}

// --------------------------------------GETTER--------------------------------------

const qreal& EditorScene::rotation() const
{
    return m_rotation;
}

const qreal& EditorScene::scale() const
{
    return m_scale;
}

// --------------------------------------SETTER--------------------------------------

void EditorScene::setMode(EditorMode mode)
{
    m_editorMode = mode;
}

// **************************************SLOTS***************************************

void EditorScene::on_selection_changed()
{
    if(selectedItems().size() == 0)
    {
        emit noItemSelected();
        return;
    }
    if(selectedItems().size() == 1)
    {
        emit itemSelected(selectedItems().at(0));
        return;
    }
    if(selectedItems().size() > 1)
    {
        emit noItemSelected();
        return;
    }
}

void EditorScene::on_reset()
{
    emit viewParamsChanged(1, -m_rotation, m_viewPos);
    m_rotation = 0;
    qreal fac;
    if(m_scale > 1)
    {
        fac = ZOOM_OUT_FAC;
    }
    else
    {
        fac = ZOOM_IN_FAC;
    }
    while(not(abs(m_scale - 1.0) <= 0.0001))
    {
        m_scale *= fac;
        emit viewParamsChanged(fac, m_rotation, m_viewPos);
    }
    m_zoom = 100.0;
}

// **************************************EVENTS**************************************

void EditorScene::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    emit sceneMousePressEvent();
    QGraphicsScene::mousePressEvent(e);
}

void EditorScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsScene::mouseMoveEvent(e);
    if(m_gotItem)
    {
        QGraphicsItem* item = items().at(items().lastIndexOf(m_curItem));
        item->show();
        item->setPos(e->scenePos());
    }
    m_mouseScreenPos = e->scenePos();
    QGraphicsScene::mouseMoveEvent(e);
}

void EditorScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    if(m_gotItem)
    {
        items().at(items().lastIndexOf(m_curItem))->setOpacity(1.0);
    }
    m_gotItem = false;
    QGraphicsScene::mouseReleaseEvent(e);
}

void EditorScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if(selectedItems().size() > 1)
    {
        return;
    }
    if(selectedItems().size() == 1)
    {
        QString name = static_cast<PinballItem *>(selectedItems().at(0))->name();
        if(name == "board" or name == "ball")
        {
            return;
        }
        qreal value;
        if(event->delta() < 0)
        {
            if(event->modifiers() == Qt::ShiftModifier)
            {
                value = 1.0;
            }
            else
            {
                value = 10.0;
            }
        }
        else
        {
            if(event->modifiers() == Qt::ShiftModifier)
            {
                value = -1.0;
            }
            else
            {
                value = -10.0;
            }
        }
        selectedItems().at(0)->setRotation(selectedItems().at(0)->rotation() + value);
        emit itemSelected(selectedItems().at(0));
        return;
    }
    if(event->modifiers() == Qt::ShiftModifier)
    {
        m_rotation += event->delta()/120;
        if(m_rotation > 360)
        {
            m_rotation -= 360;
        }
        if(m_rotation < -360)
        {
            m_rotation += 360;
        }
        emit viewParamsChanged(1, event->delta()/120, m_viewPos);
        return;
    }
    if((m_zoom + event->delta()/120) < 95 or (m_zoom + event->delta()/120) > 105) return;
    m_zoom += event->delta()/120;
    qreal fac;
    if(event->delta() < 0)
    {
        fac = ZOOM_OUT_FAC;
    }
    else
    {
        fac = ZOOM_IN_FAC;
    }
    m_scale *= fac;
    m_viewPos = ((m_viewPos - event->scenePos() * fac) + event->scenePos());
    emit viewParamsChanged(fac, 0, m_viewPos);
    QGraphicsScene::wheelEvent(event);
}

void EditorScene::keyPressEvent(QKeyEvent *e)
{
    if(selectedItems().size() > 0)
    {
        if(selectedItems().size() == 1 and e->modifiers() == Qt::ControlModifier)
        {
            QString name = static_cast<PinballItem *>(selectedItems().at(0))->name();
            if(name == "board" or name == "ball")
            {
                return;
            }
            if(e->key() == Qt::Key_R)
            {
                selectedItems().at(0)->setRotation(selectedItems().at(0)->rotation() + 18);
                emit itemSelected(selectedItems().at(0));
            }
        }
        if(e->key() == Qt::Key_Left)
        {
            changeSelectedItemsPos(-1, 0);
            emit itemSelected(selectedItems().at(0));
            return;
        }
        if(e->key() == Qt::Key_Right)
        {
            changeSelectedItemsPos(1, 0);
            emit itemSelected(selectedItems().at(0));
            return;
        }
        if(e->key() == Qt::Key_Up)
        {
            changeSelectedItemsPos(0, -1);
            emit itemSelected(selectedItems().at(0));
            return;
        }
        if(e->key() == Qt::Key_Down)
        {
            changeSelectedItemsPos(0, 1);
            emit itemSelected(selectedItems().at(0));
            return;
        }
        return;
    }
    if(e->modifiers() == Qt::ControlModifier and selectedItems().size() == 0)
    {
        if(e->key() == Qt::Key_R)
        {
            m_rotation += 18;
            if(m_rotation > 360)
            {
                m_rotation -= 360;
            }
            emit viewParamsChanged(1, 18, m_viewPos);
        }
    }
    QGraphicsScene::keyPressEvent(e);
}
