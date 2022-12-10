#ifndef GRAPHICNODE_H
#define GRAPHICNODE_H

#include <QGraphicsObject>
#include<QBrush>

class Node;

class GraphicNode : public QGraphicsObject {
    Q_OBJECT
public:
    GraphicNode(Node *node);

    virtual ~GraphicNode(){}

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    inline Node *getNode() { return m_Node; }

    inline int Width() const { return 50; }
    inline int Height() const { return 50; }

    int type() const override;

    QPointF TopCenterPosition();
    QPointF BottomCenterPosition();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    Node *m_Node;
    QBrush m_brush = QBrush();

signals:
    void needRedraw();
};

#endif // GRAPHICNODE_H
