#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QFileSystemWatcher>
#include <fstream>
#include <iostream>

using std::ifstream;
using std::string;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
public slots:
    void updateSlot();
private:
    Ui::MainWindow *ui;
    QFileSystemWatcher watcher;
    QImage* images;
    int imageCount;
    int cardCount;
    int CountImageFiles();
    void LoadImageFiles();
    void ReadAndPrintPlayerStats(ifstream& inputFile, QPainter& painter, int posX, int posY);
    void ReadAndPrintCards(ifstream &inputFile, QPainter &painter, int numberOfCards, int posX, int posY, int sizeX, int sizeY);
};
#endif // MAINWINDOW_H
