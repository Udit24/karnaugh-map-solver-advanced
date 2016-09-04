#include "inputnoofvariableswindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   InputNoOfVariablesWindow w;
    w.show();

    return a.exec();
}
