#include <cstdio>
#include <dirent.h>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include "main_window.h"
#include "./ui_mainwindow.h"
#include "../image_files_enum.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cardCount = 1;

    //Load the games sprites.
    imageCount = CountImageFiles();
    images = new QImage[imageCount];
    LoadImageFiles();

    //Watch for changes in the input.txt file. If the contents of the file change, call the updateSlot method.
    watcher.addPath(INPUT_PATH);
    QObject::connect(&watcher, SIGNAL(fileChanged(const QString&)), this, SLOT(updateSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Main logic. Updated whenever the input.txt file changes.
//First prints the enemy players.
//Next the main player's stats.
//Next the main player's cards.
void MainWindow::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    if(imageCount > 0)
    {
        try
        {
            QPainter painter(this);
            QRectF backgroundTarget(0,0,1920,1080);
            ifstream inputFile;
            string word;
            painter.drawImage(backgroundTarget, images[IMAGE_FILE_ID::game_board]);
            int numberOfProvinces, numberOfCardsInHand;
            int enemyXStart = 10;
            int cardCount = 0;

            painter.setPen(Qt::black);
            painter.setFont(QFont("Arial", 11));
            inputFile.open(INPUT_PATH);
            while(inputFile >> word)
            {
                if(word == "PLAYER") //enemy player
                {
                    ReadAndPrintPlayerStats(inputFile, painter, enemyXStart, 20);
                    //The cards in the enemy's hand are not visible to the main player.
                    inputFile >> word;
                    numberOfCardsInHand = stoi(word);
                    for(int i = 0; i < numberOfCardsInHand; i++)
                    {
                        QRectF target(enemyXStart + i * 78, 30, 64, 128);
                        painter.drawImage(target, images[IMAGE_FILE_ID::green_card_back].scaledToWidth(64, Qt::TransformationMode::SmoothTransformation));
                    }
                    //The provinces are visible to all (if they are revealed, but we don't care about that here).
                    inputFile >> word;
                    numberOfProvinces = stoi(word);
                    painter.setFont(QFont("Arial", 9)); //change the pen because the cards are small.
                    ReadAndPrintCards(inputFile, painter, numberOfProvinces, enemyXStart, 186, 64, 128);
                    painter.setFont(QFont("Arial", 11)); //reset the pen
                    //Calculate the horizontal position (where to draw) of the next enemy.
                    if(numberOfProvinces < numberOfCardsInHand)
                    {
                        enemyXStart = enemyXStart + numberOfCardsInHand * 78;
                    }else
                    {
                        enemyXStart = enemyXStart + numberOfProvinces * 78;
                    }
                    enemyXStart += 60;
                    continue;
                }else if(word == "THIS_PLAYER")
                {
                    ReadAndPrintPlayerStats(inputFile, painter, 10, this->size().height() - 340);
                    inputFile >> word;
                    numberOfCardsInHand = stoi(word);
                    inputFile >> word;
                    numberOfProvinces = stoi(word);
                    ReadAndPrintCards(inputFile, painter, numberOfProvinces + numberOfCardsInHand, 10, this->size().height() - 330, 160, 320);
                }else
                {
                    for(int i = 0; i < word.length(); i++)
                    {
                        inputFile.unget();
                    }
                    ReadAndPrintCards(inputFile, painter, 3, 10, this->size().height() - 330, 160, 320); //strongholds, TODO 3 is a magic number
                }
            }
            inputFile.close();
        }catch(...){
            //To-Do. Investigate crash. The program is crashing because of an error in stoi(). Unable to reproduce reliably. There is probably some problem with the passing of ifstreams in functions.
        }
    }else
    {
        imageCount = CountImageFiles();
        images = new QImage[imageCount];
        LoadImageFiles();
    }
}

//Print the next players stats (as read from the inputFile).
void MainWindow::ReadAndPrintPlayerStats(ifstream& inputFile, QPainter& painter, int posX, int posY)
{
    string word;
    int honour, armyPower, income;
    inputFile >> word;
    honour = stoi(word);
    inputFile >> word;
    armyPower = stoi(word);
    inputFile >> word;
    income = stoi(word);
    word = "Player: (Honour: " + to_string(honour) + ", Army power: " + to_string(armyPower) + ", Income: " + to_string(income) + ")";
    painter.drawText(posX, posY, QString::fromStdString(word));
}

//Print the player's cards.
void MainWindow::ReadAndPrintCards(ifstream& inputFile, QPainter& painter, int numberOfCards, int posX, int posY, int sizeX, int sizeY)
{
    string word;
    for(int i = 0; i < numberOfCards; i++)
    {
        inputFile >> word; //read the id of the card (used to find the card in the 'images' array)
        QRectF target(posX + i * sizeX * 1.05, posY, sizeX, sizeY); //the position to draw the card
        painter.drawImage(target, images[stoi(word)].scaledToWidth(sizeX, Qt::TransformationMode::SmoothTransformation)); //draw the card
        inputFile >> word;
        for(int j = 0; ; inputFile >> word, j++)
        {
            if(word == "END")
                break;
            QRectF target2(posX + sizeX * 0.05 + i * sizeX * 1.05, posY + sizeY * 0.47 + j * 15, sizeX, sizeY);
            string toPrint = word;
            inputFile >> word;
            toPrint += word;
            painter.drawText(target2, QString::fromStdString(toPrint));
        }
    }
}

//Count the regular files (image files in this case) in the images folder.
int MainWindow::CountImageFiles()
{
    struct dirent *de;  // Pointer for directory entry
    int count = 0;
    DIR *dr = opendir(IMAGES_PATH);

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return 0;
    }
    while ((de = readdir(dr)) != NULL)
    {
        if(de->d_type == DT_REG)    //if it's a regular file
            count++;
    }
    closedir(dr);
    return count;
}

