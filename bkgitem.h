/**
* @projectName   simulation
* @brief         每种折法的背景
* @author        Zeki
* @date          2021-09-11
*/
#ifndef BKGITEM_H
#define BKGITEM_H

#include <QGraphicsItem>

class BkgItem : public QGraphicsItem
{
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
protected:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    QRectF getCustomRect() const;
    QSize m_size;
    QSize m_sizhe_size;
    QSize m_erfang_size;
};

#endif // BKGITEM_H
