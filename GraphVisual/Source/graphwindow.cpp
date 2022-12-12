#include "Headers/graphwindow.h"
#include "ui_graphwindow.h"

#include "Headers/graphtable.h"
#include "Headers/node.h"
#include "Headers/graphicnode.h"

#include "Headers/edge.h"
#include "Headers/graphicedge.h"

#include <QString>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QTextEdit>
#include <QWidget>

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

    connect(ui->twRight, &QTabWidget::currentChanged, this, &GraphWindow::ChangeMode);
    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::addedNewNode, this, &GraphWindow::AddNode);
    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::addedNewEdge, this, &GraphWindow::AddEdge);
    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::edgeWeightChanged, this, &GraphWindow::changeWeight);
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
    }
    else{
        dynamic_cast<GraphTable*>(m_GraphTable)->setDrawingMode(false);
        dynamic_cast<GraphTable*>(m_GraphTable)->setHasTmp(false);
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



void GraphWindow::on_actionSaveAsPng_triggered() {

        QString dir = QDir::homePath();
        QString name = "Untilted.png";
        QString fileName= QFileDialog::getSaveFileName(this, "Save image", dir + "/" + name, "PNG (*.PNG)" );
            if (!fileName.isNull()) {
                QPixmap pixMap = this->ui->graphicsView->grab();
                pixMap.save(fileName);
            }
}


void GraphWindow::on_actionSaveAsJpg_triggered(){

        QString dir = QDir::homePath();
        QString name = "Untilted.jpeg";
        QString fileName= QFileDialog::getSaveFileName(this, "Save image", dir + "/" + name, "JPEG (*.JPEG)" );
            if (!fileName.isNull()) {
                QPixmap pixMap = this->ui->graphicsView->grab();
                pixMap.save(fileName);
            }
}

void GraphWindow::on_pbUndirected_pressed(){   
    ui->pbUndirected->setStyleSheet("background-color: rgb(45, 74, 90); color: rgb(211, 215, 207); border-color: rgb(10, 10, 10); border-style: solid; border-width: 2px");
    ui->pbDirected->setStyleSheet("background-color: #287caa; color: rgb(245, 243, 242); border-color: #287caa; border-style: solid; border-width: 2px");
    // TODO undirected edges}
}

void GraphWindow::on_pbDirected_pressed(){
    ui->pbUndirected->setStyleSheet("background-color: #287caa; color: rgb(211, 215, 207); border-color: #287caa; border-style: solid; border-width: 2px");
    ui->pbDirected->setStyleSheet("background-color: rgb(45, 74, 90); color: rgb(245, 243, 242); border-color: rgb(10, 10, 10); border-style: solid; border-width: 2px");
    // TODO directed edges
}

void GraphWindow::on_actionClose_triggered()
{
    // TODO ask user if they want to save
    close();
}

// delet this
void GraphWindow::on_pbUndirected_released(){}
void GraphWindow::on_pbUndirected_clicked(){}
void GraphWindow::on_pbAddNode_clicked(){}

