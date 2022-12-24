#ifndef BINARYSERIALIZER_H
#define BINARYSERIALIZER_H

#include "graphserialization_global.h"
#include "serializer.h"

class GRAPHSERIALIZATION_EXPORT BinarySerializer : public Serializer
{
public:
    BinarySerializer();

    void save(const Serializable &serializable, const QString &filepath, const QString &rootName = "") override;
    void load(Serializable &serializable, const QString &filepath) override;
};




#endif // BINARYSERIALIZER_H
