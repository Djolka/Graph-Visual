#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "graphserialization_global.h"
#include "serializer.h"

class GRAPHSERIALIZATION_EXPORT JSONSerializer : public Serializer
{
public:
    JSONSerializer();

    void save(const Serializable &serializable, const QString &filepath, const QString &rootName = "") override;

    void load(Serializable &serializable, const QString &filepath) override;
};


#endif // JSONSERIALIZER_H
