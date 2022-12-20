#include "Headers/graphtable.h"
#include "Headers/graphicnode.h"
#include "Headers/graphicedge.h"

#include "Headers/popup.h"
#include "qapplication.h"
#include "qdatetime.h"
#include <QMessageBox>
#include <iostream>
#include <QTime>

#include<cmath>


GraphTable::GraphTable(bool dir, QObject *parent)
    : QGraphicsScene(parent) {
    m_directed = dir;
}

void GraphTable::AddNewNodeOnTable(GraphicNode *node) {
    m_Nodes.append(node);

    connect(node, &GraphicNode::needRedraw, this, &GraphTable::Redraw);

    PlaceNodeOnTable(node);
}

void GraphTable::AddNewEdgeOnTable(GraphicEdge *edge) {
    m_Edges.append(edge);
    edge->setFlag(QGraphicsItem::ItemIgnoresTransformations, false);
    connect(edge, &GraphicEdge::weightEdited, this, &GraphTable::editWeight);
    connect(edge, &GraphicEdge::needRedraw, this, &GraphTable::Redraw);
    connect(edge, &GraphicEdge::needWarning, this, &GraphTable::Warning);

    addItem(edge);
    addWidget(edge->getLineEdit());
}

void GraphTable::DeleteGraphFromTable() {
    for(auto edge : m_Edges) {
        removeItem(edge);
        delete edge;
    }
    m_Edges.clear();
    for(auto node : m_Nodes) {
        removeItem(node);
        delete node;
    }
    m_Nodes.clear();
    update();
}

void GraphTable::Redraw(){
    this->update();
}

void GraphTable::PlaceNodeOnTable(GraphicNode *node) {
    const int tableWidth = static_cast<int>(width());
    auto newNodeIndex = m_Nodes.size() - 1;

    const auto xPos = (node->m_width * newNodeIndex) % tableWidth;
    const auto yPos = node->m_height * ((node->m_width * newNodeIndex) / tableWidth);
    node->setPos(xPos, yPos);

    node->setFlag(QGraphicsItem::ItemIgnoresTransformations, false);
}


QVector<GraphicNode *> GraphTable::getNodes(){
    return m_Nodes;
}
QVector<GraphicEdge *> GraphTable::getEdges(){
    return m_Edges;
}

void GraphTable::editWeight(GraphicEdge* edge, int w){
    emit edgeWeightChanged(edge->getStart()->getNode(), edge->getEnd()->getNode(), w);
}

void GraphTable::Warning (QString s){
    emit needWarning(s);
}

bool GraphTable::hasGraphicEdge(GraphicNode *u, GraphicNode *v) {
    auto it = m_Edges.begin();
    for(;it != m_Edges.end(); ++it){
        if ((*it)->getStart()->getNode() == u->getNode() && (*it)->getEnd()->getNode() == v->getNode()){
            return true;
        }
    }
    return false;
}

void GraphTable::mousePressEvent ( QGraphicsSceneMouseEvent * event ){

    if(m_drawingMode && itemAt(event->scenePos(), QTransform()) == NULL){
        if(m_hasTmp){
            setHasTmp(false);
        }
        else{ //add new node
            Popup* p = new Popup();

            if(p->exec() == QDialog::Accepted){

                QString nodeName = p->getNodeName();

                bool alreadyExists = false;
                for(GraphicNode* n : m_Nodes){
                    if(n->getNode()->name() == nodeName.toStdString()){
                        alreadyExists = true;
                        emit needWarning("Node with that name already exists");
                        break;
                    }
                }


                if(!alreadyExists && !(nodeName.length()==0)){

                    Node* node = new Node(nodeName.toStdString());
                    GraphicNode* graphicNode = new GraphicNode(node);

                    QPointF point = event->scenePos() - QPointF(graphicNode->m_width / 2, graphicNode->m_height / 2);
                    qreal x = 0, y = 0;
                    x = std::min(sceneRect().width() - GraphicNode::m_width, point.x());
                    y = std::min(sceneRect().height() - GraphicNode::m_height, point.y());
                    x = std::fmax(0, x);
                    y = std::fmax(0, y);

                    AddNewNodeOnTable(graphicNode);
                    graphicNode->setPos(x, y);
                    addItem(graphicNode);
                    emit addedNewNode(node);
                }
            }
        }
    }
    else if(m_drawingMode && (itemAt(event->scenePos(), QTransform())->type() == 1)){ //click on node
        if(!m_hasTmp){
            this->m_tmp = dynamic_cast<GraphicNode*>(itemAt(event->scenePos(), QTransform()));
            setHasTmp(true);
        }
        else{
            GraphicNode* node = dynamic_cast<GraphicNode*>(itemAt(event->scenePos(), QTransform()));

            if(!hasGraphicEdge(m_tmp, node) && m_tmp != node) {
                GraphicEdge* edge = new GraphicEdge(m_tmp, node, 1, m_directed);
                AddNewEdgeOnTable(edge);


                emit addedNewEdge(m_tmp->getNode(), node->getNode(), 1);
            }

            setHasTmp(false);
        }
        this->update();
    }
    else if(m_deleteMode && itemAt(event->scenePos(), QTransform()) == NULL){
        setHasTmp(false);
        QGraphicsScene::mousePressEvent(event);
    }
    else if(m_deleteMode && (itemAt(event->scenePos(), QTransform())->type() == 1)){ //delete node
        const auto graphicNode = dynamic_cast<GraphicNode*>(itemAt(event->scenePos(), QTransform()));
        removeItem(graphicNode);
        m_Nodes.removeOne(graphicNode);

        Node* node = graphicNode->getNode();

        // delete edges around the node
        auto i = m_Edges.begin();
        while (i != m_Edges.end()) {
            if((*i)->getStart()->getNode()==node || (*i)->getEnd()->getNode()==node){
                removeItem(*i);
                removeItem((*i)->getLineEdit()->graphicsProxyWidget());
                emit deletedEdge((*i)->getStart()->getNode(), (*i)->getEnd()->getNode());
                i = m_Edges.erase(i);
                Redraw();
            }
            else
                ++i;
        }

        emit deletedNode(node);
    }
    else if(m_deleteMode && (itemAt(event->scenePos(), QTransform())->type() == 2)){ //delete edge
        const auto graphicEdge = dynamic_cast<GraphicEdge*>(itemAt(event->scenePos(), QTransform()));
        removeItem(graphicEdge);
        removeItem(graphicEdge->getLineEdit()->graphicsProxyWidget());
        m_Edges.removeOne(graphicEdge);

        Redraw();

        emit deletedEdge(graphicEdge->getStart()->getNode(), graphicEdge->getEnd()->getNode());
    }
    else{
        setHasTmp(false);
        QGraphicsScene::mousePressEvent(event);
    }
}

