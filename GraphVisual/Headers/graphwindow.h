#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include<QPointF>

#include"Headers/graphicedge.h"
#include"Headers/graph.h"

class Node;
class GraphicNode;
class QGraphicsScene;

QT_BEGIN_NAMESPACE
namespace Ui { class GraphWindow; }
QT_END_NAMESPACE

class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    GraphWindow(QWidget *parent = nullptr);
    ~GraphWindow();

signals:
    void AddedNewNode(GraphicNode *);
    void AddedNewEdge(GraphicEdge *);
    void DeletedAllNodes();
    void NeedRedraw();

private slots:
    void AddNewEdge();
    void DeleteAllNodes();
    void ChangeMode(int index);
    void AddNode(Node* node);
    void AddEdge(Node* n1, Node* n2);
    void changeWeight(Node* n1, Node* n2, int weight);

private:
    Ui::GraphWindow *ui;
    QGraphicsScene *m_GraphTable;
    Graph *m_graph;
};
#endif // GRAPHWINDOW_H
