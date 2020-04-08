#include "snakeview.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QtDebug>
#include <QMessageBox>
#include <QGraphicsRectItem>

SnakeView::SnakeView(QWidget* parent) :
    QGraphicsView(parent)
{
    Scene = new QGraphicsScene(this);
    this->setScene(Scene);
    frame = Scene->addRect(QRect(0, 0, 750, 500));
    frame->setPen(QPen(QColor(0, 255, 0, 200)));
}

void SnakeView::drawRect(const QRect &r, const QColor &color)
{
    QPixmap Pixmap(r.size());
    Pixmap.fill(color);

    QGraphicsPixmapItem* item = Scene->addPixmap(Pixmap);
    item->setPos(QPoint(r.top(), r.left()));
    item->setParentItem(frame);
}

void SnakeView::clear()
{
    Scene->clear();
    frame = Scene->addRect(QRect(0, 0, 750, 500));
    frame->setPen(QPen(QColor(0, 255, 0, 200)));
}

void SnakeView::keyPressEvent(QKeyEvent *event)
{
    emit keyEvent((Qt::Key)event->key());
}
