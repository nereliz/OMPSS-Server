#include <QCoreApplication>
#include <vrmath.h>
#include <iostream>
using namespace std;

int main( int argc, char *argv[] )
{
    QCoreApplication a(argc, argv);
    vrMath *vm = new vrMath();

    char c;

    do{
        cin >> c;
        if( c == 't' )
            vm->done();

        cout << c << '\n';
    }while( c != 'x' );

    return a.exec();
}
