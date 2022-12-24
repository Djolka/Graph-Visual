#include "Headers/jsonserializer.h"

#include <QJsonDocument>
#include <QFile>


JSONSerializer::JSONSerializer()
{

}

void JSONSerializer::save(const Serializable &serializable, const QString &filepath, const QString &rootName)
{

    Q_UNUSED(rootName);


    QJsonDocument doc = QJsonDocument::fromVariant(serializable.toVariant());
    QFile file(filepath);
    file.open(QFile::WriteOnly);
    file.write(doc.toJson(QJsonDocument::JsonFormat::Indented)); // Neminimizovan zapis (moze i QJsonDocument::JsonFormat::Compact)
    file.close();
}

void JSONSerializer::load(Serializable &serializable, const QString &filepath)
{
    QFile file(filepath);
    file.open(QFile::ReadOnly);

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    serializable.fromVariant(doc.toVariant());
}


