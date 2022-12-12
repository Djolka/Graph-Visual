#include "Headers/graphicnode.h"
#include "Headers/node.h"

#include <QPainter>

GraphicNode::GraphicNode(Node *node)
    : QGraphicsObject()
    , m_Node(node) {
     setFlags(GraphicsItemFlag::ItemIsSelectable | GraphicsItemFlag::ItemIsMovable);
}

QRectF GraphicNode::boundingRect() const {
    return QRectF(0, 0, Width(), Height());
}

void GraphicNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawRoundedRect(boundingRect(), 30, 30);


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


