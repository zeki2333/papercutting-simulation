/**
* @projectName   simulation
* @brief         折法模板控件
* @author        Zeki
* @date          2021-10-07
*/
/**
* @version       1.0
* @content       添加四折模板
* @author        Zeki
* @date          2021-10-07
*/
/**
* @version       1.1
* @content       添加选中效果；添加换色；添加变更大小；添加二方连续模板；实现自定义信号；
* @author        Zeki
* @date          2021-10-07
*/
#include "bkgitem.h"


BkgItem::BkgItem()
{
    this->m_mode = none;
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    m_size.setWidth(0);m_size.setHeight(0);
    m_sizhe_size.setWidth(200);m_sizhe_size.setHeight(200);
    m_erfang_size.setWidth(30);m_erfang_size.setHeight(45);
}

void BkgItem::setFoldMode(BkgItem::foldMode mode)
{
    if(mode == sizhe)
    {
        m_size.setWidth(m_sizhe_size.width());
        m_size.setHeight(m_sizhe_size.height());
    }
    else if(mode == erfanglianxu)
    {
        m_size.setWidth(m_erfang_size.width());
        m_size.setHeight(m_erfang_size.height());
    }
    else return;

    this->m_mode = mode;
    this->update();
    return;

}

int BkgItem::width()
{
    return m_size.width();
}

int BkgItem::height()
{
    return m_size.height();
}

void BkgItem::changeColor(QString color)
{

    m_color = color;
}

void BkgItem::changeSize(int width)
{
    qreal height = 200;
    if(m_mode == sizhe)
        height = width;
    else if(m_mode == erfanglianxu)
        height = 1.5f*width;
    m_size=QSize(width,height);
    this->update();
}

int BkgItem::getMode()
{
    return m_mode;
}

void BkgItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    emit sync(m_size.width(),m_color.name());
}

QRectF BkgItem::boundingRect() const
{
    QPointF centerPos(0, 0);
    return QRectF(centerPos.x() - m_size.width() / 2, centerPos.y() - m_size.height() / 2, \
                  m_size.width(), m_size.height());
}

QPainterPath BkgItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void BkgItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing, true);

    pen.setWidth(5);
    pen.setColor(m_color);
    pen.setJoinStyle(Qt::MiterJoin);

    brush.setColor(m_color);
    brush.setStyle(Qt::SolidPattern);

    QRectF rect = boundingRect();
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(rect);

    if(!this->isSelected())
        return;

    pen.setWidth(1);
    pen.setColor(m_color);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);

    QRectF itemRect = getCustomRect();
    QRectF outLineRect = itemRect.adjusted(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);

    painter->setBrush(QColor(Qt::transparent));
    painter->drawRect(outLineRect);

    //画笔样式复位
    pen.setStyle(Qt::SolidLine);
}

QRectF BkgItem::getCustomRect() const
{
    QPointF centerPos(0, 0);
    return QRectF(centerPos.x() - m_size.width() / 2, centerPos.y() - m_size.height() / 2, \
                  m_size.width(), m_size.height());
}
