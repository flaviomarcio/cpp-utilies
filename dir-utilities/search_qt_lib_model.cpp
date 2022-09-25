#include "./search_qt_lib_model.h"
#include <QDir>
#include <QDebug>
#include <QRegularExpressionMatch>
#include <QDirIterator>
#include <QCoreApplication>

QVector<QHash<int, QVariant>> searchPaths(const SearchQtLibModelSettings& settings)
{
    QVector<QHash<int, QVariant>> __return;
    QDir dir(settings.workDir());
    if(!dir.exists())
        dir.mkpath(settings.workDir());

    if(!dir.exists())
        return {};

    QStringList searchExtension;
    auto s=settings.searchExtension().trimmed().simplified();
    for(auto&v:s.split(",")){
        auto s=v.trimmed();
        if(s.isEmpty())
            continue;
        searchExtension.append(s);
    }

    if(searchExtension.isEmpty())
        searchExtension.append("*.*");

    //find paths where contains configuration files
    QDirIterator it(settings.workDir(), searchExtension, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()){
        it.next();
        const auto info=it.fileInfo();

        if(!settings.showAllFiles()){
            if(!settings.searchExpression().isEmpty()){
                QRegularExpression re(settings.searchExpression());
                QRegularExpressionMatch match = re.match(info.fileName());
                if (!match.hasMatch())
                    continue;
            }

            if(!settings.searchText().isEmpty()){
                if(!info.fileName().contains(settings.searchText()))
                    continue;
            }
        }

        auto v=QHash<int, QVariant>
        {
            {SearchQtLibModel::FileName, info.fileName()},
            {SearchQtLibModel::FilePath, info.filePath()},
            {SearchQtLibModel::Path, info.path()}
        };
        __return.append(v);
    }
    return __return;
}

SearchQtLibModel::SearchQtLibModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    this->_settings.load();
    connect(&this->_settings, &SearchQtLibModelSettings::saved, this, &SearchQtLibModel::search);
}

QModelIndex SearchQtLibModel::index(int row, int column, const QModelIndex &parent) const
{
    const auto &v=this->rows[row].value(column);
    return this->createIndex(row, column, &v);
}

QVariant SearchQtLibModel::data(const QModelIndex &index, int role) const
{
    const auto &v=this->rows[index.row()];

    auto data=v.value(role);
    return data;
}

QVariant SearchQtLibModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    auto data=this->roles.value(role);
    return data;
}

QHash<int, QByteArray> SearchQtLibModel::roleNames() const
{
    return this->roles;
}

QHash<int, QByteArray> SearchQtLibModel::columnNames() const
{
    return this->roles;
}

int SearchQtLibModel::rowCount(const QModelIndex &parent) const
{
    return this->rows.count();
}

int SearchQtLibModel::columnCount(const QModelIndex &parent) const
{
    return this->roles.count();
}

void SearchQtLibModel::clear()
{
    this->rows.clear();
}

void SearchQtLibModel::search()
{
    this->clear();
    this->beginResetModel();
    this->rows=searchPaths(this->_settings);
    this->endResetModel();
}

void SearchQtLibModel::rename(const QString&replaceText, const QString&newText)
{
    for(auto&v:this->rows){
        auto path=v.value(Path).toString();
        auto fileName=v.value(FileName).toString();
        auto srcFile=fileName;
        auto renFile=fileName.replace(replaceText, newText);

//        if(renFile==srcFile)
//            continue;

        if(_settings.changeIntoFiles()){
            QFile file(path+"/"+srcFile);
            if(!file.open(file.ReadOnly)){
                qWarning()<<file.errorString();
                return;
            }
            auto bytes=file.readAll();
            file.close();
            if(bytes.contains(_settings.searchText().toUtf8())){
                bytes=bytes.replace(_settings.searchText().toUtf8(), _settings.searchTextReplace().toUtf8());
                if(!file.open(file.Truncate | file.WriteOnly)){
                    qWarning()<<file.errorString();
                    return;
                }
                file.write(bytes);
                file.flush();
                file.close();
            }
        }


        QFile::rename(path+"/"+srcFile, path+"/"+renFile);
    }
    this->search();
}

SearchQtLibModelSettings *SearchQtLibModel::settings()
{
    return &_settings;
}

void SearchQtLibModel::setSettings(const SearchQtLibModelSettings *newSettings)
{
//    if (_settings == newSettings)
//        return;
//    _settings = newSettings;
    emit settingsChanged();
}

void SearchQtLibModel::resetSettings()
{
    setSettings({});
}
