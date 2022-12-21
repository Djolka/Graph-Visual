#ifndef GRAPHTABLE_H
#define GRAPHTABLE_H

#include<QGraphicsScene>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsLineItem>
#include<QLineEdit>
#include<QWidget>
#include<QGraphicsProxyWidget>

#include "Headers/node.h"
#include "Headers/graphicnode.h"
#include "Headers/graphicedge.h"

class GraphTable : public QGraphicsScene {
Q_OBJECT
public:
    explicit GraphTable(bool dir, QObject *parenet = nullptr);
    virtual ~GraphTable(){}

    QVector<GraphicNode *> getNodes();
    QVector<GraphicEdge *> getEdges();

    bool hasGraphicEdge(GraphicNode *u, GraphicNode *v);

    void mousePressEvent ( QGraphicsSceneMouseEvent * event ) override;
//    void mouseMoveEvent (QGraphicsSceneMouseEvent * event ) override;
    void setDrawingMode(bool x);
    void setHasTmp(bool x);
    void setDeleteMode(bool x);

public slots:
    void AddNewNodeOnTable(GraphicNode *node);
    void AddNewEdgeOnTable(GraphicEdge *edge);
    void DeleteGraphFromTable();
    void Redraw();
    void editWeight(GraphicEdge* edge, int w);
    void Warning (QString s);

signals:
    void addedNewNode(Node* node);
    void addedNewEdge(Node* node1, Node* node2, int weight);
    void edgeWeightChanged(Node* node1, Node* node2, int weight);
    void deletedNode(Node* node);
    void deletedEdge(Node* node1, Node* node2);
    void needWarning(QString s);

private:
    void PlaceNodeOnTable(GraphicNode *node);

    QVector<GraphicNode *> m_Nodes;
    QVector<GraphicEdge *> m_Edges;

    bool m_drawingMode = false;
    bool m_hasTmp = false;
    GraphicNode* m_tmp;
    QGraphicsLineItem* m_lineToDraw;
    bool directed;

    bool m_deleteMode = false;


//    QVector<QGraphicsLineItem *> _veze;
};



#endif // GRAPHTABLE_H
