#include "itemfactory.h"

#include <QDebug>

ItemFactory& ItemFactory::inst()
{
    static ItemFactory obj;
    return obj;
}

PinballItem* ItemFactory::itemBin(const QString &name) const
{
    auto it = m_items.find(name);

    if (it != m_items.end())
    {
        PinballItem* i = it->second->cloneType();
//        i->readFromBinary(m_reader);
        return i;
    }

    return nullptr;
}

PinballItem* ItemFactory::item(const QString &name) const
{
    auto it = m_items.find(name);

    if (it != m_items.end())
    {
        PinballItem* i = it->second->clone();
        return i;
    }

    return nullptr;
}

void ItemFactory::registerItem(PinballItem *item)
{
    auto it = m_items.find(item->name());

    if (it == m_items.end())
    {
        m_items[item->name()].reset(item);
        m_items[item->name()]->readFromXML(m_reader);
    }
}
