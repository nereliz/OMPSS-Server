#ifndef TASK_H
#define TASK_H

#include <QRunnable>
#include <QObject>
#include <QThread>
#include <QProcess>
#include <QByteArray>
#include <QtNetwork/QtNetwork>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtScript/QtScript>
#include <iostream>
#include <stdlib.h>
//#include <QMessageBox>
#include <QDateTime>
#include <QProcess>
#include <QUuid>
#include <QDir>

using namespace std;

class Task : public QObject, public QRunnable
{
    Q_OBJECT

public:
    Task();
    ~Task();
    void run();
    int id;
    int socketDescriptor;
    QString programType, binaryPath;
    QSqlDatabase cdb;
    QByteArray data;
    QString token, program_id;
    QStringList params;
    QDateTime dateTime;
    QString conName;
    QScriptEngine engine;
    QScriptValue sc;

signals:
    void requestExecute(QStringList);
    void requestCompile(QStringList);

};

#endif // TASK_H
