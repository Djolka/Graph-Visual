#ifndef GRAPHTABLE_H
#define GRAPHTABLE_H

#include<QGraphicsScene>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsLineItem>
#include<QLineEdit>
#include<QWidget>

#include"Headers/node.h"
class GraphicNode;
class GraphicEdge;

class GraphTable : public QGraphicsScene {
Q_OBJECT
public:
    GraphTable(QObject *parenet = nullptr);
    virtual ~GraphTable(){}

    QVector<GraphicNode *> getNodes();
    QVector<GraphicEdge *> getEdges();

    void mousePressEvent ( QGraphicsSceneMouseEvent * event ) override;
//    void mouseMoveEvent (QGraphicsSceneMouseEvent * event ) override;
    void setDrawingMode(bool x);
    void setHasTmp(bool x);

public slots:
    void AddNewNodeOnTable(GraphicNode *node);
    void AddNewEdgeOnTable(GraphicEdge *edge);
    void DeleteAllNodesFromTable();
    void Redraw();
    void editWeight(GraphicEdge* edge, int w);

signals:
    void addedNewNode(Node* node);
    void addedNewEdge(Node* node1, Node* node2);
    void edgeWeightChanged(Node* node1, Node* node2, int weight);

private:
    void PlaceNodeOnTable(GraphicNode *node);

    QVector<GraphicNode *> m_Nodes;
    QVector<GraphicEdge *> m_Edges;

    bool m_drawingMode = true;
    bool m_hasTmp = false;
    GraphicNode* m_tmp;
    QGraphicsLineItem* m_lineToDraw;

//    QVector<QGraphicsLineItem *> _veze;
};



#endif // GRAPHTABLE_H
