#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QVariant>

#include "graphserialization_global.h"

class GRAPHSERIALIZATION_EXPORT Serializable
{
public:
    virtual ~Serializable() = default;

    virtual QVariant toVariant() const = 0;

    virtual void fromVariant(const QVariant & variant) = 0;
};


#endif // SERIALIZABLE_H
