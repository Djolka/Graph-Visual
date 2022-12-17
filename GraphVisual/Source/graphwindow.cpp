#include "Headers/graphwindow.h"
#include "Headers/popup.h"
#include "ui_graphwindow.h"

#include "Headers/graphtable.h"
#include "Headers/node.h"
#include "Headers/graphicnode.h"

#include "Headers/edge.h"
#include "Headers/graphicedge.h"
#include "Headers/algorithm.h"

#include <QString>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QTextEdit>
#include <QWidget>
#include <QMessageBox>
#include <iostream>

#include "Headers/algorithm.h"
#include "Headers/popup.h"
#include "ui_popup.h"

GraphWindow::GraphWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GraphWindow)
    , m_graph(new Graph(false, false))
    , m_GraphTable(new GraphTable(m_graph->isDirected(), this))
{
    ui->setupUi(this);

//    connecting scene and view
    m_GraphTable->setSceneRect(ui->graphicsView->rect());
    ui->graphicsView->setScene(m_GraphTable);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

//    connecting singals and slots
    connect(ui->pbDirected, &QPushButton::clicked, this, &GraphWindow::graphDirected);
    connect(ui->pbUndirected, &QPushButton::clicked, this, &GraphWindow::graphUndirected);
    connect(ui->pbAddNode, &QPushButton::clicked, this, &GraphWindow::AddNewEdge);
    connect(ui->teNode1, &MyTextEdit::textChanged, this, &GraphWindow::nodeNameLength);
    connect(ui->teNode2, &MyTextEdit::textChanged, this, &GraphWindow::nodeNameLength);

    connect(this, &GraphWindow::AddedNewNode, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::AddNewNodeOnTable);
    connect(this, &GraphWindow::AddedNewEdge, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::AddNewEdgeOnTable);

    connect(ui->pbDeleteAll, &QPushButton::clicked, this, &GraphWindow::DeleteGraphFromTable);
    connect(this, &GraphWindow::DeletedGraph, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::DeleteGraphFromTable, Qt::QueuedConnection);

    connect(this, &GraphWindow::NeedRedraw, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::Redraw);

    connect(ui->twRight, &QTabWidget::currentChanged, this, &GraphWindow::ChangeMode);
    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::addedNewNode, this, &GraphWindow::AddNode);
    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::addedNewEdge, this, &GraphWindow::AddEdge);
    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::edgeWeightChanged, this, &GraphWindow::changeWeight);

    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::deletedNode, this, &GraphWindow::deleteNode);
    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::deletedEdge, this, &GraphWindow::deleteEdge);

    connect(dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::needWarning, this, &GraphWindow::warning);

    connect(ui->pbRUN, &QPushButton::clicked, this, &GraphWindow::algorithm);

    connect(this, &GraphWindow::colorDFS, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::colorNodes);
    connect(this, &GraphWindow::colorBFS, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::colorNodes);

    connect(ui->pbRESET, &QPushButton::clicked, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::reset);


    fillMap();
}

GraphWindow::~GraphWindow()
{
    delete ui;
    delete m_GraphTable;
    delete m_graph;
}

void GraphWindow::fillMap() {
    m_colors.insert("off white", "#E4E8D6");
    m_colors.insert("white", "#FFFFFF");
    m_colors.insert("black", "#000000");
    m_colors.insert("navy", "#192841");
    m_colors.insert("yellow", "#ece75f");
    m_colors.insert("green", "#87ab69");
    m_colors.insert("purple", "#D9C4EC");
    m_colors.insert("blue", "#287caa");
    m_colors.insert("dark grey", "#3A3B3C");
    m_colors.insert("red", "#D0312D");

}

void GraphWindow::SaveAsPic(const QString& m_ext){
    QString dir = QDir::homePath();
    QString name = "Untilted." + m_ext;
    QString fileType = m_ext.toUpper() + "(*." + m_ext.toUpper() + ")";
    QString fileName= QFileDialog::getSaveFileName(this, "Save image", dir + "/" + name, fileType);
        if (!fileName.isNull()) {
            QPixmap pixMap = this->ui->graphicsView->grab();
            pixMap.save(fileName);
        }

}


void GraphWindow::AddNewEdge() {    
    const auto name1 = ui->teNode1->toPlainText();
    ui->teNode1->clear();

    const auto name2 = ui->teNode2->toPlainText();
    ui->teNode2->clear();

    GraphicNode* graphicNode1 = nullptr;
    GraphicNode* graphicNode2 = nullptr;
    Node* node1 = nullptr;
    Node* node2 = nullptr;

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


        if(m_graph->addEdge(node1, node2, weight)) {
            if(m_graph->isDirected()){
                ui->lw->addItem(QString::fromStdString(node1->name())+"->"+QString::fromStdString(node2->name())+"    weight="+QString::fromStdString(std::to_string(weight)));
            }else{
                ui->lw->addItem(QString::fromStdString(node1->name())+"-"+QString::fromStdString(node2->name())+"    weight="+QString::fromStdString(std::to_string(weight)));
            }

            const auto graphicEdge = new GraphicEdge(graphicNode1, graphicNode2, weight, m_graph->isDirected());
            emit AddedNewEdge(graphicEdge);
        }else{
            warning("Edge already exists");
        }

        emit NeedRedraw();
    }
}

