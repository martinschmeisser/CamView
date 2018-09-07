#include "camview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CamView w;
    w.show();

    return a.exec();
}
