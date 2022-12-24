#include "Headers/xmlserializer.h"

#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>


XMLSerializer::XMLSerializer()
{

}

void XMLSerializer::save(const Serializable &serializable, const QString &filepath, const QString &rootName)
{
    QFile file(filepath);
    file.open(QFile::WriteOnly);

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);

    stream.writeStartDocument();

    writeVariantToStream(rootName, serializable.toVariant(), stream);

    stream.writeEndDocument();
    file.close();
}

void XMLSerializer::load(Serializable &serializable, const QString &filepath)
{

    QFile file(filepath);
    file.open(QFile::ReadOnly);
    QXmlStreamReader stream(&file);
    stream.readNextStartElement();
    serializable.fromVariant(readVariantFromStream(stream));
    file.close();
}

void XMLSerializer::writeVariantToStream(const QString &nodeName, const QVariant &variant, QXmlStreamWriter &stream)
{

    stream.writeStartElement(nodeName);

    stream.writeAttribute("type", variant.typeName());


    switch (variant.type()) {
    case QVariant::Type::List:
        writeVariantListToStream(variant, stream);
        break;
    case QVariant::Type::Map:
        writeVariantMapToStream(variant, stream);
        break;
    default:
        writeVariantValueToStream(variant, stream);
        break;
    }

    stream.writeEndElement();
}


void XMLSerializer::writeVariantValueToStream(const QVariant &variant, QXmlStreamWriter &stream)
{
    stream.writeCharacters(variant.toString());
}

void XMLSerializer::writeVariantListToStream(const QVariant &variant, QXmlStreamWriter &stream)
{
    const auto variantList = variant.toList();

    for(const auto& element : variantList) {
        writeVariantToStream("item", element, stream);
    }
}

void XMLSerializer::writeVariantMapToStream(const QVariant &variant, QXmlStreamWriter &stream)
{
    const auto variantMap = variant.toMap();
    QMapIterator<QString, QVariant> i(variantMap);

    while (i.hasNext()) {
        i.next();
        writeVariantToStream(i.key(), i.value(), stream);
    }
}

QVariant XMLSerializer::readVariantFromStream(QXmlStreamReader &stream)
{
    QXmlStreamAttributes attributes = stream.attributes();
    QString typeString = attributes.value("type").toString();
    QVariant variant;

    switch (QVariant::nameToType(typeString.toStdString().c_str())) {
    case QVariant::Type::List:
        variant = readVariantListFromStream(stream);
        break;
    case QVariant::Type::Map:
        variant = readVariantMapFromStream(stream);
        break;
    default:
        variant = readVariantValueFromStream(stream);
        break;
    }

    return variant;
}

QVariant XMLSerializer::readVariantValueFromStream(QXmlStreamReader &stream)
{

    QXmlStreamAttributes attributes = stream.attributes();
    QString typeString = attributes.value("type").toString();

    QString dataString = stream.readElementText();

    QVariant variant(dataString);

    variant.convert(QVariant::nameToType(typeString.toStdString().c_str()));
    return variant;
}

QVariant XMLSerializer::readVariantListFromStream(QXmlStreamReader &stream)
{
    QVariantList list;

    while(stream.readNextStartElement()) {
        list.append(readVariantFromStream(stream));
    }
    return list;
}

QVariant XMLSerializer::readVariantMapFromStream(QXmlStreamReader &stream)
{
    QVariantMap map;
    while(stream.readNextStartElement()) {
        map.insert(stream.name().toString(), readVariantFromStream(stream));
    }
    return map;
}

