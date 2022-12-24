#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "graphserialization_global.h"
#include "serializable.h"

class GRAPHSERIALIZATION_EXPORT Serializer
{
public:
    virtual ~Serializer() = default;

    virtual void save(const Serializable& serializable, const QString& filepath, const QString& rootName = "") = 0;

    virtual void load(Serializable& serializable, const QString& filepath) = 0;
};



#endif // SERIALIZER_H
