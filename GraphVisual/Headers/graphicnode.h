#ifndef GRAPHICNODE_H
#define GRAPHICNODE_H

#include <QGraphicsObject>

class Node;

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

    QPointF CenterPosition() const;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Node *m_Node;

signals:
    void needRedraw();
};

#endif // GRAPHICNODE_H
