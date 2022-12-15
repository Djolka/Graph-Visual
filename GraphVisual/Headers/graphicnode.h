#ifndef GRAPHICNODE_H
#define GRAPHICNODE_H

#include <QGraphicsObject>
#include<QBrush>

#include "Headers/node.h"

class GraphicNode : public QGraphicsObject {
    Q_OBJECT
public:
    GraphicNode(Node *node);

    virtual ~GraphicNode(){}

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    inline Node *getNode() { return m_Node; }

    static int m_width;
    static int m_height;

    int type() const override;

    QPointF CenterPosition();

    static QColor m_color;


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