void GraphWindow::DeleteGraphFromTable() {
    for(auto node : m_graph->nodeSet()) {
        m_graph->removeNode(node);
    }

    ui->lw->clear();
    emit DeletedGraph();
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
    if(m_graph->addEdge(n1, n2, weight)){
        if(m_graph->isDirected()){
            ui->lw->addItem(QString::fromStdString(n1->name())+"->"+QString::fromStdString(n2->name())+"    weight="+QString::fromStdString(std::to_string(weight)));
        }else{
            ui->lw->addItem(QString::fromStdString(n1->name())+"-"+QString::fromStdString(n2->name())+"    weight="+QString::fromStdString(std::to_string(weight)));
        }

    }
}
void GraphWindow::changeWeight(Node* n1, Node* n2, int weight){
    //update list

    QString edge;
    if(m_graph->isDirected()){
        edge = QString::fromStdString(n1->name()+"->"+n2->name());
    }else{
        edge = QString::fromStdString(n1->name()+"-"+n2->name());
    }

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

    if(m_graph->isDirected()){
        ui->lw->addItem(QString::fromStdString(n1->name())+"->"+QString::fromStdString(n2->name())+"    weight="+QString::fromStdString(std::to_string(weight)));
    }else{
        ui->lw->addItem(QString::fromStdString(n1->name())+"-"+QString::fromStdString(n2->name())+"    weight="+QString::fromStdString(std::to_string(weight)));
    }


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

void GraphWindow::graphDirected() {

    if(m_graph->nodeSet().empty()){
            ui->pbUndirected->setEnabled(true);
            ui->pbDirected->setEnabled(false);
            m_graph->setDirected(true);
            shouldPopUpUndir = true;
    }else if(shouldPopUpDir){
        switch(QMessageBox::question(this, "Error",
                "<FONT COLOR='#FFEFD5'>Current progress will be deleted if you change to directed graph, click yes to continue</FONT>",

                QMessageBox::Yes |
                QMessageBox::No |

                QMessageBox::No) )
        {
          case QMessageBox::Yes:
            ui->pbUndirected->setEnabled(true);
            emit ui->pbDeleteAll->clicked();
            ui->pbDirected->setEnabled(false);
            m_graph->setDirected(true);
            shouldPopUpUndir = true;
            shouldPopUpDir = false;
            break;
          case QMessageBox::No:
            shouldPopUpUndir=false;
            ui->pbUndirected->setChecked(true);
            ui->pbUndirected->setEnabled(true);
            ui->pbUndirected->click();
            ui->pbUndirected->setEnabled(false);
            break;
          default:
            break;
        }
    }
    return;
}



void GraphWindow::graphUndirected() {
    if(m_graph->nodeSet().empty()){
            ui->pbUndirected->setEnabled(false);
            ui->pbDirected->setEnabled(true);
            m_graph->setDirected(false);
            shouldPopUpDir = true;
    }else if(shouldPopUpUndir){
        switch(QMessageBox::question(this, "Error",
                "<FONT COLOR='#FFEFD5'>Current progress will be deleted if you change to undirected graph, click yes to continue</FONT>",

                QMessageBox::Yes |
                QMessageBox::No |

                QMessageBox::No) )
        {
          case QMessageBox::Yes:
            ui->pbUndirected->setEnabled(false);
            ui->pbDirected->setEnabled(true);
            emit ui->pbDeleteAll->clicked();
            m_graph->setDirected(false);
            shouldPopUpDir = true;
            shouldPopUpUndir = false;
            break;
          case QMessageBox::No:
            shouldPopUpDir=false;
            ui->pbDirected->setChecked(true);
            ui->pbDirected->setEnabled(true);
            ui->pbDirected->click();
            ui->pbDirected->setEnabled(false);
            break;
          default:
            break;
        }
    }
    return;
}

        


void GraphWindow::on_actionSaveAsPng_triggered() {
    GraphWindow::SaveAsPic("png");
}


void GraphWindow::on_actionSaveAsJpg_triggered() {
    GraphWindow::SaveAsPic("jpeg");
}

void GraphWindow::on_pbUndirected_pressed() {
    ui->pbUndirected->setStyleSheet("background-color: rgb(45, 74, 90); color: rgb(211, 215, 207); border-color: rgb(10, 10, 10); border-style: solid; border-width: 2px");
    ui->pbDirected->setStyleSheet("background-color: #287caa; color: rgb(245, 243, 242); border-color: #287caa; border-style: solid; border-width: 2px");
}

void GraphWindow::on_pbDirected_pressed() {
    ui->pbUndirected->setStyleSheet("background-color: #287caa; color: rgb(211, 215, 207); border-color: #287caa; border-style: solid; border-width: 2px");
    ui->pbDirected->setStyleSheet("background-color: rgb(45, 74, 90); color: rgb(245, 243, 242); border-color: rgb(10, 10, 10); border-style: solid; border-width: 2px");
}

void GraphWindow::on_actionClose_triggered() {
    // TODO ask user if they want to save
    switch(QMessageBox::question(this, "Warning",
            "<FONT COLOR='#FFEFD5'>Do you want to save changes?</FONT>",

                QMessageBox::Save |
                QMessageBox::No |
                QMessageBox::Cancel |

                QMessageBox::Cancel) )
    {
      case QMessageBox::Save:
        qDebug("Yes");
        //implement saving to current project if it is already saved, or save to new project if it doesn't exist and than leaving
        //close();
        break;
      case QMessageBox::No:
        qDebug("No");
        close();
        break;
      case QMessageBox::Cancel:
        qDebug("Cancel");
        break;
      default:
        break;
    }
    return;
}

// delete this
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

void GraphWindow::on_pbSave_clicked() {
    GraphicNode::m_height = ui->sbRadius->value();
    GraphicNode::m_width = ui->sbRadius->value();
    GraphicNode::m_color = QColor(m_colors[ui->cbNodecolor->currentText()]);
    GraphicEdge::m_color = QColor(m_colors[ui->cbEdgecolor->currentText()]);
    ui->graphicsView->setBackgroundBrush(QColor(m_colors[ui->cbBgcolor->currentText()]));

    if (ui->cbEdgecolor->currentText() == ui->cbBgcolor->currentText()) {
        ui->lblMsg->setText(QString("\n\n\nWatch out! Your edges are the same color as the background."));
        ui->lblMsg->setStyleSheet(QString("background-image: url(:/new/rec/Resources/warning.png)"));
    } else {
        ui->lblMsg->setText(QString());
        ui->lblMsg->setStyleSheet(QString());
    }
}


//void GraphWindow::algorithm() {

//    QString nodeName;
//    Popup *p = new Popup();
//    if(p->exec() == QDialog::Accepted) {
//        nodeName = p->getNodeName();
//    }

//    Node *node = m_graph->getNode(nodeName.toStdString());

//    if(node != nullptr && ui->pbDFS->isEnabled()) { // node exists
//        QHash<Node*, bool> visited;
//        QList<Node*> result;

//        QWidget::setEnabled(false);
//        a->DFS(node, visited, result);
//        emit colorDFS(result);
//        QMessageBox::information(this, "Finished", "<FONT COLOR='#FFEFD5'>Algorithm is finished</FONT>");
//        QWidget::setEnabled(true);
//    }
//    else { // node doesn't exist
////        std::cout << "Searched node does not exist\n";
//        QMessageBox::warning(this, "Error", "<FONT COLOR='#FFEFD5'>Node with this name does not exists</FONT>");
//    }

//}



void GraphWindow::algorithm() {
    auto a = new Algorithm();
    if(ui->pbBFS->isChecked()){
        auto p = new Popup();
        if(p->exec() == QDialog::Accepted){
            QString nodeName = p->getNodeName();
            Node* node = m_graph->getNode(nodeName.toStdString());
            if(node != nullptr){
                QWidget::setEnabled(false);
                QList<Node*> result = a->BFS(node);
                emit colorBFS(result, true);
                QMessageBox::information(this, "Finished", "<FONT COLOR='#FFEFD5'>Algorithm is finished</FONT>");
                QWidget::setEnabled(true);
            }
            else{
                warning("Node with that name does not exist");
            }
        }
    }
    else if(ui->pbDFS->isChecked()){
        auto p = new Popup();
        if(p->exec() == QDialog::Accepted){
            QString nodeName = p->getNodeName();
            Node* node = m_graph->getNode(nodeName.toStdString());
            if(node != nullptr){
                QHash<Node*, bool> visited;
                QList<Node*> result;

                QWidget::setEnabled(false);
                a->DFS(node, visited, result);
                emit colorDFS(result, true);
                QMessageBox::information(this, "Finished", "<FONT COLOR='#FFEFD5'>Algorithm is finished</FONT>");
                QWidget::setEnabled(true);
            }
            else{
                warning("Node with that name does not exist");
            }
        }
    }
}
