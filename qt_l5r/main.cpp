#include "main_window.h"

#include <QTextStream>
#include <QApplication>
#include <QFileSystemWatcher>
#include <QLabel>
#include <QScrollArea>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //Scrolling
    QScrollArea scrollArea;
    scrollArea.setBackgroundRole(QPalette::Dark);
    scrollArea.setWidgetResizable(true);

    //Watch input.txt file for changes.
    QFileSystemWatcher watcher;
    watcher.addPath("../qt_l5r/input.txt");

    //Update the graphics every time the input.txt file changes.
    QObject::connect(&watcher, SIGNAL(fileChanged(const QString&)), &w, SLOT(updateSlot()));

    //Scrolling and window stuff.
    w.setMinimumSize(1024,768);
    w.show();
    scrollArea.setWidget(&w);
    scrollArea.setMinimumSize(512, 512);
    scrollArea.show();

    return a.exec();
}