void GraphTable::setDrawingMode(bool x) {
    m_drawingMode = x;
}
void GraphTable::setHasTmp(bool x) {
    m_hasTmp = x;
}
void GraphTable::setDeleteMode(bool x) {
    m_deleteMode = x;
}


void GraphTable::delay() {
    QTime dieTime = QTime::currentTime().addMSecs(5000-m_sliderValue);
    while(QTime::currentTime() < dieTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

GraphicNode* GraphTable::getGraphicNode(Node *node) {
    for(GraphicNode *gn : m_Nodes)
        if(gn->getNode()->name() == node->name())
            return gn;

    return nullptr;
}
GraphicEdge* GraphTable::getGraphicEdge(Edge *edge) {

    for(GraphicEdge *ge : m_Edges){

        if((ge->getStart()->getNode()->name() == edge->first()->name() && ge->getEnd()->getNode()->name() == edge->second()->name())
                ||(ge->getStart()->getNode()->name() == edge->second()->name() && ge->getEnd()->getNode()->name() == edge->first()->name())){
            return ge;
        }
    }
    return nullptr;
}


void GraphTable::colorNodes(QList<Node*> result) {
    reset();
    for(auto n : result){
        GraphicNode* node = getGraphicNode(n);
        node->setBrush(QBrush(Qt::red), true);
        Redraw();
        delay();
    }
}

void GraphTable::colorNodesDijkstra(QList<Node*> path, QList<Node*> visit, QList<Edge*> edges) {
    reset();
    for(auto n : visit){
        GraphicNode* node = getGraphicNode(n);
        node->setBrush(QBrush(Qt::red), true);
        Redraw();

        for(auto e : edges){
            if(e->first()->name()==n->name() || e->second()->name()==n->name()){
                GraphicEdge* edge = getGraphicEdge(e);
                edge->setPen(QPen(Qt::red), true);
                Redraw();
                delay();
                edge->setPen(QPen(GraphicEdge::m_color), false);
                Redraw();
            }
        }

        if(!path.contains(n)){
            delay();
            node->setBrush(QBrush(GraphicNode::m_color), false);
        }
        Redraw();
        delay();
    }
}

void GraphTable::colorEdges(QList<Edge*> result) {
    reset();
    for(auto e : result){
        GraphicEdge* edge = getGraphicEdge(e);

        edge->setPen(QPen(Qt::red), true);
        Redraw();
        delay();
    }
}



void GraphTable::colorNodesSet(QSet<Node *> result) {
    reset();
    for(auto n : result){
        GraphicNode* node = getGraphicNode(n);
        node->setBrush(QBrush(Qt::red), true);
        Redraw();
        delay();
    }

}


 void GraphTable::reset() {
     for(GraphicNode* node : m_Nodes){
         node->setBrush(QBrush(GraphicNode::m_color), false);
     }
     for(GraphicEdge* edge : m_Edges){
         edge->setPen(QPen(GraphicEdge::m_color), false);
     }
     Redraw();
 }

void GraphTable::setToDir() {
    m_directed = true;
}

void GraphTable::setToUndir() {
    m_directed = false;
}

void GraphTable::changeSliderValue(int value) {
    m_sliderValue = value;
}
