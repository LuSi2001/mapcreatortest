#include "pinballitem.h"

#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

PinballItem::PinballItem(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    setAcceptHoverEvents(true);
}

//-----------------------------------GETTER--------------------------------------

bool PinballItem::isHovered()
{
    return m_hovered;
}

qreal PinballItem::width() const
{
    return boundingRect().size().width();
}

qreal PinballItem::height() const
{
    return boundingRect().size().height();
}

QSizeF PinballItem::size() const
{
    return boundingRect().size();
}

Qt::CheckState PinballItem::diagonallyFlipped() const
{
    if(m_diagonallyFlipped)
    {
        return Qt::CheckState::Checked;
    }
    return Qt::CheckState::Unchecked;
}

//-----------------------------------SETTER--------------------------------------

void PinballItem::setColorMode(ItemColorMode mode)
{
    m_textureMode = mode;
}

void PinballItem::setDiagonallyFlipped(bool flipped)
{
    m_diagonallyFlipped = flipped;
}

//***********************************EVENTS**************************************

void PinballItem::hoverEnterEvent(QGraphicsSceneHoverEvent* e)
{
    m_hovered = true;
    update();
    QGraphicsItem::hoverEnterEvent(e);
}

void PinballItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* e)
{
    m_hovered = false;
    update();
    QGraphicsItem::hoverLeaveEvent(e);
}
