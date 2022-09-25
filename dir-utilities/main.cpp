#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "./search_model.h"
#include "./search_model_settings.h"
#include "./search_qt_lib_model.h"
#include "./search_qt_lib_model_setting.h"


#define CLASS_REGISTER(CLASS)\
    qRegisterMetaType<CLASS>(#CLASS);\
    qmlRegisterType<CLASS>("Utils", 0, 0, #CLASS)

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/dirUtilities/main.qml"_qs);

    CLASS_REGISTER(SearchModel);
    CLASS_REGISTER(SearchModelSettings);
    CLASS_REGISTER(SearchQtLibModel);
    CLASS_REGISTER(SearchQtLibModelSettings);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
