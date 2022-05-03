/*  COMP.CS.110 Project: Numbers_gui
 *
 * Pääikkuna missä on ohjelman graafiset komponentit  ja toiminnot
 * Lisää pelistä osoitteessa instruction.txt
 *
 * Ohjelman kirjoittaja ( Täytä omilla tiedoillasi )
 * Nimi: Elias Nikkinen
 * Opiskelijanumero: 50497168
 * Käyttäjätunnus: shelni
 * E-Mail: elias.nikkinen@tuni.fi
 *
 * */
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include "gameboard.hh"
#include "numbertile.hh"
#include <vector>
#include <random>
#include <string>
#include <QKeyEvent>
#include <QFont>
#include <QGraphicsTextItem>
#include <QPoint>
#include <QLabel>
#include <QTimer>

const int TILESIZE = 100;
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
    void hide_labels();
    void win_condition();
    void lose_condition();
    void enable_stuff();
    void disable_stuff();
    void set_target();
    void timer_clear();
    void time_counter();

private slots:
    void on_StartpushButton_clicked();
    void on_ExitpushButton_clicked();
    void on_RestartpushButton_clicked();
    void on_GamepausepushButton_clicked();


private:
    Ui::MainWindow *ui;
    GameBoard gameboard;
    QGraphicsScene* scene;
    int target;
    bool game_running;
    bool ignore_cmds;
    QTimer* timer;

    struct Item {
        int number;
        const QString marker;

        QColor color;
    };
    std::vector<Item> Items =
    {
        {2,QString::number(2),QColor(255, 235, 235)},
        {4,QString::number(4),QColor(255, 204, 204)},
        {8,QString::number(8),QColor(255, 133, 133)},
        {16,QString::number(16),QColor(255, 61, 61)},
        {32,QString::number(32),QColor(255, 15, 15)},
        {64,QString::number(64),QColor(189, 194, 255)},
        {128,QString::number(128),QColor(140, 150, 255)},
        {256,QString::number(256),QColor(84, 98, 255)},
        {512,QString::number(512),QColor(38, 56, 255)},
        {1024,QString::number(1024),QColor(0, 13, 150)},
        {2048,QString::number(2048),QColor(208, 0, 255)},
        {0,"",QColor(255,255,255)}
    };
    QColor fill = QColor(0, 0, 0);

    Item find_item(int item);
};
#endif // MAINWINDOW_HH
