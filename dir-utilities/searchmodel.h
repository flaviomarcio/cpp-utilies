#pragma once

#include <QObject>
#include <QVariant>
#include <QVector>
#include <QHash>
#include <QAbstractItemModel>
#include <QStandardPaths>
#include "settingsutilfiles.h"

class SearchModel : public QAbstractTableModel
{
    Q_OBJECT

    Q_PROPERTY(SettingsUtilFiles* settings READ settings WRITE setSettings RESET resetSettings NOTIFY settingsChanged)

public:

    enum Roles{
        FileName=Qt::UserRole+1,
        FilePath=Qt::DisplayRole+2,
        Path=Qt::DisplayRole+3
    };

    explicit SearchModel(QObject *parent = nullptr);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;
    virtual QHash<int,QByteArray> columnNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent) const override;

    Q_INVOKABLE void clear();


    Q_INVOKABLE void rename(const QString &replaceText, const QString &newText);

    SettingsUtilFiles *settings();
    void setSettings(const SettingsUtilFiles *newSettings);
    void resetSettings();

public slots:
    Q_INVOKABLE void search();
private:
    QHash<int, QByteArray> roles=
    {
        {FileName,"FileName"}, {FileName,"fileName"},
        {FilePath,"FilePath"}, {FilePath,"filePath"}
    };
    QVector<QHash<int, QVariant>> rows;
    SettingsUtilFiles _settings;

signals:
    void settingsChanged();
};
