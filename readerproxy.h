#ifndef READERPROXY_H
#define READERPROXY_H

#include <QColor>
#include <QLinearGradient>
#include "xmlreader.h"
#include "binaryreader.h"
#include "constants.h"

//struct NamedVariable
//{
//    const char  *name;
//    union
//    {
//        int     iV;
//        float   fV;
//        QColor  cV;
//    } V;

//    void    set(float v) {V.fV = v;}
//    void    set(int v) {V.iV = v;}
//    void    set(const QColor &v) {V.cV = v;}

//    void    get(float &v) const {v = V.fV;}
//    float   getFloat() const {return V.fV;}


//    const float &operator()() const {return V.fV;}
//};

class ReaderProxy
{
public:
    ReaderProxy();
    bool readXML(const QString& name, int &value) const;
    bool readXML(const QString& name, qreal &value) const;
    bool readXML(const QString& name, QColor &c) const;
    bool readXML(const QString& name, QLinearGradient &lg) const;
    bool readXML(const QString& name, ItemColorMode &mode) const;
    bool readXML(const QString& name, QString &link) const;
    bool readBinary(const QString& name, int &value) const;
    bool readBinary(const QString& name, qreal &value) const;
    bool readBinary(const QString& name, QColor &c) const;
    bool readBinary(const QString& name, QLinearGradient &lg) const;
    bool readBinary(const QString& name, ItemColorMode &mode) const;
    bool readBinary(const QString& name, QString &link) const;

    void setCurPinballItem(const QString& name) const;

private:
    XMLReader *m_xmlReader;
    BinaryReader *m_binReader;

//    NamedVariable   radius;// = {"Radius"};
};

#endif // READERPROXY_H
