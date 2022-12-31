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
    inline void setBrush(QBrush b, bool x) { m_brush = b; m_algorithm = x; }
    inline QBrush getBrush(){return m_brush;}

    int type() const override;

    QPointF CenterPosition();


protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;


signals:
    void needRedraw();

public:
    static QColor m_color;
    static int m_width;
    static int m_height;

private:
    Node *m_Node;
    QBrush m_brush = QBrush(Qt::white);
    bool m_algorithm = false;
};

#endif // GRAPHICNODE_H
