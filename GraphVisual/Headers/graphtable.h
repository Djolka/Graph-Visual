#ifndef GRAPHTABLE_H
#define GRAPHTABLE_H

#include <QGraphicsScene>
#include<QGraphicsSceneMouseEvent>

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
    void setDrawingMode(bool x);

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
};



#endif // GRAPHTABLE_H
