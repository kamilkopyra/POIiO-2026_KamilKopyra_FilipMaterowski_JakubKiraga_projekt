#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSqlDatabase>
#include <QSqlError>
#include <QCoreApplication>
#include <QDebug>

bool initDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbPath = QString(PROJECT_PATH) + "/coffemachine.db";
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Blad otwarcia bazy danych:" << db.lastError().text();
        return false;
    }

    qDebug() << "Udalo sie polaczyc z baza danych!";
    return true;
}

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    initDatabase();

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Qt_CoffeMachine_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}
