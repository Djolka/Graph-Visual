#ifndef GRAPHTABLE_H
#define GRAPHTABLE_H

#include <QGraphicsScene>

class GraphicNode;
class GraphicEdge;

class GraphTable : public QGraphicsScene {
public:
    explicit GraphTable(QObject *parenet = nullptr);

    QVector<GraphicNode *> getNodes();
    QVector<GraphicEdge *> getEdges();

public slots:
    void AddNewNodeOnTable(GraphicNode *node);
    void AddNewEdgeOnTable(GraphicEdge *edge);
    void DeleteAllNodesFromTable();
    void Redraw();

private:
    void PlaceNodeOnTable(GraphicNode *node);

    QVector<GraphicNode *> m_Nodes;
    QVector<GraphicEdge *> m_Edges;
};



#endif // GRAPHTABLE_H
