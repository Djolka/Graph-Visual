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
{
    ui->setupUi(this);

//    connecting scene and view
    m_GraphTable->setSceneRect(ui->gv_graphTable->rect());
    ui->gv_graphTable->setScene(m_GraphTable);
    ui->gv_graphTable->setRenderHint(QPainter::Antialiasing);
    ui->gv_graphTable->setAlignment(Qt::AlignTop | Qt::AlignLeft);

//    connecting singals and slots
    connect(ui->pbAddNode, &QPushButton::clicked, this, &GraphWindow::AddNewNode);
    connect(this, &GraphWindow::AddedNewNode, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::AddNewNodeOnTable);

    connect(ui->pbDeleteAll, &QPushButton::clicked, this, &GraphWindow::DeleteAllNodes);
    connect(this, &GraphWindow::DeletedAllNodes, dynamic_cast<GraphTable *>(m_GraphTable),&GraphTable::DeleteAllNodesFromTable);

    connect(this, &GraphWindow::AddedNewEdge, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::AddNewEdgeOnTable);

}

GraphWindow::~GraphWindow()
{
    delete ui;

    for(auto node : m_Nodes) {
        delete node;
    }

}

//TODO: provera da li cvor vec postoji
void GraphWindow::AddNewNode() {
    const auto name1 = ui->teNode1->toPlainText();
    const auto node1 = new Node(name1.toStdString());

    m_Nodes.push_back(node1);

    const auto graphicNode1 = new GraphicNode(node1);
    m_GraphTable->addItem(graphicNode1);

    emit AddedNewNode(graphicNode1);



    const auto name2 = ui->teNode2->toPlainText();
    const auto node2 = new Node(name2.toStdString());

    m_Nodes.push_back(node2);

    const auto graphicNode2 = new GraphicNode(node2);
    m_GraphTable->addItem(graphicNode2);

    m_GNodes.push_back(graphicNode2);

    emit AddedNewNode(graphicNode2);

    const auto weight = ui->teWeight->toPlainText().toInt();
    //const auto edge = new Edge(std::make_pair(node, node2), 1);
    //m_Edges.push_back(edge);

    const auto graphicEdge = new GraphicEdge(graphicNode1, graphicNode2, weight);
    m_GraphTable->addItem(graphicEdge);

    emit AddedNewEdge(graphicEdge);
}

void GraphWindow::DeleteAllNodes() {
    for(auto node : m_Nodes) {
        delete node;
    }
    m_Nodes.clear();

    emit DeletedAllNodes();
}




