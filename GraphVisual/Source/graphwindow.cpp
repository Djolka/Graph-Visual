#include "Headers/graphwindow.h"
#include "Headers/popup.h"
#include "ui_graphwindow.h"

#include "Headers/graphtable.h"
#include "Headers/node.h"
#include "Headers/graphicnode.h"

#include "Headers/edge.h"
#include "Headers/graphicedge.h"
#include "Headers/algorithm.h"
#include "Headers/graph.h"

#include "Headers/algorithm.h"
#include"Headers/popup.h"
#include"ui_popup.h"

#include <QJsonDocument>
#include <future>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <fstream>
#include <string>
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
#include <QIcon>

#include "Headers/algorithm.h"
#include "Headers/popup.h"
#include "ui_popup.h"
#include <unistd.h>

GraphWindow::GraphWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GraphWindow)
    , m_graph(new Graph(false, true))
    , m_GraphTable(new GraphTable(m_graph->isDirected(), this))
{
    ui->setupUi(this);

    ui->horizontalSlider->setRange(1000, 4000);
    ui->horizontalSlider->setValue((ui->horizontalSlider->maximum()+ui->horizontalSlider->minimum())/2);

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
    connect(this, &GraphWindow::colorMST, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::colorEdges);
    connect(this, &GraphWindow::colorDijkstra, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::colorNodesDijkstra);
    connect(this, &GraphWindow::colorArticulation, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::colorNodesSet);
    connect(this, &GraphWindow::colorBridges, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::colorEdges);
    connect(this, &GraphWindow::colorEulerCycle, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::colorEdges);

    connect(ui->pbRESET, &QPushButton::clicked, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::reset);
    connect(this, &GraphWindow::changeToDir, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::setToDir);
    connect(this, &GraphWindow::changeToUndir, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::setToUndir);

    connect(ui->horizontalSlider, &QSlider::valueChanged, dynamic_cast<GraphTable *>(m_GraphTable), &GraphTable::changeSliderValue);


    fillMap();
    QApplication::setWindowIcon(QIcon(":/Resources/logo.ico"));
    indexColors();
}

GraphWindow::~GraphWindow()
{
    delete ui;
    delete m_GraphTable;
    delete m_graph;
}


