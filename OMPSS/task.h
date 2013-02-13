#ifndef TASK_H
#define TASK_H

#include <QRunnable>
#include <QObject>
#include <QThread>
#include <QProcess>
#include <QByteArray>
#include <QtNetwork>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtScript>
#include <stdlib.h>
#include <QMessageBox>
#include <QDateTime>
#include <QProcess>
#include <QUuid>
#include <QDir>

class Task : public QObject, public QRunnable
{
    Q_OBJECT

public:
    Task();
    void run();
    int id;
    int socketDescriptor;
    QString programType;
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
