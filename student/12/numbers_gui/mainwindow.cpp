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
    if(event->key() == Qt::Key_W)
    {
        if(gameboard.move(UP,target))
        {
        }
    }
    else if(event->key() == Qt::Key_S)
    {
        if(gameboard.move(DOWN,target))
        {
        }
    }
    else if(event->key() == Qt::Key_D)
    {
        if(gameboard.move(RIGHT,target))
        {
        }
    }
    else if(event->key() == Qt::Key_A)
    {
        if(gameboard.move(LEFT,target))
        {
        }
    }
    else
    {
        return;
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

void MainWindow::on_startPushButton_clicked()
{
    gameboard.init_empty();

    if(ui->SeedspinBox->value() != 0)
    {
        int seed = ui->SeedspinBox->value();
        gameboard.fill(seed);
    }
    else
    {
    int seed = time(NULL);
    gameboard.fill(seed);
    }
    configure();
    game_running = true;

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
