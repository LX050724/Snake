#ifndef SNAKEVIEW_H
#define SNAKEVIEW_H

#include <QWidget>
#include <QGraphicsView>

class SnakeView : public QGraphicsView
{
    Q_OBJECT

    QGraphicsScene* Scene;
    QGraphicsRectItem* frame;
public:
    explicit SnakeView(QWidget* parent = nullptr);

    void drawRect(const QRect &r, const QColor &color);
    void clear();

private:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void keyEvent(Qt::Key key);

};


#endif // SNAKEVIEW_H
