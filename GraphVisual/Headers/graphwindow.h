#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include<QPointF>

#include"Headers/graphicedge.h"

class Node;
class GraphicNode;
class QGraphicsScene;
//class GraphicEdge;

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

private slots:
    void AddNewNode();
    void DeleteAllNodes();

private:
    Ui::GraphWindow *ui;
    QGraphicsScene *m_GraphTable;
    QVector<Node *> m_Nodes;
    QVector<GraphicNode* > m_GNodes;
};
#endif // GRAPHWINDOW_H
