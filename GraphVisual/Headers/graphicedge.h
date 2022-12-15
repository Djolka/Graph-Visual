#ifndef GRAPHICEDGE_H
#define GRAPHICEDGE_H

#include <QGraphicsLineItem>
#include"Headers/graphicnode.h"
#include<QLineEdit>
#include<QPen>
#include<QPolygon>

class GraphicEdge : public QObject, public QGraphicsLineItem {
    Q_OBJECT
public:
    GraphicEdge(GraphicNode* start, GraphicNode* end, int weight);
    ~GraphicEdge();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override;
    QPainterPath shape() const;

    int getWeight(){return m_weight;}
    GraphicNode* getStart(){return m_start;}
    GraphicNode* getEnd(){return m_end;}
    QPointF getCenter();
    QLineEdit* getLineEdit(){return m_weightLineEdit;}

public slots:
    void editWeight();

signals:
    void weightEdited(GraphicEdge* e, int w);
    void needRedraw();
    void needWarning(QString s);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    GraphicNode* m_start;
    GraphicNode* m_end;
    int m_weight;
    QLineEdit* m_weightLineEdit;
    QPen m_pen = QPen(Qt::black);
};


#endif // GRAPHICEDGE_H
