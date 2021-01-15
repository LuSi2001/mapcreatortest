#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <QFile>
#include <QDataStream>

#include "pinballitem.h"

class BinaryReader : public QObject
{
    Q_OBJECT
public:
    BinaryReader();
    BinaryReader(const QString& fileName);
    QList<PinballItem *> readAll();
    void close();
    void setFilename(const QString& fileName);

private:
    QFile m_file;
    QDataStream m_in;
    QString m_fileName;

    void init();

signals:
    void newPixmap(const QPixmap& pixi);

};

#endif // BINARYREADER_H
