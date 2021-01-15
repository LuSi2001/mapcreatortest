#include "view.h"
#include "constants.h"

#include <QDebug>
#include <QImage>

View::View(QWidget *parent) :
    QGraphicsView (parent)
{
    setDragMode(QGraphicsView::RubberBandDrag);
}

const QPixmap View::snapshot(qreal curScale)
{

    qreal oldScale = curScale;

    qreal fac;
    if(curScale > 1.25)
    {
        fac = ZOOM_OUT_FAC;
    }
    else
    {
        fac = ZOOM_IN_FAC;
    }
    while(not(abs(curScale - 1.25) <= 0.0001))
    {
        curScale *= fac;
        this->scale(fac, fac);
    }

    const QRectF &r = QRectF(0, 0, this->width(), this->height());
    const QPixmap &pixi = this->grab(r.toRect());
    // pixi.save("/tmp/pixi.png");

    if(oldScale > 1.25)
    {
        fac = ZOOM_IN_FAC;
    }
    else
    {
        fac = ZOOM_OUT_FAC;
    }
    while(not(abs(curScale - oldScale) <= 0.0001))
    {
        curScale *= fac;
        this->scale(fac, fac);
    }

    return pixi;
}

void View::scrollContentsBy(int, int){}
