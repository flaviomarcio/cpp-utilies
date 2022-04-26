#ifndef SETTINGS_H
#define SETTINGS_H

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


public:
    Q_INVOKABLE explicit Settings(QObject *parent = nullptr);

public slots:

    Q_INVOKABLE void save();
    Q_INVOKABLE void load();


signals:
    void loaded();
    void saved();

};

#endif // SETTINGS_H
