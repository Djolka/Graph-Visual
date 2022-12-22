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
#include <iostream>
#include <QShortcut>
#include <math.h>
#include <QTime>

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
    int weight = w == "" ? 1 : w.toInt();
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
                    node1 = graphicNode1->getNode();
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
                    node2 = graphicNode2->getNode();
                    break;
                }
            }
        }


        if(m_graph->addEdge(node1, node2, weight)) {
            ui->lw->addItem(QString::fromStdString(node1->name())+"->"+QString::fromStdString(node2->name())+"    weight="+QString::fromStdString(std::to_string(weight)));
            const auto graphicEdge = new GraphicEdge(graphicNode1, graphicNode2, weight, m_graph->isDirected());
            emit AddedNewEdge(graphicEdge);
        }

        emit NeedRedraw();
    }

    std::cout << "Num of nodes: " << m_graph->nodeSet().size() << std::endl;
    std::cout << "Num of edges: " << m_graph->edgeSet().size() << std::endl;
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
    std::cout << "Num of nodes: " << m_graph->nodeSet().size() << std::endl;
}
void GraphWindow::AddEdge(Node* n1, Node* n2, int weight) {
    if(m_graph->addEdge(n1, n2, weight)){
        ui->lw->addItem(QString::fromStdString(n1->name())+"->"+QString::fromStdString(n2->name())+"    weight="+QString::fromStdString(std::to_string(weight)));
    }

    std::cout << "Num of edges: " << m_graph->edgeSet().size() << std::endl;
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

void GraphWindow::graphDirected() {
    if(shouldPopUpDir){
//        QMessageBox *msg = new QMessageBox();
        switch(QMessageBox::question(
                    this,
                    tr("Warning"),
                    tr("Current progress will be deleted if you change to directed graph, click yes to continue"),

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
            ui->pbUndirected->setChecked(true);
            ui->pbUndirected->setEnabled(true);
            ui->pbUndirected->click();
            ui->pbUndirected->setEnabled(false);
            break;
          default:
            break;
        }
//        msg->setStyleSheet("color:white;background:white"); //not working
    }


}



void GraphWindow::graphUndirected() {
    if(shouldPopUpUndir){
        //pop-up warning window
        QMessageBox *msg = new QMessageBox();
        switch(msg->question(
                    this,
                    tr("Warning"),
                    tr("Current progress will be deleted if you change to undirected graph, click yes to continue"),

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
            ui->pbDirected->setChecked(true);
            ui->pbDirected->setEnabled(true);
            ui->pbDirected->click();
            ui->pbDirected->setEnabled(false);
            break;
          default:
            break;
        }
        msg->setStyleSheet("background:white");
    }else{
        return;
    }

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
    close();
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

void GraphWindow::gravityDelay(){
        QTime dieTime = QTime::currentTime().addMSecs(5);
        while(QTime::currentTime() < dieTime){
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
}

void GraphWindow::on_pbBeautify_clicked()
{

    // TODO ----------------------------------------
    // add center of gravity
    // fix parametars and num of iters

    int numOfIters = 500;

    double C = 0.2; // relative force strength
    double K = 50.0; // optimal distance
    double pointsDistance = 0.0;
    QPointF normalizedVector = QPointF(0, 0);
    double directionCorrection = 1.0;

    QPointF repulsiveForce = QPointF(0, 0);
    QPointF attractionForce = QPointF(0, 0);
    QPointF moveForce = QPointF(0, 0);

    if(m_graph->isDirected()){
        directionCorrection = 0.7;
    }

    QVector<GraphicNode*> nodesList = dynamic_cast<GraphTable *>(m_GraphTable)->getNodes();

    for(int brojac = 0; brojac < numOfIters; brojac++) {

        for (int i = 0; i < nodesList.size(); i++) {

            QList<Node*> neighourList = nodesList[i]->getNode()->neighbours();

            for(int j = 0; j < nodesList.size(); j++) {

                if(i == j)
                    continue;

                pointsDistance = nodesList[i]->distance(nodesList[j]);
                normalizedVector = nodesList[i]->normalize(nodesList[j]);

                repulsiveForce += (-C*K*K / pointsDistance) * normalizedVector * 0.2 * directionCorrection;

                for(int k = 0; k < neighourList.size(); k++) {

                    if(nodesList[j]->getNode() == neighourList[k]) {
                        attractionForce += pow(pointsDistance, 2) / K  * normalizedVector * 0.001 * directionCorrection;
                        break;
                    }
                }
            }

            moveForce = repulsiveForce + attractionForce;

            double newX = nodesList[i]->CenterPosition().x() + moveForce.x();
            double newY = nodesList[i]->CenterPosition().y() + moveForce.y();

            double x = fmin(dynamic_cast<GraphTable *>(m_GraphTable)->sceneRect().width() - GraphicNode::m_width, newX - nodesList[i]->m_width / 2);
            double y = fmin(dynamic_cast<GraphTable *>(m_GraphTable)->sceneRect().height() - GraphicNode::m_height, newY - nodesList[i]->m_height / 2);
            x = std::fmax(0, x);
            y = std::fmax(0, y);

            nodesList[i]->setPos(x, y);
            moveForce = repulsiveForce = attractionForce = QPointF(0, 0);
        }

        emit NeedRedraw();
        gravityDelay();
    }
}

