#ifndef VRMATH_H
#define VRMATH_H

#include <QMainWindow>
#include "server.h"

namespace Ui {
    class vrMath;
}

class vrMath : public QMainWindow
{
    Q_OBJECT

public:
    explicit vrMath(QWidget *parent = 0);
    ~vrMath();

private:
    Ui::vrMath *ui;
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
