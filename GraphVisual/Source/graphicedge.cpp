#include"Headers/graphicedge.h"

#include <QPen>
#include <QPainter>

GraphicEdge::GraphicEdge(GraphicNode* start, GraphicNode* end, int weight)
    :QGraphicsLineItem(),
    m_start (start),
    m_end (end),
    m_weight(weight){
    setFlags(GraphicsItemFlag::ItemIsSelectable | GraphicsItemFlag::ItemIsMovable);
}

QRectF GraphicEdge::boundingRect() const {
    return QRectF();
}


void GraphicEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen;

    if(collidesWithItem(m_start) or collidesWithItem(m_end)) {
        pen.setColor(Qt::white);
    } else {
        pen.setColor(Qt::black);
    }

    painter->setPen(pen);

    painter->drawLine(m_start->CenterPosition(), m_end->CenterPosition());

    const auto text = QString::fromStdString(std::to_string(m_weight));
    painter->drawText(m_start->CenterPosition().rx() - (m_start->CenterPosition().rx() - m_end->CenterPosition().rx())/2.0,
                      m_start->CenterPosition().ry() - (m_start->CenterPosition().ry() - m_end->CenterPosition().ry())/2.0,
                      text);
}
