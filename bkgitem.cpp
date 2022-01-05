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
    this->m_N = 4;
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    m_size.setWidth(0);m_size.setHeight(0);
    m_sizhe_size.setWidth(200);m_sizhe_size.setHeight(200);
    m_erfang_size.setWidth(100);m_erfang_size.setHeight(150);
    m_bazhe_size.setWidth(200);m_bazhe_size.setHeight(200);
    m_wuzhe_size.setWidth(100);m_wuzhe_size.setHeight(100);
    m_Nzhe_size.setWidth(150);m_Nzhe_size.setHeight(150);
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
    else if(mode == bazhe)
    {
        m_size.setWidth(m_bazhe_size.width());
        m_size.setHeight(m_bazhe_size.height());
    }
    else if(mode == wuzhe)
    {
        m_size.setWidth(m_wuzhe_size.width());
        m_size.setHeight(m_wuzhe_size.height());
    }
    else if(mode == Nzhe)
    {
        m_size.setWidth(m_Nzhe_size.width());
        m_size.setHeight(m_Nzhe_size.height());
    }
    else return;

    this->m_mode = mode;
    this->update();
    return;

}

void BkgItem::setNFoldNum(int n)
{
    m_N = n;
    this->update();
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
    else if(m_mode == bazhe)
        height = width;
    else if(m_mode == wuzhe||m_mode == Nzhe)
        height = width;
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
    //八折 五折 N折需要单独用QPainter画
    if(m_mode == bazhe)
    {
        QPainterPath TrianglePath;
        TrianglePath.moveTo(rect.bottomLeft());
        TrianglePath.lineTo(rect.topLeft());
        TrianglePath.lineTo(rect.topRight());
        TrianglePath.lineTo(rect.bottomLeft());
        qDebug()<<rect.topLeft().x()<<rect.topLeft().y();
        painter->fillPath(TrianglePath,brush);
    }
    else if(m_mode == wuzhe)
    {
        QPainterPath wubanPath;
        wubanPath.moveTo(rect.bottomRight());
        wubanPath.lineTo(QPointF(rect.bottomRight().rx()+rect.height()*cos(0.7*M_PI),rect.bottomRight().ry()-rect.height()*sin(0.7*M_PI)));
        wubanPath.lineTo(QPointF(rect.bottomRight().rx()+rect.height()*cos(0.6*M_PI),rect.bottomRight().ry()-rect.height()*sin(0.6*M_PI)));
        wubanPath.lineTo(rect.topRight());
        wubanPath.lineTo(rect.bottomRight());
        painter->fillPath(wubanPath,brush);
    }
    else if(m_mode == Nzhe)
    {
        QPainterPath NzhePath;
        NzhePath.moveTo(rect.bottomRight());
        NzhePath.lineTo(rect.topRight());
        NzhePath.arcTo(rect.topLeft().rx(),rect.topLeft().ry(),2*rect.width(),2*rect.height(),90,360/m_N);
        NzhePath.lineTo(rect.bottomRight());
        painter->fillPath(NzhePath,brush);
    }
    else
    {
        painter->drawRect(rect);
    }

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
