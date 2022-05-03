#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include "gameboard.hh"
#include "numbertile.hh"
#include <vector>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <random>
#include <string>
#include <iostream>


const int TILESIZE = 80;
const Coords LEFT = {0, -1};
const Coords UP = {-1, 0};
const Coords RIGHT = {0, 1};
const Coords DOWN = {1, 0};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void new_tile();
    void action();
    void keyPressEvent(QKeyEvent* key);
    void configure();

private slots:
    void on_startPushButton_clicked();

private:
    Ui::MainWindow *ui;
    GameBoard gameboard;
    QGraphicsScene* scene;
    int target;
    bool game_running;
    bool ignore_cmds;

    struct Item {
        int number;
        const QString marker;
    };
    const std::vector<Item> Items =
    {
    {2,QString::number(2)},
    {4,QString::number(4)},
    {8,QString::number(8)},
    {16,QString::number(16)},
    {32,QString::number(32)},
    {64,QString::number(64)},
    {128,QString::number(128)},
    {256,QString::number(256)},
    {512,QString::number(512)},
    {1024,QString::number(1024)},
    {2048,QString::number(2048)},
    {0,""}
    };

    Item find_item(int item);
};
#endif // MAINWINDOW_HH
