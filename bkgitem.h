/**
* @projectName   simulation
* @brief         每种折法的背景
* @author        Zeki
* @date          2021-09-11
*/
#ifndef BKGITEM_H
#define BKGITEM_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QtMath>

class BkgItem : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    BkgItem();
public:
    enum foldMode{
        none,
        sizhe,//四折
        erfanglianxu,//二方连续
        bazhe,//八折
        wuzhe//五折
    };
    void setFoldMode(foldMode mode);
    foldMode m_mode;
    int width();
    int height();
    void changeColor(QString color);
    void changeSize(int width);
    int getMode();
signals:
    void sync(int size,QString color);
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    QRectF getCustomRect() const;

    QPen pen;
    QBrush brush;

    QSize m_size;
    QSize m_sizhe_size;
    QSize m_erfang_size;
    QSize m_bazhe_size;
    QSize m_wuzhe_size;
    int m_nInterval = 10;
    QColor m_color = Qt::red;

    const QPointF points[6] = {
        QPointF(00.0, -50.0),
        QPointF(120.0, -50.0),
        QPointF(99.5, -36.0),
        QPointF(113.8, -12.1),
        QPointF(92.8, 00.9),
        QPointF(97.3, 20.2)
    };
};

#endif // BKGITEM_H
