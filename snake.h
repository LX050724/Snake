#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <snakeview.h>

class Snake : public QObject
{
    Q_OBJECT

#define S_H 50
#define S_L 300

    typedef enum {
        D_Up,
        D_Down,
        D_Left,
        D_Right,
    }Driect_t;

    typedef enum {
        S_Life,
        S_Out,
        S_Touch,
    } state_t;

    QTimer* Timer = nullptr;

    int cols = 50, rows = 75;

    QList<QPoint> snake;
    Qt::Key lastKey;
    Qt::Key Key;
    int speed = S_L;
    Driect_t listDriect;
    state_t state;
    bool appleflag = false;
    QPoint apple;

    SnakeView *View = nullptr;

public:
    explicit Snake(QObject* parent);
    inline void setPrinter(SnakeView* view) { View = view; }
    void clean();
    void start();

private:
    QPoint createapple();
    bool chick(QPoint p);

public slots:
    void keyPress(Qt::Key key);
    void TimerEvent();

signals:
    void outside();
    void touch();
    void scour(int s);
};

#endif // SNAKE_H
