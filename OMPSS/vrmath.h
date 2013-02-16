#ifndef VRMATH_H
#define VRMATH_H

#include "server.h"


class vrMath : public QObject
{
    Q_OBJECT

public:
    explicit vrMath();
    ~vrMath();

private:
    int i;
    server *myServer;
   // void done();

public slots:
    void done();
    void changeActiveCompileProcessCnt(int);
    void changeProcessCntCompileTotal(int);
    void changeActiveProcessCnt(int cnt);
    void changeProcessCntTotal(int cnt);
    void changeProcessExeCntTotal(int cnt);
    void addActiveProcess(QString name,int id);
    void remActiveProcess(int id);
    void killActiveProcess();
    void dbStatus(int status,QString error);
    void debug(QString);
};

#endif // VRMATH_H
