#ifndef XMLREADER_H
#define XMLREADER_H

#include <QFile>

#include <QDomElement>

class QDomDocument;

class XMLReader
{
public:
    XMLReader();
    XMLReader(const QString fileName);
    bool find(const QString& name);

    void setCurPinballItem(const QString& tagname);

    const QDomElement itemArgumentElement(const QString tagName);
    const QDomElement pinballElement(const QString tagName);
    const QDomElement pinballElement(const QDomElement& element);
    const QDomElement searchTreeLevelUnder(const QDomElement& element);
    QList<QDomElement*> elements();
    QList<QDomElement*> childrenFromParent(const QDomElement &p);

private:
    QDomDocument m_doc;
    QDomElement m_searchUnderElement;
    QDomElement m_rootElement;
    QFile m_file;

    void init();
};

#endif // XMLREADER_H
