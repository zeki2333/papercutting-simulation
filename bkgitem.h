/**
* @projectName   simulation
* @brief         每种折法的背景
* @author        Zeki
* @date          2021-09-11
*/
#ifndef BKGITEM_H
#define BKGITEM_H

#include <QGraphicsItem>
#include <QPainter>

class BkgItem : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    BkgItem();
public:
    enum foldMode{
        none,
        sizhe,
        erfanglianxu
    };
    void setFoldMode(foldMode mode);
    foldMode m_mode;
    int width();
    int height();
    void changeColor(QString color);
protected:
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
    int m_nInterval = 10;
    QColor m_color = Qt::red;
};

#endif // BKGITEM_H
