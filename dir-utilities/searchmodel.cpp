#include "./searchmodel.h"
#include <QDir>
#include <QDebug>
#include <QRegularExpressionMatch>
#include <QDirIterator>
#include <QCoreApplication>

QVector<QHash<int, QVariant>> searchPaths(const QString&rootDir, const QVariant&extention, const QString&expression)
{
    QVector<QHash<int, QVariant>> __return;
    QDir dir(rootDir);
    if(!dir.exists())
        dir.mkpath(rootDir);

    if(!dir.exists())
        return {};

    QStringList ext;
    switch (extention.typeId()) {
    case QMetaType::QStringList:
    case QMetaType::QVariantList:{
        for(auto&v:extention.toList()){
            auto s=v.toString().trimmed();
            if(s.isEmpty())
                continue;

            ext.append(s);
        }
        break;
    }
    default:
        auto s=extention.toString().trimmed();
        for(auto&v:s.split(",")){
            auto s=v.trimmed();
            if(s.isEmpty())
                continue;
            ext.append(s);
        }
    }
    if(ext.isEmpty())
        ext.append("*.*");

    //find paths where contains configuration files
    QDirIterator it(rootDir, ext, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()){
        it.next();
        const auto info=it.fileInfo();

        if(!expression.isEmpty()){
            QRegularExpression re(expression);
            QRegularExpressionMatch match = re.match(info.fileName());
            if (!match.hasMatch())
                continue;
        }

        auto v=QHash<int, QVariant>
        {
            {SearchModel::FileName, info.fileName()},
            {SearchModel::FilePath, info.filePath()}
        };
        __return.append(v);
    }
    return __return;
}

SearchModel::SearchModel(QObject *parent)
    : QAbstractTableModel{parent}
{

}

QModelIndex SearchModel::index(int row, int column, const QModelIndex &parent) const
{
    const auto &v=this->rows[row].value(column);
    return this->createIndex(row, column, &v);
}

QVariant SearchModel::data(const QModelIndex &index, int role) const
{
    const auto &v=this->rows[index.row()];

    auto data=v.value(role);
    return data;
}

QVariant SearchModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    auto data=this->roles.value(role);
    return data;
}

QHash<int, QByteArray> SearchModel::roleNames() const
{
    return this->roles;
}

QHash<int, QByteArray> SearchModel::columnNames() const
{
    return this->roles;
}

int SearchModel::rowCount(const QModelIndex &parent) const
{
    return this->rows.count();
}

int SearchModel::columnCount(const QModelIndex &parent) const
{
    return this->roles.count();
}

void SearchModel::clear()
{
    this->rows.clear();
}

void SearchModel::search()
{
    this->clear();
    this->beginResetModel();
    this->rows=searchPaths(this->_rootDir, this->_ext, this->_expression);
    this->endResetModel();
}

void SearchModel::rename(const QString&replaceText, const QString&newText)
{
    for(auto&v:this->rows){
        auto srcFile=v.value(FileName).toString();
        auto renFile=srcFile.replace(replaceText, newText);
        QFile::rename(srcFile, renFile);
    }
    this->search();
}

const QString &SearchModel::rootDir() const
{
    return _rootDir;
}

void SearchModel::setRootDir(const QString &newRootDir)
{
    if (_rootDir == newRootDir)
        return;
    _rootDir = newRootDir;
    this->search();
    emit rootDirChanged();
}

void SearchModel::resetRootDir()
{
    setRootDir({}); // TODO: Adapt to use your actual default value
}

const QString &SearchModel::ext() const
{
    return _ext;
}

void SearchModel::setExt(const QString &newExt)
{
    if (_ext == newExt)
        return;
    _ext = newExt;
    this->search();
    emit extChanged();
}

void SearchModel::resetExt()
{
    setExt({}); // TODO: Adapt to use your actual default value
}

bool SearchModel::changeIntoFiles()
{
    return _changeIntoFiles;
}

void SearchModel::setChangeIntoFiles(const bool &newChangeIntoFiles)
{
    if (_changeIntoFiles == newChangeIntoFiles)
        return;
    _changeIntoFiles = newChangeIntoFiles;
    this->search();
    emit extChanged();
}

void SearchModel::resetChangeIntoFiles()
{
    setChangeIntoFiles({}); // TODO: Adapt to use your actual default value
}

const QString &SearchModel::expression() const
{
    return _expression;
}

void SearchModel::setExpression(const QString &newExpression)
{
    if (_expression == newExpression)
        return;
    _expression = newExpression;
    this->search();
    emit expressionChanged();
}

void SearchModel::resetExpression()
{
    setExpression({}); // TODO: Adapt to use your actual default value
}
