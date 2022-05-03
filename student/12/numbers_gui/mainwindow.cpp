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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::new_tile()
{
    gameboard.new_value();
}

void MainWindow::action()
{
    scene->clear();
    new_tile();
    configure();
}

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
            scene->addRect(square);
            QGraphicsTextItem *text = scene->addText(value.marker);
            text->setPos(y * TILESIZE, x * TILESIZE);
            }
      }
}

void MainWindow::hide_labels()
{
    ignore_cmds = false;
    ui->WinnerLabel->hide();
    ui->LoserLabel->hide();
}

void MainWindow::win_condition()
{
    ui->WinnerLabel->setText("You have won!");
    game_running = false;
    ui->WinnerLabel->show();
}

void MainWindow::lose_condition()
{
    ui->LoserLabel->setText("You have lost!");
    game_running = false;
    ui->LoserLabel->show();
}

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
    game_running = true;

}

void MainWindow::on_ExitpushButton_clicked()
{
    delete scene;
    MainWindow::close();
}

void MainWindow::on_RestartpushButton_clicked()
{
    gameboard.reset_gameboard();
    scene->clear();
    enable_stuff();
    hide_labels();
    game_running = false;
}

void MainWindow::enable_stuff()
{
    ui->StartpushButton->setEnabled(true);
    ui->SeedspinBox->setEnabled(true);
    ui->TargetspinBox->setEnabled(true);
}

void MainWindow::disable_stuff()
{
    ui->StartpushButton->setEnabled(false);
    ui->SeedspinBox->setEnabled(false);
    ui->TargetspinBox->setEnabled(false);
}

void MainWindow::set_target()
{
   QString default_goal = "2048";
   QString goal = QString::number(ui->TargetspinBox->value());
   if(ui->TargetspinBox->value() == 0)
   {
       target = DEFAULT_GOAL;
       ui->Targetlabel->setText(default_goal);
   }
   else
   {
    target = ui->TargetspinBox->value();
    ui->Targetlabel->setText(goal);
   }
}

MainWindow::Item MainWindow::find_item(int item)
{
    for(auto &x:Items)
    {
        if(x.number == item)
        {
           return x;
        }
    }
}
