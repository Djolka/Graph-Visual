#ifndef GRAPHICEDGE_H
#define GRAPHICEDGE_H

#include <QGraphicsObject>
#include"Headers/graphicnode.h"

class GraphicEdge : public QGraphicsObject {
Q_OBJECT
public:
    GraphicEdge(GraphicNode* start, GraphicNode* end, int weight);

    virtual ~GraphicEdge(){}

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    GraphicNode* m_start;
    GraphicNode* m_end;
    int m_weight;
};


#endif // GRAPHICEDGE_H
