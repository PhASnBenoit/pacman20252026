#include "capp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CApp app(nullptr, argc, argv);

    return a.exec();
}
