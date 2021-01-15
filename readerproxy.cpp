#include "readerproxy.h"

#include <QDomElement>
#include <QDebug>

ReaderProxy::ReaderProxy()
{
    m_xmlReader = new XMLReader();
    m_binReader = new BinaryReader();
}

void ReaderProxy::setCurPinballItem(const QString &name) const
{
    m_xmlReader->setCurPinballItem(name);
}

bool ReaderProxy::readXML(const QString &name, int &value) const
{
    if(m_xmlReader->find(name))
    {
        QDomElement e = m_xmlReader->itemArgumentElement(name);
        if(not e.text().isEmpty())
        {
            value = e.text().toInt();
            return true;
        }
    }
    return false;
}

bool ReaderProxy::readXML(const QString &name, qreal &value) const
{
    if(m_xmlReader->find(name))
    {
        QDomElement e = m_xmlReader->itemArgumentElement(name);
        if(not e.text().isEmpty())
        {
            value = e.text().toDouble();
            return true;
        }
    }
    return false;
}

bool ReaderProxy::readXML(const QString &name, QColor &c) const
{
    if(m_xmlReader->find(name))
    {
        QDomElement e = m_xmlReader->itemArgumentElement(name);
        if(not e.text().isEmpty())
        {
            c = QColor(e.text());
            return true;
        }
    }
    return false;
}

bool ReaderProxy::readXML(const QString &name, QLinearGradient &lg) const
{
    if(m_xmlReader->find(name))
    {
        QDomElement e = m_xmlReader->itemArgumentElement(name);
        if(not e.text().isEmpty())
        {
            lg = QLinearGradient();
            return true;
        }
    }
    return false;
}

bool ReaderProxy::readXML(const QString &name, ItemColorMode &mode) const
{
    if(m_xmlReader->find(name))
    {
        QDomElement e = m_xmlReader->itemArgumentElement(name);
        if(not e.text().isEmpty())
        {
            mode = COLOR;
            return true;
        }
    }
    return false;
}

bool ReaderProxy::readXML(const QString &name, QString &link) const
{
    if(m_xmlReader->find(name))
    {
        QDomElement e = m_xmlReader->itemArgumentElement(name);
        if(not e.text().isEmpty())
        {
            link = e.text();
            return true;
        }
    }
    return false;
}

bool ReaderProxy::readBinary(const QString &name, int &value) const
{
    return false;
}

bool ReaderProxy::readBinary(const QString &name, qreal &value) const
{
    return false;
}

bool ReaderProxy::readBinary(const QString &name, QColor &c) const
{
    return false;
}

bool ReaderProxy::readBinary(const QString &name, QLinearGradient &lg) const
{
    return false;
}

bool ReaderProxy::readBinary(const QString &name, ItemColorMode &mode) const
{
    return false;
}

bool ReaderProxy::readBinary(const QString &name, QString &link) const
{
    return false;
}
