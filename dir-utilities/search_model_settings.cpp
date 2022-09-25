#include "search_model_settings.h"

SearchModelSettings::SearchModelSettings(QObject *parent)
    : Settings{parent}
{
    connect(this, &SearchModelSettings::workDirChanged, this, &SearchModelSettings::save);
    connect(this, &SearchModelSettings::searchExtensionChanged, this, &SearchModelSettings::save);
    connect(this, &SearchModelSettings::changeIntoFilesChanged, this, &SearchModelSettings::save);
    connect(this, &SearchModelSettings::showAllFilesChanged, this, &SearchModelSettings::save);
    connect(this, &SearchModelSettings::searchExpressionChanged, this, &SearchModelSettings::save);
    connect(this, &SearchModelSettings::searchTextChanged, this, &SearchModelSettings::save);
    connect(this, &SearchModelSettings::searchTextReplaceChanged, this, &SearchModelSettings::save);
}

const QString SearchModelSettings::workDir() const
{
    return _workDir.trimmed();
}

void SearchModelSettings::setWorkDir(const QString &newWorkDir)
{
    if (_workDir == newWorkDir)
        return;
    _workDir = newWorkDir;
    emit workDirChanged();
}

void SearchModelSettings::resetWorkDir()
{
    setWorkDir({});
}

const QString SearchModelSettings::searchExtension() const
{
    return _searchExtension.trimmed();
}

void SearchModelSettings::setSearchExtension(const QString &newSearchExtension)
{
    if (_searchExtension == newSearchExtension)
        return;
    _searchExtension = newSearchExtension;
    emit searchExtensionChanged();
}

void SearchModelSettings::resetSearchExtension()
{
    setSearchExtension({});
}

bool SearchModelSettings::changeIntoFiles() const
{
    return _changeIntoFiles;
}

void SearchModelSettings::setChangeIntoFiles(bool newChangeIntoFiles)
{
    if (_changeIntoFiles == newChangeIntoFiles)
        return;
    _changeIntoFiles = newChangeIntoFiles;
    emit changeIntoFilesChanged();
}

void SearchModelSettings::resetChangeIntoFiles()
{
    setChangeIntoFiles({});
}

const QString SearchModelSettings::searchExpression() const
{
    return _searchExpression.trimmed();
}

void SearchModelSettings::setSearchExpression(const QString &newSearchExpression)
{
    if (_searchExpression == newSearchExpression)
        return;
    _searchExpression = newSearchExpression;
    emit searchExpressionChanged();
}

void SearchModelSettings::resetSearchExpression()
{
    setSearchExpression({});
}

const QString SearchModelSettings::searchText() const
{
    return _searchText.trimmed();
}

void SearchModelSettings::setSearchText(const QString &newSearchText)
{
    if (_searchText == newSearchText)
        return;
    _searchText = newSearchText;
    emit searchTextChanged();
}

void SearchModelSettings::resetSearchText()
{
    setSearchText({});
}

const QString &SearchModelSettings::searchTextReplace() const
{
    return _searchTextReplace;
}

void SearchModelSettings::setSearchTextReplace(const QString &newSearchTextReplace)
{
    if (_searchTextReplace == newSearchTextReplace)
        return;
    _searchTextReplace = newSearchTextReplace;
    emit searchTextReplaceChanged();
}

void SearchModelSettings::resetSearchTextReplace()
{
    setSearchTextReplace({});
}

bool SearchModelSettings::showAllFiles() const
{
    return _showAllFiles;
}

void SearchModelSettings::setShowAllFiles(bool newShowAllFiles)
{
    if (_showAllFiles == newShowAllFiles)
        return;
    _showAllFiles = newShowAllFiles;
    emit showAllFilesChanged();
}
