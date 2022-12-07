#ifndef GRAPHICNODE_H
#define GRAPHICNODE_H

#include <QGraphicsObject>

class Node;

// TODO: redrawing edges when a node is moved
// FIXME: when Q_OBJECT is added it behaves wierd

class GraphicNode : public QGraphicsObject {
    Q_OBJECT
public:
    GraphicNode(Node *node);

    virtual ~GraphicNode(){}

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    inline const Node *getNode() { return m_Node; };

    inline int Width() const { return 50; };
    inline int Height() const { return 50; };

    QPointF TopCenterPosition();
    QPointF BottomCenterPosition();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Node *m_Node;

signals:
    void needRedraw();
};

#endif // GRAPHICNODE_H
