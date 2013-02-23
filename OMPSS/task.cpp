#include "task.h"

Task::Task()
{
    cout << "Task created\n";
}
Task::~Task()
{
}

void Task::run(){
    cout << "Task running\n";
    QTcpSocket socket;
    QString answerID,type,lang;
    socket.setSocketDescriptor(this->socketDescriptor);
    socket.waitForReadyRead();
    data=socket.readAll();
    dateTime = QDateTime::currentDateTime();
    QStringList params;
    QFile file;
    token=QUuid::createUuid().toString();
    token=token.left(token.size()-1);
    token=token.right(token.size()-1);
    conName=cdb.connectionName()+QString::number(id);
    {
        QSqlDatabase db=QSqlDatabase(QSqlDatabase::cloneDatabase(cdb,conName));
        db.open();
        QSqlQuery query(db);

        sc = engine.evaluate("(" + QString(data) + ")");
                      QScriptValueIterator it(sc);
                      while (it.hasNext()) {
                          it.next();
                          if (it.name()=="program")
                          {
                              program_id=it.value().toString();
                              token=token+"-"+program_id;
                              params<<program_id;
                              if (!params.at(0).isNull()||!params.at(0).isEmpty())
                              {
                                  query.exec("INSERT INTO math.answer (an_user_id, an_token, an_complete,  an_start_date, an_cp_id) VALUES (0, '"+token+"', 0,  '"+dateTime.toString("yyyy-MM-dd hh:mm:ss")+"', '"+program_id+"');");
                                  query.exec("SELECT @an_id:=LAST_INSERT_ID();");
                                  query.next();
                                  answerID = query.value(0).toString();
                                  params<<answerID;
                              }
                          }
                          if (it.name()=="exec")
                          {
                              type=it.value().toString();
                          }
                          if (it.name()=="lang")
                          {
                              lang=it.value().toString();
                              params<<lang;
                          }
                          if (it.value().isObject())
                          {
                              if (type=="execute")
                              {
                                    QScriptValueIterator sit(it.value());
                                    while (sit.hasNext()) {
                                          sit.next();
                                          if (sit.value().isObject())//--- jeigu tai failas
                                          {
                                               QScriptValueIterator sits(sit.value());
                                               while (sits.hasNext()) {
                                                       sits.next();
                                                       if (sits.value().toString()=="file")
                                                       {
                                                            sits.next();

                                                            query.exec("SELECT @pp_id:=pp_id FROM math.program_param_list,math.program_param WHERE ppl_pp_id=pp_id and ppl_cp_id="+program_id+" and pp_name='"+sits.name()+"'");
                                                            cout << program_id.toStdString() << " program id \n";
                                                            query.prepare("INSERT INTO math.answer_param_value (pv_value, pv_pp_id) VALUES (:val, @pp_id);");
                                                            query.bindValue(":val",sits.value().toString());
                                                            query.exec();
                                                            query.exec("SELECT @pv_id:=LAST_INSERT_ID();");
                                                            query.exec("INSERT INTO math.answer_param_list (anpl_an_id, anpl_pv_id) VALUES (@an_id, @pv_id)");
                                                            query.exec("SELECT BD_DATA FROM math.big_data where BD_ID="+sits.value().toString());
                                                            query.next();
                                                            if (lang=="Qt")
                                                            {
                                                                  file.setFileName(QDir::current().absolutePath()+"/"+program_id+"/release/"+sits.value().toString());
                                                                  params<<QDir::current().absolutePath()+"/"+program_id+"/release/"+sits.value().toString();
                                                            }
                                                            else
                                                            {
                                                               file.setFileName(QDir::current().absolutePath()+"/"+program_id+"/"+sits.value().toString());
                                                               params<<QDir::current().absolutePath()+"/"+program_id+"/"+sits.value().toString();
                                                            }
                                                               if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                                                               {
                                                                   QTextStream out(&file);
                                                                   out << query.value(0).toByteArray();
                                                               }
                                                               file.close();
                                                       }
                                               }
                                          }
                                          else {
                                              params<<sit.value().toString();
                                              query.exec("SELECT @pp_id:=pp_id FROM math.program_param_list,math.program_param WHERE ppl_pp_id=pp_id and ppl_cp_id="+program_id+" and pp_name='"+sit.name()+"'");
                                              query.prepare("INSERT INTO math.answer_param_value (pv_value, pv_pp_id) VALUES (:val, @pp_id);");
                                              query.bindValue(":val",sit.value().toString());
                                              query.exec();
                                              query.exec("SELECT @pv_id:=LAST_INSERT_ID();");
                                              query.exec("INSERT INTO math.answer_param_list (anpl_an_id, anpl_pv_id) VALUES (@an_id, @pv_id)");
                                          }
                                    }
                              }
                          }
                      }
    }
    QSqlDatabase::removeDatabase(conName);
    if (type=="execute")
    {
        if (params.at(0).isNull()||params.at(0).isEmpty())
        {
            socket.write("Nurodykite programa");
            socket.waitForBytesWritten();
        }
        else  emit this->requestExecute(params);
    }
    if (type=="compile")
    {
        if (params.at(0).isNull()||params.at(0).isEmpty())
        {
            socket.write("Nurodykite programa");
            socket.waitForBytesWritten();
        }
        else  emit this->requestCompile(params);
    }
   // qDebug()<<QString(data);
    socket.write(token.toLatin1());
    socket.flush();
    socket.waitForBytesWritten();
    socket.waitForDisconnected();
    socket.close();

}
