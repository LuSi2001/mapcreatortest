#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <map>
#include <memory>
#include "pinballitem.h"
#include "readerproxy.h"
#include "binaryreader.h"

class ItemFactory
{
public:

    static ItemFactory& inst();

    PinballItem* itemBin(const QString &name) const;
    PinballItem* item(const QString &name) const;

    void registerItem(PinballItem *item);

private:

    ItemFactory() = default;
    ItemFactory(const ItemFactory &) = delete;
    ItemFactory &operator=(const ItemFactory &) = delete;

    using ItemMap = std::map<QString, std::unique_ptr<PinballItem>>;

    ItemMap m_items;
    ReaderProxy m_reader;
};

template <typename T> struct RegisterProxy
{
    RegisterProxy()
    {
        ItemFactory::inst().registerItem(new T);
    }
};

#endif // ITEMFACTORY_H
