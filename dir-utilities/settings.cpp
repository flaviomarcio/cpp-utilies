#include "settings.h"

Settings::Settings(QObject *parent)
    : QObject{parent}
{

}

QString Settings::fileName() const
{
    if(!this->_name.trimmed().isEmpty())
        return QString("%1/%2.settings.json").arg(_name, QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    return QString("%1.settings.json").arg(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));

}

void Settings::save()
{
    static const QByteArray propertyObjectName="objectName";
    QVariantHash data;
    auto&metaObject = *this->metaObject();
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        if(QByteArray(property.name()) == propertyObjectName)
            continue;
        data.insert(property.name(), property.read(this));
    }

    auto sDir=QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(sDir);
    if(!dir.exists())
        dir.mkdir(sDir);

    auto fileName=this->fileName();
    QFile file(fileName);
    if(!file.open(file.Truncate | file.WriteOnly)){
        qWarning()<<file.errorString();
        return;
    }

    file.write(QJsonDocument::fromVariant(data).toJson(QJsonDocument::Indented));
    file.flush();
    file.close();

    emit saved();
}

void Settings::load()
{
    auto fileName=this->fileName();
    QFile file(fileName);

    if(!file.exists()){
        return;
    }

    if(!file.open(file.ReadOnly)){
        qWarning()<<file.errorString();
        return;
    }

    auto data=QJsonDocument::fromJson(file.readAll()).toVariant().toHash();
    file.close();

    QHashIterator <QString, QVariant> i(data);
    while(i.hasNext()){
        i.next();
        if(!this->setProperty(i.key().toUtf8(), i.value()))
            qWarning()<<"No set property: "<<i.key() <<" with value: "<<i.value();
    }

    emit loaded();
}

const QString &Settings::name() const
{
    return _name;
}

void Settings::setName(const QString &newName)
{
    if (_name == newName)
        return;
    _name = newName;
    emit nameChanged();
}

void Settings::resetName()
{
    setName({}); // TODO: Adapt to use your actual default value
}
