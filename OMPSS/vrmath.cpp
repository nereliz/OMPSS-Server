#include "vrmath.h"
#include "ui_vrmath.h"
#include <QDomDocument>

vrMath::vrMath(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::vrMath)
{
    ui->setupUi(this);
    //Read config;
     ui->textEdit->append("Server: ");

      QMap<QString, QString> map;
    QDomDocument doc("xml");

    QFile file("config.xml");
    if (!file.open(QIODevice::ReadOnly))
    {
        ui->textEdit->append("Error: missing config.xml");
        return;
    }
    if (!doc.setContent(&file)) {
        ui->textEdit->append("Error: missing config.xml3");
        file.close();
        return;
    }
    file.close();
    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            ui->textEdit->append(e.tagName()+"="+e.text());
            map.insert(e.tagName(),e.text());
        }
        n = n.nextSibling();
    }
   // ui->textEdit->append(docElem.elementsByTagName("serverPort").at(0).toElement().text());

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
    delete ui;
}
void vrMath::done()
{
    i++;
    ui->textEdit->setText(QString::number(i));
}
void vrMath::changeActiveProcessCnt(int cnt)
{
   ui->prcCntActiveExe->setText(QString::number(cnt));
}
void vrMath::changeActiveCompileProcessCnt(int cnt)
{
   ui->prcCntCompAct->setText(QString::number(cnt));
}
void vrMath::changeProcessCntCompileTotal(int cnt)
{
   ui->prcCntCmpTotal->setText(QString::number(cnt));
}
void vrMath::changeProcessCntTotal(int cnt)
{
   ui->prcCntTotal->setText(QString::number(cnt));
}
void vrMath::changeProcessExeCntTotal(int cnt)
{
   ui->prcCntExeTotal->setText(QString::number(cnt));
}
void vrMath::addActiveProcess(QString name,int id)
{
    ui->activeProcess->addItem(name,id);
}
void vrMath::remActiveProcess(int id)
{
    ui->activeProcess->removeItem(ui->activeProcess->findData(id));
}
void vrMath::killActiveProcess()
{
    myServer->killActiveProcess(ui->activeProcess->itemData(ui->activeProcess->currentIndex()).toInt());
    this->ui->activeProcess->removeItem(this->ui->activeProcess->currentIndex());
}
void vrMath::dbStatus(int status, QString error)
{
    if (status<0) {
        ui->textEdit->append("Database error: ");
        ui->textEdit->append(error);
    }
    else {
        ui->textEdit->append("Connected to database");
    }
}
void vrMath::debug(QString text)
{
    ui->textEdit->append(text);
}
