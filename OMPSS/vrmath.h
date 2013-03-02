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

public slots:
    void addActiveProcess(QString name,int id);
    void remActiveProcess(int id);
    void killActiveProcess();
    void dbStatus(int status,QString error);
};

#endif // VRMATH_H
