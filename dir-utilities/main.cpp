#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "./searchmodel.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/dir-utilities/main.qml"_qs);

    qRegisterMetaType<SearchModel>("SearchModel");
    qmlRegisterType<SearchModel>("Utils", 0, 0, "SearchModel");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
