#include "timerfielditem.h"
#include <QPainter>
#include "timeconverter.h"

//template <typename T> struct Prefix
//{
//};

//template <> struct Prefix<int>
//{
//    static const char prefix = 'i';
//};

//template <> struct Prefix<float>
//{
//    static const char prefix = 'f';
//};

//struct A
//{
//    void huhu() const {std::cout << "huhu" << std::endl;}

//    template<typename T> void huhuT(const T &t) const {std::cout << Prefix<T>::prefix << t << std::endl;}
//};

TimerFieldItem::TimerFieldItem(int h, int m, int s, int ms, FieldItem* parent) :
    FieldItem(parent),
    m_stopped(false)
{
    m_timer = new QTime(h, m, s, ms);
    m_timerStr = m_timer->toString("hh:mm:ss:zzz");
    m_reference = 0;
}

void TimerFieldItem::start()
{
    m_timer->start();
}

void TimerFieldItem::stop()
{
    m_reference += m_timer->elapsed();
    m_stopped = true;
}

void TimerFieldItem::resume()
{
    m_timer->start();
    m_stopped = false;
}

void TimerFieldItem::updateTxt()
{
    if(not m_stopped)
    {
        int ms = m_reference + m_timer->elapsed();
        int s = tconv::TimeConverter<int>(ms).msecsToSecs();
        int m = tconv::TimeConverter<int>(ms).msecsToMin();
        int h = tconv::TimeConverter<int>(ms).msecsToHour();
        ms = tconv::TimeConverter<int>(ms).msecsToSecsRest();
        s = tconv::TimeConverter<int>(s).secsToMinRest();
        m = tconv::TimeConverter<int>(m).minToHourRest();
        QString preH, preM, preS, preMS = "";
        if(h < 10)
        {
            preH = "0";
        }
        if(m < 10)
        {
            preM = "0";
        }
        if(s < 10)
        {
            preS = "0";
        }
        if(ms < 10)
        {
            preMS = "00";
        }
        if(ms < 100 and ms >= 10)
        {
            preMS = "0";
        }
        m_timerStr = preH + QString::number(h) + ":" + preM + QString::number(m) + ":" +
                     preS + QString::number(s) + ":" + preMS + QString::number(ms);
        update(boundingRect());
    }
}

QRectF TimerFieldItem::boundingRect() const
{
    return {-50, -20, 100, 40};
}

void TimerFieldItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::SolidLine);
    QPainterPath path;
    path.addRect(boundingRect());
    path.addText(QPointF(-38, 5), QFont(), m_timerStr);
    painter->drawPath(path);
}

QPainterPath TimerFieldItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    path.addText(QPointF(0, 0), QFont(), m_timerStr);
    return path;
}

const QString TimerFieldItem::name() const
{
    return "timerField";
}

void TimerFieldItem::handleCollision(Vec3 &m_velocity, Vec3 &m_accl, QTime &time)
{

}
