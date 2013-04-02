#include "vrmath.h"
#include "server.h"

#include <iostream>
#include <QSettings>

using namespace std;

vrMath::vrMath()
{

    QMap<QString, QString> map;
    QString dir = QDir::current().absolutePath();
    QSettings settings( dir+"/config.ini", QSettings::IniFormat );
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
    myServer->makePath = map["makePath"];
    myServer->dbServer = map["dbServer"];
    myServer->dbName = map["dbName"];
    myServer->dbUser = map["dbUser"];
    myServer->dbPassword = map["dbPassword"];
    myServer->binaryPath = map["binaryPath"];

    connect(myServer, SIGNAL(activeProcessAdded(QString,int)), this, SLOT(addActiveProcess(QString,int)));
    connect(myServer, SIGNAL(activeProcessRemoved(int)), this, SLOT(remActiveProcess(int)));
    connect(myServer, SIGNAL(dbConnect(int,QString)), this, SLOT(dbStatus(int,QString)));
    myServer->StartServer();
}

vrMath::~vrMath()
{
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
       cout << "Database error: \n";
       cout << error.toStdString() << "\n";
    }
    else {
        cout<< "Connected to database.\n";
    }
}
