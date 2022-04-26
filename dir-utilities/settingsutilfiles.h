#ifndef SETTINGSUTILFILES_H
#define SETTINGSUTILFILES_H

#include "./settings.h"

class SettingsUtilFiles : public Settings
{
    Q_OBJECT

    Q_PROPERTY(QString workDir READ workDir WRITE setWorkDir RESET resetWorkDir NOTIFY workDirChanged)
    Q_PROPERTY(QString searchExtension READ searchExtension WRITE setSearchExtension RESET resetSearchExtension NOTIFY searchExtensionChanged)
    Q_PROPERTY(bool changeIntoFiles READ changeIntoFiles WRITE setChangeIntoFiles RESET resetChangeIntoFiles NOTIFY changeIntoFilesChanged)
    Q_PROPERTY(QString searchExpression READ searchExpression WRITE setSearchExpression RESET resetSearchExpression NOTIFY searchExpressionChanged)
    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText RESET resetSearchText NOTIFY searchTextChanged)
    Q_PROPERTY(QString searchTextReplace READ searchTextReplace WRITE setSearchTextReplace RESET resetSearchTextReplace NOTIFY searchTextReplaceChanged)
    Q_PROPERTY(bool showAllFiles READ showAllFiles WRITE setShowAllFiles NOTIFY showAllFilesChanged)

public:
    Q_INVOKABLE explicit SettingsUtilFiles(QObject *parent = nullptr);


    const QString workDir() const;
    void setWorkDir(const QString &newWorkDir);
    void resetWorkDir();

    const QString searchExtension() const;
    void setSearchExtension(const QString &newSearchExtension);
    void resetSearchExtension();

    bool changeIntoFiles() const;
    void setChangeIntoFiles(bool newChangeIntoFiles);
    void resetChangeIntoFiles();

    const QString searchExpression() const;
    void setSearchExpression(const QString &newSearchExpression);
    void resetSearchExpression();

    const QString searchText() const;
    void setSearchText(const QString &newSearchText);
    void resetSearchText();

    const QString &searchTextReplace() const;
    void setSearchTextReplace(const QString &newSearchTextReplace);
    void resetSearchTextReplace();

    bool showAllFiles() const;
    void setShowAllFiles(bool newShowAllFiles);

signals:

    void workDirChanged();
    void searchExtensionChanged();
    void changeIntoFilesChanged();
    void searchExpressionChanged();
    void searchTextChanged();
    void searchTextReplaceChanged();
    void showAllFilesChanged();

private:
    QString _workDir=QString("%1/qtreforce.mfe").arg(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    QString _searchExtension="*.h, *.cpp, *.qml";
    bool _changeIntoFiles=false;
    QString _searchExpression;
    QString _searchText;
    QString _searchTextReplace;
    bool _showAllFiles=true;
};

#endif // SETTINGSUTILFILES_H
