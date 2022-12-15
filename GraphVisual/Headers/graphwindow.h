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
    QMap<QString, QString> m_colors;
    void fillMap();
    void SaveAsPic(const QString& m_ext);

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
    void deleteNode(Node* node);
    void deleteEdge(Node* node1, Node* node2);

    void on_actionSaveAsPng_triggered();
    void on_actionSaveAsJpg_triggered();

    void on_pbUndirected_pressed();

    void on_pbUndirected_released();

    void on_pbDirected_pressed();

    void on_pbUndirected_clicked();

    void on_actionClose_triggered();

    void on_pbAddNode_clicked();

    void on_pbSave_clicked();

private:
    Ui::GraphWindow *ui;
    QGraphicsScene *m_GraphTable;
    Graph *m_graph;
};
#endif // GRAPHWINDOW_H
