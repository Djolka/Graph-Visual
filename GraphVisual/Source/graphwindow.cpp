#include "Headers/graphwindow.h"
#include "ui_graphwindow.h"

#include "Headers/graphtable.h"
#include "Headers/node.h"
#include "Headers/graphicnode.h"

#include "Headers/edge.h"
#include "Headers/graphicedge.h"

#include <QString>
#include <QListWidgetItem>

GraphWindow::GraphWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GraphWindow)
    , m_GraphTable(new GraphTable(this))
    , m_graph(new Graph(false, false))
{
    ui->setupUi(this);

//    connecting scene and view
    m_GraphTable->setSceneRect(ui->graphicsView->rect());
    ui->graphicsView->setScene(m_GraphTable);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

//    connecting singals and slots
    connect(ui->pbAddNode, &QPushButton::clicked, this, &GraphWindow::AddNewEdge);
    connect(this, &GraphWindow::AddedNewNode, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::AddNewNodeOnTable);

    connect(ui->pbDeleteAll, &QPushButton::clicked, this, &GraphWindow::DeleteAllNodes);
    connect(this, &GraphWindow::DeletedAllNodes, dynamic_cast<GraphTable *>(m_GraphTable),&GraphTable::DeleteAllNodesFromTable);

    connect(this, &GraphWindow::AddedNewEdge, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::AddNewEdgeOnTable);

    connect(this, &GraphWindow::NeedRedraw, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::Redraw);

    connect(ui->menu_right, &QTabWidget::currentChanged, this, &GraphWindow::ChangeMode);
    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::addedNewNode, this, &GraphWindow::AddNode);
    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::addedNewEdge, this, &GraphWindow::AddEdge);
    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::edgeWeightChanged, this, &GraphWindow::changeWeight);

    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::deletedNode, this, &GraphWindow::deleteNode);
}

GraphWindow::~GraphWindow()
{
    delete ui;

//    for(auto node : m_Nodes) {
//        delete node;
//    }

}


void GraphWindow::AddNewEdge() {
    const auto name1 = ui->teNode1->toPlainText();
    ui->teNode1->clear();

    GraphicNode* graphicNode1;
    if(!m_graph->hasNode(name1.toStdString())){
        const auto node1 = new Node(name1.toStdString());

        m_graph->addNode(node1);

        graphicNode1 = new GraphicNode(node1);
        m_GraphTable->addItem(graphicNode1);

        emit AddedNewNode(graphicNode1);
    }
    else{
        for(GraphicNode* n : dynamic_cast<GraphTable *>(m_GraphTable)->getNodes()){
            if(n->getNode()->name() == name1.toStdString()){
                graphicNode1 = n;
                break;
            }
        }
    }


    const auto name2 = ui->teNode2->toPlainText();
    ui->teNode2->clear();

    GraphicNode* graphicNode2;
    if(!m_graph->hasNode(name2.toStdString())){
        const auto node2 = new Node(name2.toStdString());

        m_graph->addNode(node2);

        graphicNode2 = new GraphicNode(node2);
        m_GraphTable->addItem(graphicNode2);

        emit AddedNewNode(graphicNode2);
    }
    else{
        for(GraphicNode* n : dynamic_cast<GraphTable *>(m_GraphTable)->getNodes()){
            if(n->getNode()->name() == name2.toStdString()){
                graphicNode2 = n;
                break;
            }
        }
    }

    const auto weight = ui->teWeight->toPlainText().toInt();
    //m_graph->addEdge() TODO

    const auto graphicEdge = new GraphicEdge(graphicNode1, graphicNode2, weight);

    emit AddedNewEdge(graphicEdge);
    emit NeedRedraw();
}

void GraphWindow::DeleteAllNodes() {
//    for(auto node : m_Nodes) {
//        delete node;
//    }
//    m_Nodes.clear();
}

void GraphWindow::ChangeMode(int index) {
    if(index == 2){
        dynamic_cast<GraphTable*>(m_GraphTable)->setDrawingMode(true);
        dynamic_cast<GraphTable*>(m_GraphTable)->setDeleteMode(false);
    }
    else if(index == 3){
        dynamic_cast<GraphTable*>(m_GraphTable)->setDeleteMode(true);
        dynamic_cast<GraphTable*>(m_GraphTable)->setDrawingMode(false);
        dynamic_cast<GraphTable*>(m_GraphTable)->setHasTmp(false);
    }
    else{
        dynamic_cast<GraphTable*>(m_GraphTable)->setDrawingMode(false);
        dynamic_cast<GraphTable*>(m_GraphTable)->setHasTmp(false);
        dynamic_cast<GraphTable*>(m_GraphTable)->setDeleteMode(false);
    }
}

void GraphWindow::AddNode(Node* node) {
    m_graph->addNode(node);
}
void GraphWindow::AddEdge(Node* n1, Node* n2) {
    m_graph->addEdge(n1, n2, 1);
}
void GraphWindow::changeWeight(Node* n1, Node* n2, int weight){
    m_graph->getEdge(n1, n2)->setWeight(weight);
}

void GraphWindow::deleteNode(Node* node) {
    m_graph->removeNode(node);
}
