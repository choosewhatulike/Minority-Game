#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQuickView>
#include <QQmlContext>
#include "enviroment.h"

int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    EnvControl envc;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("envControl", &envc);
    engine.load(QUrl(QStringLiteral("qrc:/frontend/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
