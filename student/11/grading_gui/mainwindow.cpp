#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecounter.hh"
#include <QString>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_countPushButton_clicked()
{
     int n = ui->spinBoxN->value();
     int g = ui->spinBoxG->value();
     int p = ui->spinBoxP->value();
     int e = ui->spinBoxE->value();

    int result = count_final_grade(n,g,p,e);
    const QString x = QString::number(result);
    const QString text = "Total grade: " + x;

    ui->textBrowser->setText(text);
    return;
}
