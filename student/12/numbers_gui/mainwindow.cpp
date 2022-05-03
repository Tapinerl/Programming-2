/*  COMP.CS.110 Project: Numbers_gui
 *
 * Pääikkuna totetustiedosto missä kaikki toiminnot suoritetaan
 *
 * Ohjelman kirjoittaja ( Täytä omilla tiedoillasi )
 * Nimi: Elias Nikkinen
 * Opiskelijanumero: 50497168
 * Käyttäjätunnus: shelni
 * E-Mail: elias.nikkinen@tuni.fi
 *
 * */
#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , game_running(false)
    , ignore_cmds(false)

{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::time_counter);
}

MainWindow::~MainWindow()
{
    delete ui;
}
// Kutsuu new_value metodia Gameboard -luokasta
// tekee uuden laatan
void MainWindow::new_tile()
{
    gameboard.new_value();
}
// määrittää mitä tapahtuu kun siirretään pelin laattoja
void MainWindow::action()
{
    scene->clear();
    new_tile();
    configure();
}
// Käy läpi voitto ja häviö -tilanteet.
// käsittelee pelin toiminnallisuutta.
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(game_running)
    {
        if(!ignore_cmds)
        {
    if(event->key() == Qt::Key_W or
            event->key() == Qt::Key_Up)
    {
        if(gameboard.move(UP,target))
        {
            win_condition();
        }
    }
    else if(event->key() == Qt::Key_S or
            event->key() == Qt::Key_Down)
    {
        if(gameboard.move(DOWN,target))
        {
            win_condition();
        }
    }
    else if(event->key() == Qt::Key_D or
            event->key() == Qt::Key_Right)
    {
        if(gameboard.move(RIGHT,target))
        {
            win_condition();
        }
    }
    else if(event->key() == Qt::Key_A or
            event->key() == Qt::Key_Left)
    {
        if(gameboard.move(LEFT,target))
        {
            win_condition();
        }
    }
    else
    {
        return;
    }
    // kun pelilauta on täynnä
    if(gameboard.is_full()){
        lose_condition();
    }
    action();
    }
        else
        {
            event->ignore();
        }
    }
    else
    {
        event->ignore();
    }
}
// Luo peli-ikkunan jossa on laattojen numerot ja värit
void MainWindow::configure()
{
    for (int x = 0; x < SIZE; x++)
    {
        for (int y = 0; y < SIZE; y++)
        {
            QRectF square(y * TILESIZE, x * TILESIZE, TILESIZE, TILESIZE);
            std::pair <int,int> coordinates;
            coordinates = std::make_pair(x,y);
            Item value = find_item(gameboard.get_item(coordinates)->value());
            scene->addRect(square,fill, value.color);
            QGraphicsTextItem *text = scene->addText(value.marker);
            text->setPos(y * TILESIZE, x * TILESIZE);
            }
      }
}
// piilottaa etiketin pelin aikana
void MainWindow::hide_labels()
{
    ignore_cmds = false;
    ui->WinnerLabel->hide();
    ui->LoserLabel->hide();
    ui->PauseLabel->hide();
}
// Voiton ehto. Jossa tausta muuttuu vihreäksi kun peli on voitettu
void MainWindow::win_condition()
{
    timer->stop();
    ui->WinnerLabel->setText("You have won!");
    game_running = false;
    ui->WinnerLabel->setStyleSheet({"backround:green; color:white"});
    this->setStyleSheet({"background: green"});
    ui->graphicsView->setStyleSheet({"background: green"});
    ui->WinnerLabel->show();
}
// Häviön ehto. Jossa tausta muuttuu punaiseksi kun peli on hävitty
void MainWindow::lose_condition()
{
    timer->stop();
    ui->LoserLabel->setText("You have lost!");
    game_running = false;
    ui->WinnerLabel->setStyleSheet({"backround:red; color:white"});
    this->setStyleSheet({"background: red"});
    ui->graphicsView->setStyleSheet({"background: red"});
    ui->LoserLabel->show();
}
// kun painetaan pelin aloitus nappulaa
void MainWindow::on_StartpushButton_clicked()
{
    gameboard.init_empty();

    if(ui->SeedspinBox->value() != 0)
    {
        int seedvalue = ui->SeedspinBox->value();
        gameboard.fill(seedvalue);
    }
    else
    {
    int seedvalue = time(NULL);
    gameboard.fill(seedvalue);
    }
    configure();
    hide_labels();
    disable_stuff();
    set_target();
    timer->start(1000);
    game_running = true;
}
// Sulkee ohjelman kun painetaan EXIT -nappulaa
void MainWindow::on_ExitpushButton_clicked()
{
    delete timer;
    delete scene;
    MainWindow::close();
}
// aloittaa pelin uudelleen
void MainWindow::on_RestartpushButton_clicked()
{
    timer->stop();
    timer_clear();
    gameboard.reset_gameboard();
    scene->clear();
    enable_stuff();
    hide_labels();
    game_running = false;
    this->setStyleSheet({"background: rgb(114, 159, 207);"});
    ui->graphicsView->setStyleSheet({"background: white"});
}
// Pistetään peli tauolle
void MainWindow::on_GamepausepushButton_clicked()
{
    if(game_running)
    {
    ui->PauseLabel->setText("PAUSE");
    ui->PauseLabel->setStyleSheet({"background:orange; color:white"});
    if(ignore_cmds == false)
    {
        timer->stop();
        ui->PauseLabel->show();
        ignore_cmds = true;
    }
    else{
        timer->start();
        ignore_cmds = false;
        ui->PauseLabel->hide();
        }
    }
}
// Ottaa käyttöön kaikki syöttökentät käyttöliittymässä
void MainWindow::enable_stuff()
{
    ui->StartpushButton->setEnabled(true);
    ui->SeedspinBox->setEnabled(true);
    ui->TargetspinBox->setEnabled(true);
}
// poistaa kaikki syöttökentät käytöstä käyttöliittymässä
void MainWindow::disable_stuff()
{
    ui->StartpushButton->setEnabled(false);
    ui->SeedspinBox->setEnabled(false);
    ui->TargetspinBox->setEnabled(false);
}
// Asettaa tavoiteluvun pelille. jos ei aseta mitään,
// niin asettaa vakiona tavoiteluvuksi 2048
void MainWindow::set_target()
{
   QString default_target = "2048";
   QString goal = QString::number(ui->TargetspinBox->value());

   if(ui->TargetspinBox->value() == 0)
   {
       target = DEFAULT_GOAL;
       ui->Targetlabel->setText(default_target);
   }
   else
   {
    target = ui->TargetspinBox->value();
    ui->Targetlabel->setText(goal);
   }
}
// Tyhjentää ajastimen
void MainWindow::timer_clear()
{
    ui->lcdNumber->display(0);
}
// Ajastimen toiminta
void MainWindow::time_counter()
{
    ui->lcdNumber->display(ui->lcdNumber->value()+1);
}

// Etsii oikean arvon laatalle Items:eistä
MainWindow::Item MainWindow::find_item(int item)
{
    for(auto &x:Items)
    {
        if(x.number == item)
        {
           return x;
        }
    }
    return Items.at(0);
}
