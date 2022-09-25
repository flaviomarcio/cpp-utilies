#pragma once

#include <QObject>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QMetaProperty>
#include <QFile>
#include <QDir>
#include <QVariant>
#include <QVariantHash>

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName RESET resetName NOTIFY nameChanged)
public:
    Q_INVOKABLE explicit Settings(QObject *parent = nullptr);

    const QString &name() const;
    void setName(const QString &newName);
    void resetName();

public slots:

    Q_INVOKABLE void save();
    Q_INVOKABLE void load();

private:
    QString _name;
signals:
    void loaded();
    void saved();

    void nameChanged();
};
