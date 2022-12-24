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
    QMap<QString, int> m_indices;
    void fillMap();
    void indexColors();
    void SaveAsPic(const QString& m_ext);
    bool nodeExists(std::string name);
    void click();
    void unesiVrednost(std::string key, std::string key2, std::string value);

signals:
    void AddedNewNode(GraphicNode *);
    void AddedNewEdge(GraphicEdge *);
    void DeletedGraph();
    void NeedRedraw();
    void colorBFS(QList<Node*> result);

private slots:
    void AddNewEdge();
    void DeleteGraphFromTable();
    void ChangeMode(int index);
    void AddNode(Node* node);
    void AddEdge(Node* n1, Node* n2, int weight);
    void changeWeight(Node* n1, Node* n2, int weight);
    void deleteNode(Node* node);
    void deleteEdge(Node* node1, Node* node2);
    void warning(QString s);
    void nodeNameLength();

    void graphDirected();
    void graphUndirected();

    void on_actionSaveAsPng_triggered();
    void on_actionSaveAsJpg_triggered();

    void on_pbUndirected_pressed();

    void on_pbUndirected_released();

    void on_pbDirected_pressed();

    void on_pbUndirected_clicked();

    void on_actionClose_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_pbAddNode_clicked();

    void on_pbSave_clicked();

    void algorithm();

private:
    Ui::GraphWindow *ui;
    Graph *m_graph;
    QGraphicsScene *m_GraphTable;
    bool shouldPopUpUndir = false;
    bool shouldPopUpDir = true;

};
#endif // GRAPHWINDOW_H
