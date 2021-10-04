#include "svgitem.h"
#include <QDebug>
#include <QPainter>
#include <QCursor>
#include <QPen>
#include <QtMath>
#include <QVector2D>
#include <QVector3D>
#include <QByteArray>

#define PI 3.14159265358979

QImage svgItem::m_closeIcon;
QImage svgItem::m_resizeIcon;
QImage svgItem::m_rotateIcon;

svgItem::svgItem()
{
    m_render = new QSvgRenderer;

    //读取svg
    file.setFileName(":/icon/E:/ENTERTAIN/Picture/icon/Vector.svg");
    file.open(QIODevice::ReadOnly);
    QByteArray svgData = file.readAll();
    doc.setContent(svgData);
    m_render->load(svgData);
    file.close();

    this->setFlag(QGraphicsItem::ItemIsSelectable);
    initIcon();

    m_size = QSize(m_render->boundsOnElement("svg").width(),m_render->boundsOnElement("svg").height());


}

svgItem::~svgItem()
{
    qDebug()<<"delete";
}

void svgItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    m_render->render(painter,QRectF(-m_size.width()/2,-m_size.height()/2,m_size.width(),m_size.height()));//渲染本体

    if(!this->isSelected())
        return;

    QPen pen;
    pen.setWidth(1);
    pen.setColor(color);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);

    QRectF itemRect = getCustomRect();
    QRectF outLineRect = itemRect.adjusted(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);

    painter->drawRect(outLineRect);

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(Qt::transparent));

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

qreal svgItem::getDistance(QPointF Start,QPointF End)
{
    qreal delta_x = Start.x() - End.x();
    qreal delta_y = Start.y() - End.y();
    return qSqrt(delta_x*delta_x + delta_y*delta_y);

}

void svgItem::SetAttrRecur(QDomElement elem, QString strtagname, QString strattr, QString strattrval)
{
    // if it has the tagname then overwritte desired attribute
    if (elem.tagName().compare(strtagname) == 0)
    {
        elem.setAttribute(strattr, strattrval);
    }
    // loop all children
    for (int i = 0; i < elem.childNodes().count(); i++)
    {
        if (!elem.childNodes().at(i).isElement())
        {
            continue;
        }
        SetAttrRecur(elem.childNodes().at(i).toElement(), strtagname, strattr, strattrval);
    }
}

QRectF svgItem::boundingRect() const
{
    QRectF rectF = getCustomRect();

    if(!this->isSelected())
        return rectF;

    rectF.adjust(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);
    rectF.adjust(-m_nEllipseWidth, -m_nEllipseWidth, m_nEllipseWidth, m_nEllipseWidth);

    return rectF;
}

void svgItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
    else if(getDistance(pos,outLineRect.topRight()) <= m_nEllipseWidth)
        m_itemOper = t_close;
    else if(getDistance(pos,outLineRect.bottomLeft()) <= m_nEllipseWidth)
        m_itemOper = t_rotate;
    else if(getDistance(pos,outLineRect.bottomRight()) <= m_nEllipseWidth)
        m_itemOper = t_resize;
    qDebug()<<m_itemOper;

    //保存当前的一些信息
    m_pos = pos;
    m_pressedPos = scenePos;
    m_startPos = this->pos();

    emit sync(m_size.width(),color.name());

    this->update();
    return QGraphicsItem::mousePressEvent(event);

}

void svgItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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

void svgItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "CustomItem::mouseReleaseEvent";

    if(m_itemOper == t_close)
    {
        delete this;
        return;
    }
    m_itemOper = t_none;
    return QGraphicsItem::mouseReleaseEvent(event);
}

QPainterPath svgItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void svgItem::changeColor(QString color)
{
    SetAttrRecur(doc.documentElement(),"path","fill",color);
    m_render->load(doc.toByteArray());
}

QRectF svgItem::getCustomRect() const
{
    QPointF centerPos(0, 0);
    return QRectF(centerPos.x() - m_size.width() / 2, centerPos.y() - m_size.height() / 2, \
                  m_size.width(), m_size.height());
}

void svgItem::mouseMoveMoveOperator(const QPointF &scenePos, const QPointF &loacalPos)
{
    Q_UNUSED(loacalPos)

    qreal xInterval = scenePos.x() - m_pressedPos.x();
    qreal yInterval = scenePos.y() - m_pressedPos.y();

    this->setPos(m_startPos + QPointF(xInterval, yInterval));
    this->update();
}

void svgItem::mouseMoveResizeOperator(const QPointF &scenePos, const QPointF &loacalPos)
{
    Q_UNUSED(scenePos)

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
    qDebug()<<"resize";
    this->update();
}

void svgItem::mouseMoveRotateOperator(const QPointF &scenePos, const QPointF &loacalPos)
{
    qDebug()<<"rotate";

    // 获取并设置为单位向量
    QVector2D startVec(m_pos.x() - 0, m_pos.y() - 0);
    startVec.normalize();
    QVector2D endVec(loacalPos.x() - 0, loacalPos.y() - 0);
    endVec.normalize();

    // 单位向量点乘，计算角度
    qreal dotValue = QVector2D::dotProduct(startVec, endVec);
    if (dotValue > 1.0)
        dotValue = 1.0;
    else if (dotValue < -1.0)
        dotValue = -1.0;

    dotValue = qAcos(dotValue);
    if (qIsNaN(dotValue))
        dotValue = 0.0;

    // 获取角度
    qreal angle = dotValue * 1.0 / (PI / 180);

    // 向量叉乘获取方向
    QVector3D crossValue = QVector3D::crossProduct(QVector3D(startVec, 1.0),QVector3D(endVec, 1.0));
    if (crossValue.z() < 0)
        angle = -angle;
    m_rotate += angle;

    // 设置变化矩阵
    m_transform.rotate(m_rotate);
    this->setTransform(m_transform);

    m_pos = loacalPos;
    this->update();

}

void svgItem::initIcon()
{
    if(m_closeIcon.isNull())
        m_closeIcon.load(":/icon/E:/ENTERTAIN/Picture/icon/cancel.png");
    if(m_resizeIcon.isNull())
        m_resizeIcon.load(":/icon/E:/ENTERTAIN/Picture/icon/resize.png");
    if(m_rotateIcon.isNull())
        m_rotateIcon.load(":/icon/E:/ENTERTAIN/Picture/icon/rotate.png");

    m_closePixmap = QPixmap::fromImage(m_closeIcon);
    m_resizePixmap = QPixmap::fromImage(m_resizeIcon);
    m_rotatePixmap = QPixmap::fromImage(m_rotateIcon);
}
