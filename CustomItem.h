/**
* @projectName   simulation
* @brief         自定义图元组件
* @author        Zeki
* @date          2021-09-05
*/
#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class CustomItem : public QGraphicsItem
{
public:
    CustomItem();
    CustomItem(QString pixName);
    ~CustomItem();
    enum ItemOperator
        {
            t_none,
            t_move,
            t_resize,
            t_rotate,
            t_close
        };
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    QRectF boundingRect() const Q_DECL_OVERRIDE;
protected:
    //鼠标事件
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    QPainterPath shape() const override;
protected:
    QRectF getCustomRect(void) const;

    QSize m_size;
    ItemOperator m_itemOper = t_none;

    virtual void mouseMoveMoveOperator(const QPointF& scenePos, const QPointF& loacalPos);
    virtual void mouseMoveResizeOperator(const QPointF& scenePos, const QPointF& loacalPos);
    virtual void mouseMoveRotateOperator(const QPointF& scenePos, const QPointF& loacalPos);

    QPointF m_pos;              // 本地所坐标点击的点
    QPointF m_pressedPos;       // 场景坐标点击的点
    QPointF m_startPos;         // Item再场景坐标的起始坐标
    qreal m_rotate = 0.0;       // 当前旋转角度
    QTransform m_transform;     // 变换矩阵

signals:
    void onClickedCopyItem(void);
private:
    void initIcon(void);

    static QImage m_closeIcon;
    static QImage m_resizeIcon;
    static QImage m_rotateIcon;

    QPixmap m_closePixmap;
    QPixmap m_resizePixmap;
    QPixmap m_rotatePixmap;

    // 设置是否能够更改尺寸
    bool m_isResizeable = true;
    bool m_isRatioScale = true;
    qreal m_ratioValue = 1.0;

    int m_nInterval = 20;
    int m_nEllipseWidth = 16;
    QColor color;
    QPixmap pix;
};

#endif // CUSTOMITEM_H
