#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QThreadPool>
#include <QProcess>
#include <QProcess>
#include "task.h"

class server : public QTcpServer
{
    Q_OBJECT

public:
    server( QObject );
    ~server();
    explicit server(QObject *parent = 0);
    void StartServer();
    int getActiveExeProcessCnt(), getActiveProcessCntTotal(),getActiveCompileProcessCnt();
    int getProcessCntTotal(),getProcessCntExeTotal(),getProcessCntCompileTotal();
    void setExeMaxThreadCount(int cnt);
    void setCompileMaxThreadCount(int cnt);
    void setConnMaxThreadCount(int cnt);
    void killActiveProcess(int id);
    QString serverPort,serverAddr,javaExecutePath,cppCompilerPath,cppCompilerBinDir,qtModules,qtCompilerPath,qtbinDir,qtDir,terminalPath,fortranCompilerPath,javaCompilerBinDir,javaCompilerPath;
    int maxExeProgramCount,maxCompProgramCount;

private:
    int activeExeProcessCnt, activeProcessCntTotal,activeCompileProcessCnt;
    int processCntTotal,processCntExeTotal,processCntCompileTotal;
    int count;
    QThreadPool *compilePool,*conPool;
    QSqlDatabase db;
    void connectToDB();
    QList<QProcess*> ProgramList;
    QVector<QStringList> ProgramParam;
    QList<QProcess*> CompileList;
    QVector<QStringList> CompileParam;


signals:
    void clientConnected();
    void activeProcessCntChange(int cnt);
    void activeCompileProcessCntChange(int cnt);
    void activeProcessCntTotalChange(int cnt);
    void processCntTotalChange(int cnt);
    void processCntExeTotalChange(int cnt);
    void processCntCompileTotalChange(int cnt);
    void activeProcessAdded(QString name,int id);
    void activeProcessRemoved(int id);
    void dbConnect(int status,QString error);
    void sendDebug(QString);

protected:
    void incomingConnection(int handle);
private slots:
    void increaseActiveExeProcessCnt();
    void decreaseActiveExeProcessCnt();
    void finishedExeProgram(int);
    void finishedCompProgram(int);
    void errorCompProgram(QProcess::ProcessError);
    void executeProgram(QStringList);
    void compileProgram(QStringList);

};

#endif // SERVER_H
