#include "Headers/graphicnode.h"
#include "Headers/node.h"
#include "qgraphicsscene.h"
#include "qgraphicssceneevent.h"

#include <QPainter>

GraphicNode::GraphicNode(Node *node)
    : QGraphicsObject()
    , m_Node(node) {
     setFlags(GraphicsItemFlag::ItemIsSelectable | GraphicsItemFlag::ItemIsMovable);
    setAcceptHoverEvents(true);

}

GraphicNode::~GraphicNode() {

}

QColor GraphicNode::m_color = QColor("white");
int GraphicNode::m_height = 50;
int GraphicNode::m_width = 50;

QRectF GraphicNode::boundingRect() const {
    return QRectF(0, 0, GraphicNode::m_width, GraphicNode::m_height);
}

void GraphicNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(Qt::black);
    pen.setWidth(2);

    if(m_brush != QBrush(Qt::yellow)) {
        m_brush = QBrush(GraphicNode::m_color);
    }

    painter->setBrush(m_brush);
    painter->setPen(pen);
    painter->drawEllipse(boundingRect());

    const auto text = QString::fromStdString(m_Node->name());
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, text);
}

QPointF GraphicNode::CenterPosition() {
    return pos() + QPointF(GraphicNode::m_width / 2, GraphicNode::m_height / 2);
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
    m_brush = QBrush(GraphicNode::m_color);
    emit needRedraw();
    QGraphicsObject::hoverLeaveEvent(event);
}

int GraphicNode::type() const{
    return 1;
}
