#include "server.h"
#include <QtSql/QSqlDatabase>
#include <QDebug>

server::server(QObject *parent) :
    QTcpServer(parent)
{
     this->conPool = new QThreadPool();
     conPool->setMaxThreadCount(2);
     activeExeProcessCnt=0;
     activeProcessCntTotal=0;
     activeCompileProcessCnt=0;
     processCntTotal=0;
     processCntExeTotal=0;
     processCntCompileTotal=0;
     count=0;
}

server::~server()
{
}

void server::StartServer()
{
    if( this->serverAddr == "%" )
    {
        this->listen( QHostAddress::Any,this->serverPort.toInt() );
    }
    else
    {
        QHostAddress hostadd(this->serverAddr);
        this->listen(hostadd,this->serverPort.toInt());
    }

    if( this->isListening() )
        cout << "Port listening on " << this->serverAddr.toStdString() << ":" << this->serverPort.toStdString() <<"\n";
    else
    {
        cout << "Port listening failed\n";
    }
    this->connectToDB();
}
void server::incomingConnection(int handle)
{
    count++;
    Task *e= new Task();
    e->socketDescriptor=handle;
    e->id=count;
    e->programType="C++";
    e->cdb=db;
    connect(e, SIGNAL(requestExecute(QStringList)),this , SLOT(executeProgram(QStringList)),Qt::QueuedConnection);
    connect(e, SIGNAL(requestCompile(QStringList)),this , SLOT(compileProgram(QStringList)),Qt::QueuedConnection);
    conPool->start(e);
}
void server::setExeMaxThreadCount(int cnt)
{
     this->maxExeProgramCount=cnt;
}
void server::setCompileMaxThreadCount(int cnt)
{
     this->maxCompProgramCount=cnt;
}
void server::setConnMaxThreadCount(int cnt)
{
     this->conPool->setMaxThreadCount(cnt);
}
int server::getActiveCompileProcessCnt()
{
    return this->activeCompileProcessCnt;
}
int server::getActiveExeProcessCnt()
{
    return this->activeExeProcessCnt;
}
int server::getActiveProcessCntTotal()
{
    return this->activeProcessCntTotal;
}
int server::getProcessCntCompileTotal()
{
    return this->processCntCompileTotal;
}
int server::getProcessCntExeTotal()
{
    return this->processCntExeTotal;
}
int server::getProcessCntTotal()
{
    return this->processCntTotal;
}
void server::increaseActiveExeProcessCnt()
{
     this->activeExeProcessCnt++;
     emit activeProcessCntChange(activeExeProcessCnt);
}
void server::decreaseActiveExeProcessCnt()
{
    this->activeExeProcessCnt--;
    emit activeProcessCntChange(activeExeProcessCnt);
    this->processCntTotal--;
    emit processCntTotalChange(this->processCntTotal);
    this->processCntExeTotal--;
    emit processCntExeTotalChange(this->processCntExeTotal);
}
void server::killActiveProcess(int id)
{
    for (int i=0; i<ProgramParam.size(); i++)
    {
        if (ProgramParam.at(i).at(1).toInt()==id)
        {
            if (ProgramList.at(i)->state()==QProcess::Running)
            {
                ProgramList.at(i)->kill();

            }
        }
    }
    for (int i=0; i<CompileParam.size(); i++)
    {
        if (CompileParam.at(i).at(1).toInt()==id)
        {
            if (CompileList.at(i)->state()==QProcess::Running)
            {
                CompileList.at(i)->kill();
            }
        }
    }
}
void server::connectToDB()
{
        int status=0;
        QString error="";
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName( this->dbServer );
        db.setDatabaseName( this->dbName );
        db.setUserName( this->dbUser );
        db.setPassword(this->dbPassword );
        if (!db.open()) {
         error=db.lastError().text();
         status=-1;
        }
        emit dbConnect(status,error);
}
void server::executeProgram(QStringList list)
{
    QString name="binary "+list[1]+" "+list[0];
    QString str,path;
    QDir progPath;
    QString dir = QDir::current().absolutePath()+"/binaries/"+list[0];
    QString lang = list.at(2);
    if (list.at(2)=="Java")
    {
        QDir myDir( dir );
        QStringList filter;
        QString prName="";
        filter.append("*.class");
        filter=myDir.entryList(filter);
        if (filter.size()>0)
            prName=filter.at(0).split(".").at(0);

        str="/usr/bin/sudo "+this->javaExecutePath+" "+prName+ " test ";//+javaClass;
        path= dir+"/"+prName+".class";
    }
    else
    {
        str=dir+"/"+list[0];
        path=str;
    }
    if (progPath.exists(path))
    {
        this->processCntTotal++;
        this->processCntExeTotal++;
        emit processCntExeTotalChange(this->processCntExeTotal);
        emit processCntTotalChange(this->processCntTotal);
        this->ProgramParam.append(list);
        list.pop_front();
        list.pop_front();
        list.pop_front();
        QProcess *proc=new QProcess(this);
        this->ProgramList.append(proc);
        connect(ProgramList.last(), SIGNAL(finished(int)),this , SLOT(finishedExeProgram(int)));
        if (activeExeProcessCnt<maxExeProgramCount)
         {
            if( lang=="Java" )
            {
                ProgramList.last()->setWorkingDirectory( dir );
                foreach( QString arg, list)
                    str += " " + arg;
                ProgramList.last()->start(str);
            }
            else
                ProgramList.last()->start(str,list);

            increaseActiveExeProcessCnt();
            emit activeProcessAdded(name,ProgramParam.last().at(1).toInt());
         }
    }
}
void server::finishedExeProgram(int i)
{
    QString dir;
    QString lang;
    int j=ProgramList.indexOf((QProcess*)sender());
    QSqlQuery query(db);
    QDateTime dateTime = QDateTime::currentDateTime();
    query.prepare("UPDATE math.answer  SET  an_complete = 1, an_answer = :an,  an_complete_date = :date  WHERE an_id=:id");
    query.bindValue(":an", QString(ProgramList.at(j)->readAllStandardError())+QString(ProgramList.at(j)->readAllStandardOutput()));
    query.bindValue(":date",dateTime.toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":id", ProgramParam.at(j).at(1));
    query.exec();
    ProgramList.takeAt(j)->deleteLater();
    emit activeProcessRemoved(ProgramParam.at(j).at(1).toInt());
    ProgramParam.remove(j);
    QStringList list;
    this->decreaseActiveExeProcessCnt();
    if (activeExeProcessCnt<maxExeProgramCount)
    {
        for (int k=0; k<ProgramList.size(); k++)
        {
              if (ProgramList.at(k)->state()==QProcess::NotRunning)
              {
                  list=ProgramParam.at(k);
                  dir = QDir::current().absolutePath()+"/binaries/"+list[0];
                  lang = list.at(2);
                  int currnetID=list.at(1).toInt();
                  QString name="binary "+list[1]+" "+list[0];
                  QString str;
                  if (list.at(2)=="Java")
                  {
                     QDir myDir( dir );
                     QStringList filter;
                     QString prName="";
                     filter.append("*.class");
                     filter=myDir.entryList(filter);
                     if (filter.size()>0)
                         prName=filter.at(0).split(".").at(0);

                     str="/usr/bin/sudo "+this->javaExecutePath+" "+prName+ " test ";//+javaClass;
                  }
                  else
                      str=dir+"/"+list[0];

                  list.pop_front();
                  list.pop_front();
                  list.pop_front();
                  if( lang=="Java" )
                  {
                      ProgramList.at(k)->setWorkingDirectory( dir );
                      foreach( QString arg, list)
                          str += " " + arg;
                      ProgramList.at(k)->start(str);
                  }
                  else
                      ProgramList.at(k)->start(str,list);

                  emit activeProcessAdded(name,currnetID);
                  emit increaseActiveExeProcessCnt();
                  break;
              }
         }
    }
}
void server::compileProgram(QStringList list)
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    this->processCntCompileTotal++;
    emit this->processCntCompileTotalChange(processCntCompileTotal);
    this->processCntTotal++;
    emit this->processCntTotalChange(processCntTotal);
    this->CompileParam.append(list);
    QString str;
    QString script;
    QString dir=QDir::current().absolutePath() + "/binaries/" + list.at(0);
    QString sfile = dir + "/" +list.at(0);
    QSqlQuery query(db);
    QString prname=list.at(0);
    QDir().mkdir("binaries");
    QDir().mkdir("binaries/" + prname);

    if (list.at(2)=="C++")
    {
        env.insert("PATH", env.value("Path") + ";"+this->cppCompilerBinDir);
        QFile file(sfile+".cpp");
        query.exec("SELECT  cp_code FROM math.costum_program WHERE  cp_id="+list.at(0)+" order by cp_created desc");
        if (query.next())
        {
            script=query.value(0).toString();
        }
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                   cout << "File opening failed \n";
        QTextStream out(&file);
        out << script << "\n";
        file.close();
        str= "/usr/bin/sudo " +  this->cppCompilerPath + " -Wall -W " + sfile + ".cpp " + " -o " + sfile;
    }
    if (list.at(2)=="Java")
    {
        env.insert("PATH", env.value("Path") + ";"+javaCompilerBinDir);
        QFile file(sfile+".java");
        query.exec("SELECT  cp_code FROM math.costum_program WHERE  cp_id="+list.at(0)+" order by cp_created desc");
        if (query.next())
        {
            script=query.value(0).toString();
        }
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                   qDebug()<<"Neatidare";
        QTextStream out(&file);
        out << script << "\n";
        file.close();
        str="/usr/bin/sudo "+javaCompilerPath+" " + sfile + ".java";
    }
    else if (list.at(2)=="Qt")
    {
        QFile file(sfile+".cpp");
        query.exec("SELECT  cp_code FROM math.costum_program WHERE  cp_id="+list.at(0)+" order by cp_created desc");
        if (query.next())
        {
            script=query.value(0).toString();
        }
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                   qDebug()<<"Neatidare";
        QTextStream out(&file);
        out << script << "\n";
        file.close();

        str = "/usr/bin/sudo " + QDir::current().absolutePath() + "/qtCompiler.sh " + dir;
        str += " " + this->qtCompilerPath + " " + this->makePath;

    }
    else if (list.at(2)=="Fortran")
    {
        QFile file(sfile+".f");
        query.exec("SELECT  cp_code FROM math.costum_program WHERE  cp_id="+list.at(0)+" order by cp_created desc");
        if (query.next())
        {
            script=query.value(0).toString();
        }
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                   qDebug()<<"Neatidare";
        QTextStream out(&file);
        out << script << "\n";
        file.close();
        str="/usr/bin/sudo "+this->fortranCompilerPath + " " + sfile + ".f -o " + sfile;
    }
    QProcess *proc=new QProcess(this);
    CompileList.append(proc);
    connect(CompileList.last(), SIGNAL(finished(int)),this , SLOT(finishedCompProgram(int)));
    connect(CompileList.last(), SIGNAL(error(QProcess::ProcessError)),this , SLOT(errorCompProgram(QProcess::ProcessError)));
     QString name="comp "+list[1]+" "+list[0];
     if (activeCompileProcessCnt<2)
      {
         if (CompileParam.last().at(2)=="C++")
         {
            CompileList.last()->setProcessEnvironment(env);
            CompileList.last()->start(str);
         }
         else if (CompileParam.last().at(2)=="Java")
         {
            CompileList.last()->setProcessEnvironment(env);
            CompileList.last()->start(str);
         }
         else if (CompileParam.last().at(2)=="Fortran")
         {
            CompileList.last()->start(str);
         }
         else if(CompileParam.last().at(2)=="Qt")
         {
            CompileList.last()->start(str);
         }
         else CompileList.last()->start(str);
         this->activeCompileProcessCnt++;
         this->activeCompileProcessCntChange(activeCompileProcessCnt);
         emit activeProcessAdded(name,CompileParam.last().at(1).toInt());
      }
}
void server::finishedCompProgram(int i)
{
    int j=CompileList.indexOf((QProcess*)sender());
    QSqlQuery query(db);
    QDateTime dateTime = QDateTime::currentDateTime();
    QString data=CompileList.last()->readAllStandardOutput();
    data=CompileList.last()->readAllStandardError();
    query.exec("UPDATE math.answer  SET  an_complete = 1, an_answer = '"+data.replace(QDir::current().absolutePath(),"").replace("'","\"")+"',  an_complete_date = '"+dateTime.toString("yyyy-MM-dd hh:mm:ss")+"'  WHERE an_id="+CompileParam.at(j).at(1));
    CompileList.takeAt(j)->deleteLater();
    emit activeProcessRemoved(CompileParam.at(j).at(1).toInt());
    CompileParam.remove(j);
    QStringList list;
    this->activeCompileProcessCnt--;
    emit activeCompileProcessCntChange(activeCompileProcessCnt);
    this->processCntTotal--;
    emit processCntTotalChange(this->processCntTotal);
    this->processCntCompileTotal--;
    emit processCntCompileTotalChange(this->processCntCompileTotal);

    if (activeCompileProcessCnt<2)
    {
        for (int k=0; k<CompileList.size(); k++)
          {
              if (CompileList.at(k)->state()==QProcess::NotRunning)
              {
                  list=CompileParam.at(k);
                  int currnetID=list.at(1).toInt();
                  QString name="comp "+list[1]+" "+list[0];
                  QString str;
                  QString dir=QDir::current().absolutePath() + "/binaries/" + list.at(0);
                  QString sfile = dir + "/" +list.at(0);
                  if (list.at(2)=="C++")
                  {
                      QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
                      env.insert("PATH", env.value("Path") + ";"+this->cppCompilerBinDir);
                      str = "/usr/bin/sudo " + this->cppCompilerPath + " -Wall -W " + sfile + ".cpp " + " -o " + sfile;
                      CompileList.at(k)->setProcessEnvironment(env);
                      CompileList.at(k)->start(str);
                  }
                  if (list.at(2)=="Java")
                  {
                      QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
                      env.insert("PATH", env.value("Path") + ";"+javaCompilerBinDir);
                      str="/usr/bin/sudo "+javaCompilerPath+" " + sfile + ".java";
                      CompileList.at(k)->setProcessEnvironment(env);
                      CompileList.at(k)->start(str);
                  }
                  else if (list.at(2)=="Fortran")
                  {
                      str="/usr/bin/sudo "+this->fortranCompilerPath + " " + sfile + ".f -o " + sfile;
                      CompileList.at(k)->start(str);
                  }
                  else if (list.at(2)=="Qt")
                  {
                       str = "/usr/bin/sudo " + QDir::current().absolutePath() + "/qtCompiler.sh " + dir;
                       str += " " + this->qtCompilerPath + " " + this->makePath;
                       CompileList.at(k)->start(str);
                  }

                  emit activeProcessAdded(name,currnetID);
                  this->activeCompileProcessCnt++;
                  this->activeCompileProcessCntChange(activeCompileProcessCnt);
                  break;
              }
          }
    }
}

void server::errorCompProgram(QProcess::ProcessError ecode)
{
    cout<< "Error catched";
}
