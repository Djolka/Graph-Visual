#ifndef GRAPHICEDGE_H
#define GRAPHICEDGE_H

#include <QGraphicsLineItem>
#include"Headers/graphicnode.h"

class GraphicEdge : public QGraphicsLineItem {
public:
    GraphicEdge(GraphicNode* start, GraphicNode* end, int weight);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    GraphicNode* m_start;
    GraphicNode* m_end;
    int m_weight;
};


#endif // GRAPHICEDGE_H