void GraphWindow::fillMap() {
    m_colors.insert("off white", "#E8E4D6");
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

void GraphWindow::indexColors() {
    m_indices.insert("off white", 7);
    m_indices.insert("white", 1);
    m_indices.insert("black", 8);
    m_indices.insert("navy", 6);
    m_indices.insert("yellow", 5);
    m_indices.insert("green", 4);
    m_indices.insert("purple", 3);
    m_indices.insert("blue", 2);
    m_indices.insert("dark grey", 0);
    m_indices.insert("red", 9);
}



void GraphWindow::SaveAsPic(const QString& m_ext){
    QString dir = QDir::homePath();
    QString name = "Untilted." + m_ext;
    QString fileType = m_ext.toUpper() + "(*." + m_ext.toUpper() + ")";
    QString fileName= QFileDialog::getSaveFileName(this, "Save image", dir + "/" + name, fileType, nullptr, QFileDialog::DontUseNativeDialog);
        if (!fileName.isNull()) {
            QPixmap pixMap = this->ui->graphicsView->grab();
            pixMap.save(fileName);
        }

}

void GraphWindow::AddNewEdge() {

    if(m_graph->nodeSet().size() >= 14){
        warning("You have reached the maximum number of nodes allowed");
        ui->teNode1->clear();
        ui->teNode2->clear();
        ui->teWeight->clear();
        return;
    }

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

bool GraphWindow::nodeExists(std::string name){
    if(!m_graph->hasNode(name))
          return true;
    return false;
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
            emit changeToDir();
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
            emit changeToDir();
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

void GraphWindow::click(){
    this->ui->pbAddNode->animateClick();
    return;
}



void GraphWindow::graphUndirected() {
    if(m_graph->nodeSet().empty()){
            emit changeToUndir();
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
            emit changeToUndir();
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

void GraphWindow::enterValue(std::string key, std::string key2, std::string value){
    this->ui->teNode1->insertPlainText(QString::fromStdString(key));
    this->ui->teNode2->insertPlainText(QString::fromStdString(key2));
    this->ui->teWeight->insertPlainText(QString::fromStdString(value));
}



void GraphWindow::fromVariant(const QVariant &variant)
{
    const auto map = variant.toMap();

    emit this->ui->pbDeleteAll->clicked();


    int background = map.value("background").toInt();
    int nodeColor = map.value("nodeColor").toInt();
    int edgeColor = map.value("edgeColor").toInt();
    QString direction = map.value("direction").toString();

    indexColors();

    QString color=m_indices.key(background);
    this->ui->cbBgcolor->setCurrentIndex(background);

    color=m_indices.key(nodeColor);
    this->ui->cbNodecolor->setCurrentIndex(nodeColor);

    color=m_indices.key(edgeColor);
    this->ui->cbEdgecolor->setCurrentIndex(edgeColor);
    emit this->ui->pbSave->clicked();

    if(direction=="directed"){
        graphDirected();
    }else{
        graphUndirected();
    }

    //OVDE DODAJ KOD ZA INVALIDATE
    QGraphicsView obj=this;
    obj.invalidateScene(this->ui->graphicsView->sceneRect(), QGraphicsScene::SceneLayers());
    QCoreApplication::processEvents();

    bool hasEdges = map.value("hasEdges").toBool();
    QVector<Edge*> edgeSet;

    if (hasEdges) {
        // Ne zaboravimo da se oslobodimo stare memorije!!!
        qDeleteAll(edgeSet);

        const auto edges = map.value("edges").toList();
        for(const auto& edge : edges) {
            const auto map2=edge.toMap();
            QString node1=map2.value("node1").toString();
            QString node2=map2.value("node2").toString();
            QString weight=map2.value("weight").toString();
            enterValue(node1.toStdString(), node2.toStdString(), weight.toStdString());
            obj.invalidateScene(this->ui->graphicsView->sceneRect(), QGraphicsScene::SceneLayers());
            QCoreApplication::processEvents();
            AddNewEdge();
            sleep(1);
           }
       }
}

QVariant GraphWindow::toVariant() const
{
    auto edgeSet=this->m_graph->edgeSet();
    int background=this->ui->cbBgcolor->currentIndex();
    int nodeColor=this->ui->cbNodecolor->currentIndex();
    int edgeColor=this->ui->cbEdgecolor->currentIndex();
    QString direction=this->m_graph->isDirected()? "directed":"undirected";



    QVariantMap map;
        map.insert("background", background);
        map.insert("nodeColor", nodeColor);
        map.insert("edgeColor", edgeColor);
        map.insert("direction", direction);
        map.insert("hasEdges", !edgeSet.empty());

        if (!edgeSet.empty()) {
            QVariantList edges;
            for (const auto & edge : edgeSet) {
                edges.append(edge->toVariant());
            }
            map.insert("edges", edges);
        }

        return map;

}

void GraphWindow::on_actionLoadFromJson_triggered(){
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/", "JSON files (*.json)", nullptr, QFileDialog::DontUseNativeDialog);
    std::string filepath = file.toStdString();

    QFile newFile(QString::fromStdString(filepath));
    if(newFile.open(QFile::ReadOnly)){

    QJsonDocument doc = QJsonDocument::fromJson(newFile.readAll());

    newFile.close();

    GraphWindow::fromVariant(doc.toVariant());}

}

void GraphWindow::on_actionOpen_triggered(){


    QString file = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/", "GRAPH files (*.graph)", nullptr, QFileDialog::DontUseNativeDialog);
    std::string filename = file.toStdString();
    std::ifstream openFile;
    std::string path = filename;
    openFile.open(filename);
    if (!openFile.fail()){

        emit this->ui->pbDeleteAll->clicked();
        int radius;
        openFile>>radius;
        char c;
        openFile.get(c);

        std::map<std::string, int> graphInfo;
        std::string line;
        std::string key, value;
        int colorInfo=3;
        for(int i=0;i<colorInfo;i++){
            std::getline(openFile, line);
            std::istringstream input(line);
            input >> key >> value;
            graphInfo[key] = std::stoi(value);
        }
        indexColors();


        int colorIndex=graphInfo["background:"];
        this->ui->cbBgcolor->setCurrentIndex(colorIndex);

        colorIndex=graphInfo["nodeColor:"];
        this->ui->cbNodecolor->setCurrentIndex(colorIndex);

        colorIndex=graphInfo["edgeColor:"];
        this->ui->cbEdgecolor->setCurrentIndex(colorIndex);

        QGraphicsView obj=this;
        obj.invalidateScene(this->ui->graphicsView->sceneRect(), QGraphicsScene::SceneLayers());
        QCoreApplication::processEvents();

        std::string name;
        std::string skip;

        std::string mode;
        openFile>>mode;

        if(mode=="dir"){
            graphDirected();
        }else{
            graphUndirected();
        }

        std::string  key2;
        getline(openFile, line);
        while (!openFile.eof()){
            getline(openFile, line);
            std::istringstream input(line);
            input >> key >> key2 >>value;
            enterValue(key, key2, value);
            obj.invalidateScene(this->ui->graphicsView->sceneRect(), QGraphicsScene::SceneLayers());
            QCoreApplication::processEvents();
            AddNewEdge();
            sleep(1);

        }
        openFile.close();
        emit this->ui->pbSave->clicked();

    }
}


void GraphWindow::on_actionSaveAsJson_triggered(){
    if (this->m_graph->countNodes()==0){
            QMessageBox::information(this, tr("Error"), "The scene is empty");
    }else{
        QString file = QFileDialog::getSaveFileName(this, tr("Save File"), "/home/", "JSON files (*.json)", nullptr, QFileDialog::DontUseNativeDialog);
        if (!file.isEmpty()){
            std::string filename = file.toStdString();
            if (filename.substr(filename.size()-5).compare(".json")!=0){
                filename+=".json";
            }

            QJsonDocument doc = QJsonDocument::fromVariant(GraphWindow::toVariant());

            QFile file(QString::fromStdString(filename));

            file.open(QFile::WriteOnly);

            file.write(doc.toJson(QJsonDocument::JsonFormat::Indented));

            file.close();

        }
    }
}

void GraphWindow::on_actionSave_triggered(){
    if (this->m_graph->countNodes()==0){
            QMessageBox::information(this, tr("Error"), "The scene is empty");
    }else{
        QString file = QFileDialog::getSaveFileName(this, tr("Save File"), "/home/", "GRAPH files (*.graph)", nullptr, QFileDialog::DontUseNativeDialog);
        if (!file.isEmpty()){
            std::string filename = file.toStdString();
            if (filename.substr(filename.size()-6).compare(".graph")!=0){
                filename+=".graph";
            }
            std::string path = filename;
            std::ofstream saveFile;
            saveFile.open(filename);


            std::map<std::string, int> graphInfo;
            int backgroundColor=this->ui->cbBgcolor->currentIndex();
            int nodeRadius=this->ui->sbRadius->displayIntegerBase();
            int nodeColor=this->ui->cbNodecolor->currentIndex();
            int edgeColor=this->ui->cbEdgecolor->currentIndex();

            graphInfo.insert({"background: ", backgroundColor});
            graphInfo.insert({"nodeColor: ", nodeColor});
            graphInfo.insert({"edgeColor: ", edgeColor});

            auto edges=this->m_graph->edgeSet();
            saveFile<<nodeRadius<<"\n";

            for (auto &pair: graphInfo){
                saveFile<<pair.first<<" "<<pair.second<<"\n";
            }

            if(this->m_graph->isDirected()){
                saveFile<<"dir"<<"\n";
            }else{
                saveFile<<"undir"<<"\n";
            }

            for (auto &edge:edges){
                saveFile << edge->first()->name()<<" "<<edge->second()->name()<<" "<< edge->weight()<<"\n";
            }

            saveFile.close();
        }
    }
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
//void GraphWindow::on_pbUndirected_released(){}
//void GraphWindow::on_pbUndirected_clicked(){}
//void GraphWindow::on_pbAddNode_clicked(){}


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

void GraphWindow::algorithm() {
    if(m_graph->nodeSet().empty()){
        warning("Insert nodes before running algorithm!");
        return;
    }

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
    else if(ui->pbMST->isChecked()){  // works for undirected graph

        QWidget::setEnabled(false);
        std::map<Node*, Node*> parent = a->MST(*m_graph);
        QList<Edge*> result;

        for (std::map<Node*, Node*>::iterator it=parent.begin(); it!=parent.end(); ++it){
            if(it->second != nullptr)
                result.append(m_graph->getEdge(it->second, it->first));

        }

        emit colorMST(result, true);
        QMessageBox::information(this, "Finished", "<FONT COLOR='#FFEFD5'>Algorithm is finished</FONT>");
        QWidget::setEnabled(true);
    }
    else if(ui->pbDjikstra->isChecked()){
        Node* node1;
        Node* node2;

        auto p = new Popup();
        if(p->exec() == QDialog::Accepted){
            QString nodeName = p->getNodeName();
            node1 = m_graph->getNode(nodeName.toStdString());
            if(node1 == nullptr)
                warning("Node with that name does not exist");
        }
        else{
            delete a;
            return;
        }
        if(p->exec() == QDialog::Accepted){
            QString nodeName = p->getNodeName();
            node2 = m_graph->getNode(nodeName.toStdString());
            if(node2 == nullptr)
                warning("Node with that name does not exist");
        }
        else {
            delete a;
            return;
        }

        QWidget::setEnabled(false);
        QList<Node*> path;
        QList<Node*> visit;
        QList<QPair<Node*, Node*>> edges1;
        int result = a->Dijkstra(*m_graph, node1, node2, path, visit, edges1);

        if(result == -1){
            QMessageBox::information(this, "Finished", "<FONT COLOR='#FFEFD5'>There is no path from"+ QString::fromStdString(node1->name())+" to "+ QString::fromStdString(node2->name())+"</FONT>");
        }
        else{
            QList<Edge*> edges2;
            for(auto p : edges1){
                edges2.append(m_graph->getEdge(p.first, p.second));
            }

            emit colorDijkstra(path, visit, edges2, true);
            QMessageBox::information(this, "Finished", "<FONT COLOR='#FFEFD5'>Algorithm is finished. Result: "+QString::fromStdString(std::to_string(result))+"</FONT>");
        }
        QWidget::setEnabled(true);
    }
    else if(ui->pbArticulation->isChecked()){
        QSet<Node*> result;

        QWidget::setEnabled(false);
        result = a->getArticulationNodes(*m_graph);
        emit colorArticulation(result, true);
        QMessageBox::information(this, "Finished", "<FONT COLOR='#FFEFD5'>Algorithm is finished</FONT>");
        QWidget::setEnabled(true);
    }
    else if(ui->pbBridges->isChecked()){
        QList<Edge*> result;

        QWidget::setEnabled(false);
        result = a->getBridges(*m_graph);
        emit colorBridges(result, true);
        QMessageBox::information(this, "Finished", "<FONT COLOR='#FFEFD5'>Algorithm is finished</FONT>");
        QWidget::setEnabled(true);
    }
    else if(ui->pbEulerian->isChecked()) {
        QWidget::setEnabled(false);
        QList<std::string> result = a->getEulerianCircuit(*m_graph);

        if(result.size() == 0) {
            QMessageBox::information(this, "Finished", "<FONT COLOR='#FFEFD5'>There is no Euler cycle in this graph</FONT>");
        }
        else {
            QList<Edge*> coloring;
            auto start = result.begin();
            auto end = result.end() - 1;

            while(start != end) {
                Node* u = m_graph->getNode(*start);
                Node* v = m_graph->getNode((*(start+1)));
                coloring.push_back(m_graph->getEdge(u, v));
                ++start;
            }

            emit colorEulerCycle(coloring, true);
            QMessageBox::information(this, "Finished", "<FONT COLOR='#FFEFD5'>Algorithm is finished</FONT>");
        }

        QWidget::setEnabled(true);
    }
    delete a;
}

void GraphWindow::gravityDelay(){
        QTime dieTime = QTime::currentTime().addMSecs(3);
        while(QTime::currentTime() < dieTime){
            QCoreApplication::processEvents(QEventLoop::AllEvents, 5);
        }
}

void GraphWindow::on_pbBeautify_clicked()
{
    int numOfIters = 500;

    double C = 0.2;
    double K = 50.0; // optimal distance
    double pointsDistance = 0.0;
    double directionCorrection = m_graph->isDirected() ? 0.4 : 1.0;

    QVector<GraphicNode*> nodesList = dynamic_cast<GraphTable *>(m_GraphTable)->getNodes();

    QPointF normalizedVector = QPointF(0, 0);
    QPointF repulsiveForce = QPointF(0, 0);
    QPointF attractionForce = QPointF(0, 0);
    QPointF moveForce = QPointF(0, 0);
    QPointF gravityForce = QPointF(0, 0);
    QPointF centerForce = QPointF(375, 300);

    for(int iter = 0; iter < numOfIters; iter++) {

        for (int i = 0; i < nodesList.size(); i++) {

            gravityForce += nodesList[i]->normalize(centerForce) * 0.1;
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

            moveForce = repulsiveForce + attractionForce + gravityForce;

            double newX = nodesList[i]->CenterPosition().x() + moveForce.x();
            double newY = nodesList[i]->CenterPosition().y() + moveForce.y();

            double x = fmin(dynamic_cast<GraphTable *>(m_GraphTable)->sceneRect().width() - GraphicNode::m_width, newX - nodesList[i]->m_width / 2);
            double y = fmin(dynamic_cast<GraphTable *>(m_GraphTable)->sceneRect().height() - GraphicNode::m_height, newY - nodesList[i]->m_height / 2);
            x = std::fmax(0, x);
            y = std::fmax(0, y);

            nodesList[i]->setPos(x, y);
            gravityForce = moveForce = repulsiveForce = attractionForce = QPointF(0, 0);
        }

        emit NeedRedraw();
        gravityDelay();
    }
}

