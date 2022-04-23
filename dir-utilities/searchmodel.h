#pragma once

#include <QObject>
#include <QVariant>
#include <QVector>
#include <QHash>
#include <QAbstractItemModel>
#include <QStandardPaths>

class SearchModel : public QAbstractTableModel
{
    Q_OBJECT

    Q_PROPERTY(QString rootDir READ rootDir WRITE setRootDir RESET resetRootDir NOTIFY rootDirChanged)
    Q_PROPERTY(QString ext READ ext WRITE setExt RESET resetExt NOTIFY extChanged)
    Q_PROPERTY(bool changeIntoFiles READ changeIntoFiles WRITE setChangeIntoFiles RESET resetChangeIntoFiles NOTIFY changeIntoFilesChanged)
    Q_PROPERTY(QString expression READ expression WRITE setExpression RESET resetExpression NOTIFY expressionChanged)
public:

    enum Roles{
        FileName=Qt::UserRole+1,
        FilePath=Qt::DisplayRole+2
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

    Q_INVOKABLE void search();

    Q_INVOKABLE void rename(const QString &replaceText, const QString &newText);

    const QString &rootDir() const;
    void setRootDir(const QString &newRootDir);
    void resetRootDir();

    const QString &ext() const;
    void setExt(const QString &newExt);
    void resetExt();

    bool changeIntoFiles();
    void setChangeIntoFiles(const bool &newChangeIntoFiles);
    void resetChangeIntoFiles();

    const QString &expression() const;
    void setExpression(const QString &newExpression);
    void resetExpression();

private:
    QHash<int, QByteArray> roles=
    {
        {FileName,"FileName"}, {FileName,"fileName"},
        {FilePath,"FilePath"}, {FilePath,"filePath"}
    };
    QVector<QHash<int, QVariant>> rows;
    QString _rootDir=QString("%1/qtreforce.mfe").arg(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    QString _ext="*.h, *.cpp, *.qml";
    bool _changeIntoFiles=true;
    QString _expression;

signals:
    void rootDirChanged();
    void extChanged();
    void changeIntoFilesChanged();
    void expressionChanged();
};
