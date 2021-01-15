#include "binaryreader.h"
#include "itemfactory.h"

#include <QDebug>

BinaryReader::BinaryReader() : m_file("/home/azubi_cgf/Luca/scenetest/test.bin")
{
    init();
}

BinaryReader::BinaryReader(const QString& fileName) : m_file(fileName)
{
    init();
}

void BinaryReader::init()
{
    if(!m_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Unable to open file.";
        return;
    }

    m_in.setDevice(&m_file);
    m_in.setVersion(QDataStream::Qt_5_9);
}

void BinaryReader::setFilename(const QString& fileName)
{
    m_file.close();
    m_file.setFileName(fileName);
    init();
}

QList<PinballItem *> BinaryReader::readAll()
{
    QList<PinballItem *> items;

    int counter = 0;
    while(not m_in.atEnd())
    {
        if(counter == 0)
        {
            QPixmap pixi;
            m_in >> pixi;
            emit newPixmap(pixi);
        }
        QString ch;
        m_in >> ch;
        items.push_back(ItemFactory::inst().item(ch));
        items.back()->read(m_in);
        counter++;
    }

    return items;
}

void BinaryReader::close()
{
    m_file.close();
}
