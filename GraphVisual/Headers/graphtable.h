#ifndef GRAPHTABLE_H
#define GRAPHTABLE_H

#include <QGraphicsScene>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsLineItem>

#include"Headers/node.h"
class GraphicNode;
class GraphicEdge;

class GraphTable : public QGraphicsScene {
//Q_OBJECT
public:
    GraphTable(QObject *parenet = nullptr);
//    virtual ~GraphTable(){}

    QVector<GraphicNode *> getNodes();
    QVector<GraphicEdge *> getEdges();

    void mousePressEvent ( QGraphicsSceneMouseEvent * event ) override;
//    void mouseMoveEvent (QGraphicsSceneMouseEvent * event ) override;
    void setDrawingMode(bool x);
    void deleteTmp(){tmp=nullptr;}

public slots:
    void AddNewNodeOnTable(GraphicNode *node);
    void AddNewEdgeOnTable(GraphicEdge *edge);
    void DeleteAllNodesFromTable();
    void Redraw();

//signals:
//    void addedNewNode(Node* node);

private:
    void PlaceNodeOnTable(GraphicNode *node);

    QVector<GraphicNode *> m_Nodes;
    QVector<GraphicEdge *> m_Edges;

    bool m_drawingMode = true;
    GraphicNode* tmp = nullptr;
//    QGraphicsLineItem* lineToDraw;
};



#endif // GRAPHTABLE_H
