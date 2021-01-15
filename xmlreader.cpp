#include "xmlreader.h"

#include <QDomDocument>
#include <iostream>
#include <QDebug>

//Function for searching through elements under one specific element

XMLReader::XMLReader() : m_file("/home/azubi_cgf/Luca/scenetest/item_config.xml")
{
    init();
}

XMLReader::XMLReader(const QString fileName) : m_file(fileName)
{
    init();
}

//! Tries to open the file and to set the content of the QDomDocument
void XMLReader::init()
{
    if(not m_file.open(QIODevice::ReadOnly))
    {
        return;
    }
    if(not m_doc.setContent(&m_file))
    {
        m_file.close();
        return;
    }
    m_file.close();
    m_rootElement = m_doc.documentElement();
}

//-----------------------------------GETTER-----------------------------------------

bool XMLReader::find(const QString& name)
{
    QDomElement ref = pinballElement(name);
    if(m_rootElement.elementsByTagName(name).size() > 0) return true;
    return false;
}

const QDomElement XMLReader::itemArgumentElement(const QString tagName)
{
    QDomElement e = m_searchUnderElement.firstChild().toElement();
    while(not e.isNull())
    {
        if(e.tagName() == tagName)
        {
            return e;
        }
        e = e.nextSibling().toElement();
    }
    return QDomElement();
}

const QDomElement XMLReader::pinballElement(const QString tagName)
{
    QDomElement e = m_rootElement.firstChild().firstChild().toElement();
    while(not e.isNull())
    {
        if(e.tagName() == tagName)
        {
            return e;
        }
        e = e.nextSibling().toElement();
    }
    return QDomElement();
}

const QDomElement XMLReader::pinballElement(const QDomElement &element)
{
    QDomElement e = element.firstChild().firstChild().toElement();
    while(not e.isNull())
    {
        if(e == element)
        {
            return e;
        }
        e = e.nextSibling().toElement();
    }
    return QDomElement();
}

const QDomElement XMLReader::searchTreeLevelUnder(const QDomElement &element)
{
    QDomElement e = element.firstChild().toElement();
    while(not e.isNull())
    {
        if(e == element)
        {
            e = e.nextSibling().toElement();
        }
    }
    return QDomElement();
}

/*! Returns all elements of the whole document as QList
 *
 * @return QList<QDomElement*>
 *
 * */
QList<QDomElement*> XMLReader::elements()
{
    QList<QDomElement*> elementList;
    elementList.append(&m_rootElement);
    QDomNode n = m_rootElement.firstChild();
    while(not n.isNull())
    {
        QDomElement e = n.toElement();
        if(not e.isNull())
        {
            elementList.append(&e);
            elementList.append(childrenFromParent(e));
        }
        n = n.nextSibling();
    }
    return elementList;
}

/*! Returns all elements located under the QDomElement p as QList
 *
 * @param p - const QDomElement
 *
 * @return QList<QDomElement*>
 *
 * */
QList<QDomElement*> XMLReader::childrenFromParent(const QDomElement &p)
{
    QList<QDomElement*> elementList;
    QDomNode n = p.firstChild();
    while(not n.isNull())
    {
        QDomElement e = n.toElement();
        if(not e.isNull())
        {
            elementList.append(&e);;
            elementList.append(childrenFromParent(e));
        }
        n = n.nextSibling();
    }
    return elementList;
}

//---------------------------------------SETTER--------------------------------------

/*! Sets the current top element under which a
 *
 * @param p - const QDomElement
 *
 * @return QList<QDomElement*>
 *
 * */
void XMLReader::setCurPinballItem(const QString &tagname)
{
    m_searchUnderElement = pinballElement(tagname);
}
