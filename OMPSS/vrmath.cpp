#include "vrmath.h"
#include "server.h"

#include <iostream>
#include <QSettings>

using namespace std;

vrMath::vrMath()
{

    QMap<QString, QString> map;

    QSettings settings( "config.ini", QSettings::IniFormat );
    settings.beginGroup("user");
    foreach( const QString &childKey, settings.allKeys() )
        map.insert( childKey, settings.value( childKey ).toString() );
    cout<< "Server Starting...  \n";

    myServer=new server();
    myServer->serverAddr=map["serverAddress"];
    myServer->serverPort=map["serverPort"];
    myServer->javaExecutePath=map["javaExecutePath"];
    myServer->javaCompilerPath=map["javaCompilerPath"];
    myServer->javaCompilerBinDir=map["javaCompilerBinDir"];
    myServer->cppCompilerPath=map["cppCompilerPath"];
    myServer->cppCompilerBinDir=map["cppCompilerBinDir"];
    myServer->qtModules=map["qtModules"];
    myServer->qtCompilerPath=map["qtCompilerPath"];
    myServer->qtDir=map["qtDir"];
    myServer->qtbinDir=map["qtbinDir"];
    myServer->terminalPath=map["terminalPath"];
    myServer->fortranCompilerPath=map["fortranCompilerPath"];
    myServer->maxExeProgramCount=map["maxExeProgramCount"].toInt();
    myServer->maxCompProgramCount=map["maxCompProgramCount"].toInt();
    connect(myServer, SIGNAL(activeProcessCntChange(int)), this, SLOT(changeActiveProcessCnt(int)));
    connect(myServer, SIGNAL(processCntExeTotalChange(int)), this, SLOT(changeProcessExeCntTotal(int)));
    connect(myServer, SIGNAL(processCntTotalChange(int)), this, SLOT(changeProcessCntTotal(int)));
    connect(myServer, SIGNAL(processCntCompileTotalChange(int)), this, SLOT(changeProcessCntCompileTotal(int)));
    connect(myServer, SIGNAL(activeCompileProcessCntChange(int)), this, SLOT(changeActiveCompileProcessCnt(int)));
    connect(myServer, SIGNAL(activeProcessAdded(QString,int)), this, SLOT(addActiveProcess(QString,int)));
    connect(myServer, SIGNAL(activeProcessRemoved(int)), this, SLOT(remActiveProcess(int)));
    connect(myServer, SIGNAL(dbConnect(int,QString)), this, SLOT(dbStatus(int,QString)));
    connect(myServer, SIGNAL(sendDebug(QString)), this, SLOT(debug(QString)));
    myServer->StartServer();
}

vrMath::~vrMath()
{
}
void vrMath::done()
{
    i++;
    cout << "nonce \n";
    //return "Completed tasks: " + QString::number(i) + "\n";
}
void vrMath::changeActiveProcessCnt(int cnt)
{
    //return "Active processes: " +  QString::number(cnt) + "\n";
}
void vrMath::changeActiveCompileProcessCnt(int cnt)
{
    //return "Active compiles: " +  QString::number(cnt) + "\n";
}
void vrMath::changeProcessCntCompileTotal(int cnt)
{
    //return "Compiling + que compile procesese" +  QString::number(cnt) + "\n";
}
void vrMath::changeProcessCntTotal(int cnt)
{
      //return "Running + que compile procesese" +  QString::number(cnt) + "\n";
}
void vrMath::changeProcessExeCntTotal(int cnt)
{
      //return "Executible + que compile procesese" +  QString::number(cnt) + "\n";
}
void vrMath::addActiveProcess(QString name,int id)
{
    //ui->activeProcess->addItem(name,id);
}
void vrMath::remActiveProcess(int id)
{
    //ui->activeProcess->removeItem(ui->activeProcess->findData(id));
}
void vrMath::killActiveProcess()
{
    //myServer->killActiveProcess(ui->activeProcess->itemData(ui->activeProcess->currentIndex()).toInt());
    //this->ui->activeProcess->removeItem(this->ui->activeProcess->currentIndex());
}
void vrMath::dbStatus(int status, QString error)
{
    if (status<0) {
       // ui->textEdit->append("Database error: ");
       // ui->textEdit->append(error);
    }
    else {
        //ui->textEdit->append("Connected to database");
    }
}
void vrMath::debug(QString text)
{
    //ui->textEdit->append(text);
}
