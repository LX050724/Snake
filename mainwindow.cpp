#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "helpwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    game = new Snake(this);
    game->setPrinter(ui->graphicsView);

    connect(ui->graphicsView, &SnakeView::keyEvent, game, &Snake::keyPress);
    connect(game, &Snake::outside, this, &MainWindow::Snake_outside);
    connect(game, &Snake::touch, this, &MainWindow::Snake_touch);
    connect(game, &Snake::scour, this, &MainWindow::Snake_scour);
}

MainWindow::~MainWindow()
{
    disconnect(ui->graphicsView, &SnakeView::keyEvent, game, &Snake::keyPress);
    disconnect(game, &Snake::outside, this, &MainWindow::Snake_outside);
    disconnect(game, &Snake::touch, this, &MainWindow::Snake_touch);
    disconnect(game, &Snake::scour, this, &MainWindow::Snake_scour);
    delete game;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    game->start();
    ui->graphicsView->setFocus();
}

void MainWindow::on_pushButton_2_clicked()
{
    game->clean();
    ui->lcdNumber->display(0);
    ui->graphicsView->clear();
}

void MainWindow::Snake_outside()
{
    QMessageBox::information(this, tr("End"), tr("出界,你的得分为") + QString::number(ui->lcdNumber->intValue()) + tr("分"));
    game->clean();
    ui->lcdNumber->display(0);
}

void MainWindow::Snake_touch()
{
    QMessageBox::information(this, tr("End"), tr("接触自己,你的得分为") + QString::number(ui->lcdNumber->intValue()) + tr("分"));
    game->clean();
    ui->lcdNumber->display(0);
}

void MainWindow::Snake_scour(int s)
{
    ui->lcdNumber->display(s - 4);
}

void MainWindow::on_pushButton_3_clicked()
{
    HelpWindow* w = new HelpWindow;
    w->exec();
    delete w;
}
