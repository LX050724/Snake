#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <snake.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void Snake_outside();
    void Snake_touch();
    void Snake_scour(int s);

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    Snake* game = nullptr;
};
#endif // MAINWINDOW_H
