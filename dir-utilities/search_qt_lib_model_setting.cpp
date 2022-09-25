#include "search_qt_lib_model_setting.h"

SearchQtLibModelSettings::SearchQtLibModelSettings(QObject *parent)
    : Settings{parent}
{
    connect(this, &SearchQtLibModelSettings::workDirChanged, this, &SearchQtLibModelSettings::save);
    connect(this, &SearchQtLibModelSettings::searchExtensionChanged, this, &SearchQtLibModelSettings::save);
    connect(this, &SearchQtLibModelSettings::changeIntoFilesChanged, this, &SearchQtLibModelSettings::save);
    connect(this, &SearchQtLibModelSettings::showAllFilesChanged, this, &SearchQtLibModelSettings::save);
    connect(this, &SearchQtLibModelSettings::searchExpressionChanged, this, &SearchQtLibModelSettings::save);
    connect(this, &SearchQtLibModelSettings::searchTextChanged, this, &SearchQtLibModelSettings::save);
    connect(this, &SearchQtLibModelSettings::searchTextReplaceChanged, this, &SearchQtLibModelSettings::save);
}

const QString SearchQtLibModelSettings::workDir() const
{
    return _workDir.trimmed();
}

void SearchQtLibModelSettings::setWorkDir(const QString &newWorkDir)
{
    if (_workDir == newWorkDir)
        return;
    _workDir = newWorkDir;
    emit workDirChanged();
}

void SearchQtLibModelSettings::resetWorkDir()
{
    setWorkDir({});
}

const QString SearchQtLibModelSettings::searchExtension() const
{
    return _searchExtension.trimmed();
}

void SearchQtLibModelSettings::setSearchExtension(const QString &newSearchExtension)
{
    if (_searchExtension == newSearchExtension)
        return;
    _searchExtension = newSearchExtension;
    emit searchExtensionChanged();
}

void SearchQtLibModelSettings::resetSearchExtension()
{
    setSearchExtension({});
}

bool SearchQtLibModelSettings::changeIntoFiles() const
{
    return _changeIntoFiles;
}

void SearchQtLibModelSettings::setChangeIntoFiles(bool newChangeIntoFiles)
{
    if (_changeIntoFiles == newChangeIntoFiles)
        return;
    _changeIntoFiles = newChangeIntoFiles;
    emit changeIntoFilesChanged();
}

void SearchQtLibModelSettings::resetChangeIntoFiles()
{
    setChangeIntoFiles({});
}

const QString SearchQtLibModelSettings::searchExpression() const
{
    return _searchExpression.trimmed();
}

void SearchQtLibModelSettings::setSearchExpression(const QString &newSearchExpression)
{
    if (_searchExpression == newSearchExpression)
        return;
    _searchExpression = newSearchExpression;
    emit searchExpressionChanged();
}

void SearchQtLibModelSettings::resetSearchExpression()
{
    setSearchExpression({});
}

const QString SearchQtLibModelSettings::searchText() const
{
    return _searchText.trimmed();
}

void SearchQtLibModelSettings::setSearchText(const QString &newSearchText)
{
    if (_searchText == newSearchText)
        return;
    _searchText = newSearchText;
    emit searchTextChanged();
}

void SearchQtLibModelSettings::resetSearchText()
{
    setSearchText({});
}

const QString &SearchQtLibModelSettings::searchTextReplace() const
{
    return _searchTextReplace;
}

void SearchQtLibModelSettings::setSearchTextReplace(const QString &newSearchTextReplace)
{
    if (_searchTextReplace == newSearchTextReplace)
        return;
    _searchTextReplace = newSearchTextReplace;
    emit searchTextReplaceChanged();
}

void SearchQtLibModelSettings::resetSearchTextReplace()
{
    setSearchTextReplace({});
}

bool SearchQtLibModelSettings::showAllFiles() const
{
    return _showAllFiles;
}

void SearchQtLibModelSettings::setShowAllFiles(bool newShowAllFiles)
{
    if (_showAllFiles == newShowAllFiles)
        return;
    _showAllFiles = newShowAllFiles;
    emit showAllFilesChanged();
}