/* Load the images to the images(QImage[]) array. Go through every image file in the 'images' folder, read the position of the image from the enumeration in 'image_files_enum.h'
 * and then store the image in the images(QImage[]) array (at the index you just read).
 *
 * e.g.     card1 = 2 //in image_files_enum.h
 *          images[2] = card1.png
 *
 *
 * Notes:   1. Only works for .png image files
 *          2. The enumeration in image_files_enum.h has a very specific format -> name = int ,
 */
void MainWindow::LoadImageFiles()
{
    int count = 0, id = -1;
    string word;
    struct dirent *de;  // Pointer for directory entry
    DIR *dr = opendir(IMAGES_PATH);
    ifstream enumFile;

    if (dr == NULL)
    {
        cout << "Could not open current directory" << endl;
        return;
    }
    while ((de = readdir(dr)) != NULL)  //for every entry
    {
        if(de->d_type == DT_REG)    //if it's a regular file
        {
            string image_path = string(IMAGES_PATH) + "/"+ string(de->d_name); //filepath to the imagefile
            enumFile.open(IMAGE_ENUM_PATH);  //find the enumeration (id) of the imagefile
            if(enumFile.is_open() == false)
            {
                cout << "Could not open the IMAGE_ENUM_PATH file. Press any button to terminate the program." << endl;
                getchar();
                exit(-1);
            }
            while(enumFile >> word)
            {
                if(word + ".png" == string(de->d_name)) //ONLY WORKS FOR .png IMAGES
                {
                    enumFile >> word; //ignore the '=' sign
                    enumFile >> word; //reads the id(int) value
                    id = stoi(word);
                    break;
                }
            }
            enumFile.close();
            if(id == -1)
            {
                cout << "Could not find image-id(enumeration). Press any button to terminate the program." << endl;
                getchar();
                exit(-1);
            }

            bool b = images[id].load(QString::fromStdString(image_path));
            if(b == false)
            {
                cout << image_path << endl;
            }
            count++;
        }
    }
    closedir(dr);
}

//Used for controlling the program.
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R)
    {
        cardCount++;
        this->update(); //calls paintEvent
    }
}

//Called when the contents of the input.txt file change.
void MainWindow::updateSlot()
{
    this->update(); //update the UI
    if(watcher.files().contains(INPUT_PATH) == false) //for some reason the watcher points to no file after calling this method, add the file again
    {
        watcher.addPath(INPUT_PATH);
    }
}


