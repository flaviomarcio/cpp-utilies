#include "settingsutilfiles.h"

SettingsUtilFiles::SettingsUtilFiles(QObject *parent)
    : Settings{parent}
{
    connect(this, &SettingsUtilFiles::workDirChanged, this, &SettingsUtilFiles::save);
    connect(this, &SettingsUtilFiles::searchExtensionChanged, this, &SettingsUtilFiles::save);
    connect(this, &SettingsUtilFiles::changeIntoFilesChanged, this, &SettingsUtilFiles::save);
    connect(this, &SettingsUtilFiles::showAllFilesChanged, this, &SettingsUtilFiles::save);
    connect(this, &SettingsUtilFiles::searchExpressionChanged, this, &SettingsUtilFiles::save);
    connect(this, &SettingsUtilFiles::searchTextChanged, this, &SettingsUtilFiles::save);
    connect(this, &SettingsUtilFiles::searchTextReplaceChanged, this, &SettingsUtilFiles::save);
}

const QString SettingsUtilFiles::workDir() const
{
    return _workDir.trimmed();
}

void SettingsUtilFiles::setWorkDir(const QString &newWorkDir)
{
    if (_workDir == newWorkDir)
        return;
    _workDir = newWorkDir;
    emit workDirChanged();
}

void SettingsUtilFiles::resetWorkDir()
{
    setWorkDir({});
}

const QString SettingsUtilFiles::searchExtension() const
{
    return _searchExtension.trimmed();
}

void SettingsUtilFiles::setSearchExtension(const QString &newSearchExtension)
{
    if (_searchExtension == newSearchExtension)
        return;
    _searchExtension = newSearchExtension;
    emit searchExtensionChanged();
}

void SettingsUtilFiles::resetSearchExtension()
{
    setSearchExtension({});
}

bool SettingsUtilFiles::changeIntoFiles() const
{
    return _changeIntoFiles;
}

void SettingsUtilFiles::setChangeIntoFiles(bool newChangeIntoFiles)
{
    if (_changeIntoFiles == newChangeIntoFiles)
        return;
    _changeIntoFiles = newChangeIntoFiles;
    emit changeIntoFilesChanged();
}

void SettingsUtilFiles::resetChangeIntoFiles()
{
    setChangeIntoFiles({});
}

const QString SettingsUtilFiles::searchExpression() const
{
    return _searchExpression.trimmed();
}

void SettingsUtilFiles::setSearchExpression(const QString &newSearchExpression)
{
    if (_searchExpression == newSearchExpression)
        return;
    _searchExpression = newSearchExpression;
    emit searchExpressionChanged();
}

void SettingsUtilFiles::resetSearchExpression()
{
    setSearchExpression({});
}

const QString SettingsUtilFiles::searchText() const
{
    return _searchText.trimmed();
}

void SettingsUtilFiles::setSearchText(const QString &newSearchText)
{
    if (_searchText == newSearchText)
        return;
    _searchText = newSearchText;
    emit searchTextChanged();
}

void SettingsUtilFiles::resetSearchText()
{
    setSearchText({});
}

const QString &SettingsUtilFiles::searchTextReplace() const
{
    return _searchTextReplace;
}

void SettingsUtilFiles::setSearchTextReplace(const QString &newSearchTextReplace)
{
    if (_searchTextReplace == newSearchTextReplace)
        return;
    _searchTextReplace = newSearchTextReplace;
    emit searchTextReplaceChanged();
}

void SettingsUtilFiles::resetSearchTextReplace()
{
    setSearchTextReplace({});
}

bool SettingsUtilFiles::showAllFiles() const
{
    return _showAllFiles;
}

void SettingsUtilFiles::setShowAllFiles(bool newShowAllFiles)
{
    if (_showAllFiles == newShowAllFiles)
        return;
    _showAllFiles = newShowAllFiles;
    emit showAllFilesChanged();
}
