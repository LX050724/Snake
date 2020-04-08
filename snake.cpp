#include "snake.h"
#include <QTimer>
#include <QtDebug>

Snake::Snake(QObject* parent) :
    QObject(parent)
{
    srand(time(nullptr));
    Timer = new QTimer(this);

    Timer->setInterval(S_L);

    connect(Timer, &QTimer::timeout, this, &Snake::TimerEvent);


    snake.push_back(QPoint(cols / 2, rows / 2));
    snake.push_back(QPoint(cols / 2, rows / 2 + 1));
    snake.push_back(QPoint(cols / 2, rows / 2 + 2));
    snake.push_back(QPoint(cols / 2, rows / 2 + 3));

    apple = createapple();
}

void Snake::clean()
{
    Timer->stop();
    Timer->setInterval(500);

    Key = Qt::Key_unknown;
    lastKey = Qt::Key_unknown;
    snake.clear();

    snake.push_back(QPoint(cols / 2, rows / 2));
    snake.push_back(QPoint(cols / 2, rows / 2 + 1));
    snake.push_back(QPoint(cols / 2, rows / 2 + 2));
    snake.push_back(QPoint(cols / 2, rows / 2 + 3));

    apple = createapple();
}

void Snake::start()
{
    Timer->start();
    Key = Qt::Key_A;
    lastKey = Qt::Key_A;
}

QPoint Snake::createapple()
{
    QPoint temp;
    do {
        temp.setX(rand() % cols);
        temp.setY(rand() % rows);
    } while (chick(temp));
    return temp;
}

bool Snake::chick(QPoint p)
{
    for(const auto &i : snake)
    {
        if(i == p)
            return true;
    }
    return false;
}

void Snake::keyPress(Qt::Key key)
{
    qDebug() << key;
    switch (key) {
    case Qt::Key_Space:
        Key = Qt::Key_Space;
        break;
    case Qt::Key_W:
    case Qt::Key_Up:
        Key = Qt::Key_W;
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        Key = Qt::Key_A;
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        Key = Qt::Key_S;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        Key = Qt::Key_D;
        break;
    default:
        return;
    }
}

void Snake::TimerEvent()
{
    qDebug() << "Snake::TimerEvent";
    Qt::Key _Key = Key;
    if (_Key == Qt::Key_Space)
    {
        speed = S_H;
        _Key = lastKey;
    }
    else
    {
        speed = S_L;
    }

    rekey:
    switch (_Key) {
    case Qt::Key_W:
        if (listDriect == D_Down)
        {
            _Key = Qt::Key_S;
            goto rekey;
        }
        listDriect = D_Up;
        snake.push_front(snake.front() + QPoint(-1, 0));
        if (snake.front() != apple)snake.pop_back();
        else appleflag = true;
        break;
    case Qt::Key_S:
        if (listDriect == D_Up)
        {
            _Key = Qt::Key_W;
            goto rekey;
        }
        listDriect = D_Down;
        snake.push_front(snake.front() + QPoint(1, 0));
        if (snake.front() != apple)snake.pop_back();
        else appleflag = true;
        break;
    case Qt::Key_A:
        if (listDriect == D_Right)
        {
            _Key = Qt::Key_D;
            goto rekey;
        }
        listDriect = D_Left;
        snake.push_front(snake.front() + QPoint(0, -1));
        if (snake.front() != apple)snake.pop_back();
        else appleflag = true;
        break;
    case Qt::Key_D:
        if (listDriect == D_Left)
        {
            _Key = Qt::Key_A;
            goto rekey;
        }
        listDriect = D_Right;
        snake.push_front(snake.front() + QPoint(0, 1));
        if (snake.front() != apple)snake.pop_back();
        else appleflag = true;
        break;
    }

    if (snake.front().x() < 0 || snake.front().x() >= cols ||
        snake.front().y() < 0 || snake.front().y() >= rows)
    {
        state = S_Out;
        qInfo() << "out";
        emit outside();
        return;
    }

    QList<QPoint>::iterator it = snake.begin();
    ++it;
    do {
        if (snake.front() == *it)
        {
            state = S_Touch;
            qInfo() << "touch";
            emit touch();
            return;
        }
    } while (++it != snake.end());

    if (appleflag)
    {
        appleflag = false;
        apple = createapple();
        emit scour(snake.size());
    }
    lastKey = _Key;

    Timer->setInterval(speed);

    if(View == nullptr)
        return;

    View->clear();

    View->drawRect(QRect(apple * 10 , QSize(10, 10)), QColor(255, 0, 0));
    qDebug() << QRect(apple * 10 , QSize(10, 10));
    for(const auto &i : snake)
    {
        if(i == snake.front())
            View->drawRect(QRect(i * 10, QSize(10, 10)), QColor(255, 255, 0));
        else
            View->drawRect(QRect(i * 10, QSize(10, 10)), QColor(0, 255, 0));
    }
}
