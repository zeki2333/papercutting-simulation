#include "CustomItem.h"
#include <QDebug>
#include <QPainter>
#include <QCursor>
#include <QPen>
#include <QtMath>

QImage CustomItem::m_closeIcon;
QImage CustomItem::m_resizeIcon;
QImage CustomItem::m_rotateIcon;

CustomItem::CustomItem()
{
    color = Qt::blue;
    pix.load(":/icon/E:/ENTERTAIN/Picture/icon/create_s.png");

    //this->setFlag(QGraphicsItem::ItemIsFocusable);
    //设置图元为可移动的
    //this->setFlag(QGraphicsItem::ItemIsMovable);

    this->setFlag(QGraphicsItem::ItemIsSelectable);
    initIcon();
}

qreal getDistance(QPointF Start,QPointF End)
{
    qreal delta_x = Start.x()-End.x();
    qreal delta_y = Start.y()-End.y();
    return qSqrt(delta_x*delta_x + delta_y*delta_y);

}

void CustomItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    /*
    qDebug() << "CustomItem::paint";
    if(hasFocus()) {
        painter->setPen(QPen(QColor(0,0,255,200)));
    } else {
        painter->setPen(QPen(QColor(255,100,100,100)));
    }
    painter->setBrush(color);
    //painter->drawRect(-10, -10, 30, 30);
    */

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    painter->drawPixmap(QPoint(-pix.width()/2,-pix.height()/2),pix,QRect(0,0,pix.width(),pix.height()));

    if(!this->isSelected())
        return;

    QPen pen;
    pen.setWidth(1);
    pen.setColor(color);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);

    QRectF outLineRect = getCustomRect();
    painter->drawRect(outLineRect);

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("00A19D"));

    //绘制控制点
    painter->drawEllipse(outLineRect.topRight(),m_nEllipseWidth,m_nEllipseWidth);
    if(!m_closePixmap.isNull())
        painter->drawPixmap(QRect(outLineRect.topRight().x() - m_nEllipseWidth / 2, \
                                 outLineRect.topRight().y() - m_nEllipseWidth / 2, \
                                 m_nEllipseWidth, m_nEllipseWidth),m_closePixmap);

    painter->drawEllipse(outLineRect.bottomLeft(), m_nEllipseWidth, m_nEllipseWidth);
    if (!m_rotatePixmap.isNull())
       painter->drawPixmap(QRect(outLineRect.bottomLeft().x() - m_nEllipseWidth / 2, \
                                 outLineRect.bottomLeft().y() - m_nEllipseWidth / 2, \
                                 m_nEllipseWidth, m_nEllipseWidth), m_rotatePixmap);

    painter->drawEllipse(outLineRect.bottomRight(), m_nEllipseWidth, m_nEllipseWidth);
        if (!m_resizePixmap.isNull())
            painter->drawPixmap(QRect(outLineRect.bottomRight().x() - m_nEllipseWidth / 2, \
                                      outLineRect.bottomRight().y() - m_nEllipseWidth / 2, \
                                      m_nEllipseWidth, m_nEllipseWidth), m_resizePixmap);

}

QRectF CustomItem::boundingRect() const
{
    QRectF rectF = getCustomRect();

    if(!this->isSelected())
        return rectF;

    rectF.adjust(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);
    rectF.adjust(-m_nEllipseWidth, -m_nEllipseWidth, m_nEllipseWidth, m_nEllipseWidth);

    return rectF;
}

void CustomItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_transform = this->transform();

    QRectF itemRect = getCustomRect();
    QRectF outLineRect = itemRect.adjusted(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);

    //获取当前模式
    QPointF pos = event->pos();
    QPointF scenePos = event->scenePos();
    qDebug()<<getDistance(pos,outLineRect.bottomRight());
    if(itemRect.contains(pos))
        m_itemOper = t_move;
    else if(getDistance(pos,outLineRect.bottomLeft()) <= m_nEllipseWidth)
        m_itemOper = t_rotate;
    else if(getDistance(pos,outLineRect.bottomRight()) <= m_nEllipseWidth)
        m_itemOper = t_resize;
    qDebug()<<m_itemOper;

    //保存当前的一些信息
    m_pos = pos;
    m_pressedPos = scenePos;
    m_startPos = this->pos();

    this->update();
    return QGraphicsItem::mousePressEvent(event);
}

void CustomItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // 获取场景坐标和本地坐标
    QPointF scenePos = event->scenePos();
    QPointF pos = event->pos();

    if (m_itemOper == t_move)
    {
        // 处理移动
        mouseMoveMoveOperator(scenePos, pos);
    }
    else if (m_itemOper == t_resize)
    {
        // 处理更改大小
        mouseMoveResizeOperator(scenePos, pos);
    }
    else if (m_itemOper == t_rotate)
    {
        // 处理旋转
        mouseMoveRotateOperator(scenePos, pos);
    }

    return QGraphicsItem::mouseMoveEvent(event);
}

void CustomItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "CustomItem::mouseReleaseEvent";
    m_itemOper = t_none;
    return QGraphicsItem::mouseReleaseEvent(event);
}

QPainterPath CustomItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

QRectF CustomItem::getCustomRect() const
{
    /*QRectF rect = boundingRect();
    rect.adjust(m_nEllipseWidth,m_nEllipseWidth,-m_nEllipseWidth,-m_nEllipseWidth);
    return rect;*/

    QPointF centerPos(0, 0);
    return QRectF(centerPos.x() - pix.width() / 2, centerPos.y() - pix.height() / 2, \
                  pix.width(), pix.height());
}

void CustomItem::mouseMoveMoveOperator(const QPointF &scenePos, const QPointF &loacalPos)
{
    qreal xInterval = scenePos.x() - m_pressedPos.x();
    qreal yInterval = scenePos.y() - m_pressedPos.y();

    this->setPos(m_startPos + QPointF(xInterval, yInterval));
    this->update();
}

void CustomItem::mouseMoveResizeOperator(const QPointF &scenePos, const QPointF &loacalPos)
{
    if (!m_isResizeable)
        return;

    qreal ratio = m_ratioValue;
    qreal itemWidth = abs(loacalPos.x()) * 2 - m_nInterval - m_nEllipseWidth;
    qreal itemHeight = abs(loacalPos.y()) * 2 - m_nInterval - m_nEllipseWidth;
    if (m_isRatioScale)
        itemHeight = itemWidth * 1.0 / ratio;

    // 设置图片的最小大小为10
    if (itemWidth < 10 || itemHeight < 10)
        return;

    m_size = QSize(itemWidth, itemHeight);
    this->update();
}

void CustomItem::mouseMoveRotateOperator(const QPointF &scenePos, const QPointF &loacalPos)
{

}

void CustomItem::initIcon()
{
    if(m_closeIcon.isNull())
    {
        m_closeIcon.load(":/icon/E:/ENTERTAIN/Picture/icon/cancel.png");
    }
    if(m_resizeIcon.isNull())
        m_resizeIcon.load(":/icon/E:/ENTERTAIN/Picture/icon/resize.png");
    if(m_rotateIcon.isNull())
        m_rotateIcon.load(":/icon/E:/ENTERTAIN/Picture/icon/rotate.png");

    m_closePixmap = QPixmap::fromImage(m_closeIcon);
    m_resizePixmap = QPixmap::fromImage(m_resizeIcon);
    m_rotatePixmap = QPixmap::fromImage(m_rotateIcon);
    qDebug()<<m_closePixmap.isNull();
}

