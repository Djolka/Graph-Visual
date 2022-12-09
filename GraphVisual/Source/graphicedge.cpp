#include"Headers/graphicedge.h"

#include <QPainter>

GraphicEdge::GraphicEdge(GraphicNode* start, GraphicNode* end, int weight)
    :QGraphicsObject(),
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

    painter->drawLine(m_start->TopCenterPosition(), m_end->TopCenterPosition());

    const auto text = QString::fromStdString(std::to_string(m_weight));
    painter->drawText(m_start->TopCenterPosition().rx() - (m_start->TopCenterPosition().rx() - m_end->TopCenterPosition().rx())/2.0,
                      m_start->TopCenterPosition().ry() - (m_start->TopCenterPosition().ry() - m_end->TopCenterPosition().ry())/2.0,
                      text);
}
