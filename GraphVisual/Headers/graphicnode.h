#ifndef GRAPHICNODE_H
#define GRAPHICNODE_H

#include <QGraphicsObject>
#include<QBrush>

#include "Headers/node.h"

class GraphicNode : public QGraphicsObject {
    Q_OBJECT
public:
    GraphicNode(Node *node);
    ~GraphicNode();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    inline Node *getNode() { return m_Node; }

    inline int Width() const { return 50; }
    inline int Height() const { return 50; }

    int type() const override;

    QPointF CenterPosition();


protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    Node *m_Node;
    QBrush m_brush = QBrush(Qt::white);

signals:
    void needRedraw();
};

#endif // GRAPHICNODE_H
