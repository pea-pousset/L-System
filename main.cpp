#include "mainwindow.h"
#include <QApplication>

#include "lsystem.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(nullptr));

    MainWindow w;
    w.show();

    /* LSystem l;
    l.gen(2);
    std::vector<Segment> segments = l.getSegments();
    std::cout << "Segments: " << segments.size() << std::endl;
    for (unsigned i = 0; i < segments.size(); ++i)
    {
        std::cout << segments[i].origin << " ";
        std::cout << segments[i].direction + segments[i].origin << std::endl;
    } */

    return a.exec();
}
