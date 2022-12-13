#include "Headers/graphicnode.h"
#include "Headers/node.h"
#include "qgraphicsscene.h"

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

    QPen pen(Qt::black);
    pen.setWidth(2);

    painter->setBrush(m_brush);
    painter->setPen(pen);
    painter->drawEllipse(boundingRect());

    const auto text = QString::fromStdString(m_Node->name());
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, text);
}

QPointF GraphicNode::CenterPosition() {
    return pos() + QPointF(Width() / 2, Height() / 2);
}


void GraphicNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsObject::mouseMoveEvent(event);

    if(x() < 0) {
        setPos(0, y());
    } else if (x() + boundingRect().right() > scene()->width()) {
        setPos(scene()->width() - boundingRect().width(), y());
    }

    if (y() < 0) {
        setPos(x(), 0);
    } else if (y()+ boundingRect().bottom() > scene()->height()) {
        setPos(x(), scene()->height() - boundingRect().height());
    }

    emit needRedraw();
}

void GraphicNode::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    m_brush = QBrush(Qt::yellow);
    emit needRedraw();
    QGraphicsObject::hoverEnterEvent(event);
}
void GraphicNode::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    m_brush = QBrush(Qt::white);
    emit needRedraw();
    QGraphicsObject::hoverLeaveEvent(event);
}


int GraphicNode::type() const{
    return 1;
}
