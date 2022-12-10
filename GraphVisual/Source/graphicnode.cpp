#include "Headers/graphicnode.h"
#include "Headers/node.h"

#include <QPainter>

GraphicNode::GraphicNode(Node *node)
    : QGraphicsObject()
    , m_Node(node) {
     setFlags(GraphicsItemFlag::ItemIsSelectable | GraphicsItemFlag::ItemIsMovable);
    setAcceptHoverEvents(true);
}

QRectF GraphicNode::boundingRect() const {
    return QRectF(0, 0, Width(), Height());
}

void GraphicNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(m_brush);

    painter->drawEllipse(boundingRect());

    const auto text = QString::fromStdString(m_Node->name());
    painter->setPen(Qt::black);


    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, text);
}

QPointF GraphicNode::CenterPosition() const {
    return pos() + QPointF(Width() / 2, Height() / 2);
}


void GraphicNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsObject::mouseMoveEvent(event);
    emit needRedraw();
}

void GraphicNode::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    m_brush = QBrush(Qt::yellow);
    emit needRedraw();
    QGraphicsObject::hoverEnterEvent(event);
}
void GraphicNode::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    m_brush = QBrush();
    emit needRedraw();
    QGraphicsObject::hoverLeaveEvent(event);
}


int GraphicNode::type() const{
    return 1;
}


