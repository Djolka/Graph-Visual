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

    painter->drawEllipse(boundingRect());

//    TODO: if node is empty then write the index
//    ...

    const auto text = QString::fromStdString(m_Node->name());
    painter->setPen(Qt::black);
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, text);
}

QPointF GraphicNode::TopCenterPosition() {
    return pos() + QPointF(Width() / 2, 0);
}

QPointF GraphicNode::BottomCenterPosition() {
    return pos() + QPointF(Width() / 2, Height());
}

void GraphicNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

    needRedraw();
    QGraphicsObject::mouseMoveEvent(event);
}


