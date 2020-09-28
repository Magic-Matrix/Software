#include "VideoWiget.h"
#include "AcctressWiget.h"

#include <QApplication>
#include <QDebug>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    AcctressWiget w;
    w.show();
    return a.exec();
}

