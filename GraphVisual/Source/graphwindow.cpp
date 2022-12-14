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
#include <QMessageBox>

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
    connect(ui->teNode1, &MyTextEdit::textChanged, this, &GraphWindow::nodeNameLength);
    connect(ui->teNode2, &MyTextEdit::textChanged, this, &GraphWindow::nodeNameLength);

    connect(this, &GraphWindow::AddedNewNode, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::AddNewNodeOnTable);

    connect(ui->pbDeleteAll, &QPushButton::clicked, this, &GraphWindow::DeleteAllNodes);
    connect(this, &GraphWindow::DeletedAllNodes, dynamic_cast<GraphTable *>(m_GraphTable),&GraphTable::DeleteAllNodesFromTable);

    connect(this, &GraphWindow::AddedNewEdge, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::AddNewEdgeOnTable);

    connect(this, &GraphWindow::NeedRedraw, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::Redraw);

    connect(ui->twRight, &QTabWidget::currentChanged, this, &GraphWindow::ChangeMode);
    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::addedNewNode, this, &GraphWindow::AddNode);
    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::addedNewEdge, this, &GraphWindow::AddEdge);
    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::edgeWeightChanged, this, &GraphWindow::changeWeight);

    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::deletedNode, this, &GraphWindow::deleteNode);
    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::deletedEdge, this, &GraphWindow::deleteEdge);

    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::needWarning, this, &GraphWindow::warning);

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

    const auto name2 = ui->teNode2->toPlainText();
    ui->teNode2->clear();

    const auto w = ui->teWeight->toPlainText();
    int weight = w.toInt();
    ui->teWeight->clear();


    if(name1.length()==0 || name2.length()==0){
        warning(QString("You have to insert node name"));
    }
    else if(weight == 0){
        warning(QString("Edge weight must be a number"));
    }
    else if(name1 == name2){
        warning(QString("Node names are the same"));
    }
    else{
        Node* node1 = nullptr;
        GraphicNode* graphicNode1 = nullptr;
        if(!m_graph->hasNode(name1.toStdString())){
            node1 = new Node(name1.toStdString());

            m_graph->addNode(node1);

            graphicNode1 = new GraphicNode(node1);
            m_GraphTable->addItem(graphicNode1);

            emit AddedNewNode(graphicNode1);
        }
        else{
            for(GraphicNode* n : dynamic_cast<GraphTable *>(m_GraphTable)->getNodes()){
                if(n->getNode()->name() == name1.toStdString()){
                    node1 = n->getNode();
                    graphicNode1 = n;
                    break;
                }
            }
        }

        Node* node2 = nullptr;
        GraphicNode* graphicNode2 = nullptr;
        if(!m_graph->hasNode(name2.toStdString())){
            node2 = new Node(name2.toStdString());

            m_graph->addNode(node2);

            graphicNode2 = new GraphicNode(node2);
            m_GraphTable->addItem(graphicNode2);

            emit AddedNewNode(graphicNode2);
        }
        else{
            for(GraphicNode* n : dynamic_cast<GraphTable *>(m_GraphTable)->getNodes()){
                if(n->getNode()->name() == name2.toStdString()){
                    node2 = n->getNode();
                    graphicNode2 = n;
                    break;
                }
            }
        }



        // TODO: if edge exists


        //else:
        AddEdge(node1, node2, weight);
        GraphicEdge* graphicEdge = new GraphicEdge(graphicNode1, graphicNode2, weight);

        emit AddedNewEdge(graphicEdge);
        emit NeedRedraw();
    }
}

void GraphWindow::DeleteAllNodes() {
//    for(auto node : m_Nodes) {
//        delete node;
//    }
//    m_Nodes.clear();
//    emit DeletedAllNodes();
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
void GraphWindow::AddEdge(Node* n1, Node* n2, int weight) {
    m_graph->addEdge(n1, n2, weight);
    ui->lw->addItem(QString::fromStdString(n1->name())+"->"+QString::fromStdString(n2->name())+"    weight="+QString::fromStdString(std::to_string(weight)));
}
void GraphWindow::changeWeight(Node* n1, Node* n2, int weight){
    //update list

    QString edge = QString::fromStdString(n1->name()+"->"+n2->name());
    int n = ui->lw->count();
    for(int i=0;i<n;++i){
        auto item = ui->lw->item(i);
        QString  text = item->text().trimmed();
        if(text.startsWith(edge)){
            auto item1 = ui->lw->takeItem(i);
            delete item1;
            break;
        }
    }
    ui->lw->addItem(QString::fromStdString(n1->name())+"->"+QString::fromStdString(n2->name())+"    weight="+QString::fromStdString(std::to_string(weight)));

    m_graph->getEdge(n1, n2)->setWeight(weight);
}
void GraphWindow::warning(QString s) {
    QMessageBox::warning(this, "Error", "<FONT COLOR='#FFEFD5'>"+s+"</FONT>");
}
void GraphWindow::nodeNameLength() {
    auto text = ui->teNode1->toPlainText();

    if (text.length() > 5){
        text.chop(text.length() - 5); // Cut off at 5 characters
        ui->teNode1->setPlainText(text); // Reset text

        QTextCursor cursor = ui->teNode1->textCursor();
        cursor.setPosition(ui->teNode1->document()->characterCount() - 1);
        ui->teNode1->setTextCursor(cursor);
    }

    text = ui->teNode2->toPlainText();

    if (text.length() > 5){
        text.chop(text.length() - 5); // Cut off at 5 characters
        ui->teNode2->setPlainText(text); // Reset text

        QTextCursor cursor = ui->teNode2->textCursor();
        cursor.setPosition(ui->teNode2->document()->characterCount() - 1);
        ui->teNode2->setTextCursor(cursor);
    }
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


void GraphWindow::deleteNode(Node* node) {
    m_graph->removeNode(node);
}
void GraphWindow::deleteEdge(Node* node1, Node* node2) {

    QString edge = QString::fromStdString(node1->name()+"->"+node2->name());

    int n = ui->lw->count();
    for(int i=0;i<n;++i){
        auto item = ui->lw->item(i);

        QString  text = item->text().trimmed();

        if(text.startsWith(edge)){
            auto item1 = ui->lw->takeItem(i);
            delete item1;
            break;
        }
    }

    m_graph->removeEdge(node1, node2);
}
