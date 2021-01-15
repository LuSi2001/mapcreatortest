#ifndef PINBALLITEM_H
#define PINBALLITEM_H

#include "constants.h"
#include "vector.h"
#include "utils.h"

#include <QGraphicsItem>

class ReaderProxy;
class BinaryReader;

using Vec3 = mats::Vector3<double>;

class PinballItem : public QGraphicsItem
{
public:
    PinballItem(QGraphicsItem *parent = nullptr);
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *, QWidget *) override = 0;
    void setDiagonallyFlipped(bool flipped);
    void setColorMode(ItemColorMode mode);
    Qt::CheckState diagonallyFlipped() const;
    virtual void readFromXML(const ReaderProxy& reader) = 0;
    virtual void readFromBinary(const ReaderProxy& reader) = 0;

    bool isHovered();
    qreal width() const;
    qreal height() const;
    QSizeF size() const;
    virtual CollisionObject objectType() const = 0;
    virtual QRectF boundingRect() const override = 0;
    virtual QPainterPath shape() const override = 0;
    virtual const QString name() const = 0;
    virtual PinballItem* clone() const = 0;
    virtual PinballItem* cloneType() const = 0;
    virtual void handleCollision(Vec3& m_velocity, Vec3 &m_accl, QTime &time) = 0;

    virtual QDataStream &operator<<(QDataStream &str) const
    {
        return str << name();
    }

    virtual void write(QDataStream &str) const
    {
        str << name() << scenePos() << rotation();
    }

    virtual void read(QDataStream &str)
    {
        QPointF point;
        qreal rotation;

        str >> point >> rotation;

        setPos(point);
        setRotation(rotation);
    }

private:
    bool m_hovered = false;
    bool m_diagonallyFlipped = false;
    ItemColorMode m_textureMode = COLOR;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* e) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* e) override;
};

#endif // PINBALLITEM_H
