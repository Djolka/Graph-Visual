#ifndef GRAPHICEDGE_H
#define GRAPHICEDGE_H

#include <QGraphicsLineItem>
#include"graphicnode.h"
#include<QLineEdit>
#include<QPen>
#include<QPolygon>

class GraphicEdge : public QObject, public QGraphicsLineItem {
    Q_OBJECT
public:
    GraphicEdge(GraphicNode* start, GraphicNode* end, int weight, bool dir);
    ~GraphicEdge();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override;
    QPainterPath shape() const override;

    int getWeight(){return m_weight;}
    GraphicNode* getStart(){return m_start;}
    GraphicNode* getEnd(){return m_end;}
    QPointF getCenter();
    QLineEdit* getLineEdit(){return m_weightLineEdit;}

    void setPen(QPen pen, bool x){m_pen = pen;m_algorithm=x;}

    static QColor m_color;

public slots:
    void editWeight();

signals:
    void weightEdited(GraphicEdge* e, int w);
    void needRedraw();
    void needWarning(QString s);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    void calculate(QLineF *newLine, QPointF *controlPoint, QLineF *ghostLine, QPointF& arrowP1, QPointF& arrowP2);

    GraphicNode* m_start;
    GraphicNode* m_end;
    qreal m_arrowSize = 15;
    int m_weight;
    QLineEdit* m_weightLineEdit;
    QPen m_pen = QPen(Qt::black);
    QBrush m_brush = QBrush(Qt::black);
    bool directed;
    bool m_algorithm = false;
};


#endif // GRAPHICEDGE_H
