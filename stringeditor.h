#ifndef STRINGEDITOR_H
#define STRINGEDITOR_H

#include <QString>
#include <QPushButton>
#include <QDebug>

struct StringEditor
{
    static const QString& truncatedName(QPushButton* btn)
    {
        QString newStr = btn->objectName();
        newStr = newStr.remove(-3, 3);
        QString* res = new QString(newStr.toLower());
        return *res;
    }
};

#endif // STRINGEDITOR_H
