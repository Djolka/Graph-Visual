#include "Headers/graphtable.h"
#include "Headers/graphicnode.h"
#include "Headers/graphicedge.h"

GraphTable::GraphTable(QObject *parent)
    : QGraphicsScene(parent) {

}

void GraphTable::AddNewNodeOnTable(GraphicNode *node) {
    m_Nodes.append(node);

    connect(node, &GraphicNode::needRedraw, this, &GraphTable::Redraw);

    PlaceNodeOnTable(node);
}

void GraphTable::AddNewEdgeOnTable(GraphicEdge *edge) {
    m_Edges.append(edge);
    edge->setFlag(QGraphicsItem::ItemIgnoresTransformations, false);
    addItem(edge);
}

void GraphTable::DeleteAllNodesFromTable() {
    for(auto node : m_Nodes) {
        removeItem(node);
        delete node;
    }
    m_Nodes.clear();
}

void GraphTable::Redraw(){
    this->update();
}

void GraphTable::PlaceNodeOnTable(GraphicNode *node) {
    const int tableWidth = static_cast<int>(width());
    auto newNodeIndex = m_Nodes.size() - 1;

    const auto xPos = (node->Width() * newNodeIndex) % tableWidth;
    const auto yPos = node->Height() * ((node->Width() * newNodeIndex) / tableWidth);
    node->setPos(xPos, yPos);

    node->setFlag(QGraphicsItem::ItemIgnoresTransformations, false);
}


QVector<GraphicNode *> GraphTable::getNodes(){
    return m_Nodes;
}
QVector<GraphicEdge *> GraphTable::getEdges(){
    return m_Edges;
}


//TODO: add nodes and edges to graph
void GraphTable::mousePressEvent ( QGraphicsSceneMouseEvent * event ){

    if(m_drawingMode && itemAt(event->scenePos(), QTransform()) == NULL){
        deleteTmp();

        Node* node = new Node();
        GraphicNode* graphicNode = new GraphicNode(node);

        AddNewNodeOnTable(graphicNode);
        graphicNode->setPos(event->scenePos());
        addItem(graphicNode);

//        emit addedNewNode(node);
    }
    else if(m_drawingMode && (itemAt(event->scenePos(), QTransform())->type() == 1)){
        if(this->tmp == nullptr){
            this->tmp = dynamic_cast<GraphicNode*>(itemAt(event->scenePos(), QTransform()));
        }
        else{
            GraphicNode* node = dynamic_cast<GraphicNode*>(itemAt(event->scenePos(), QTransform()));
            GraphicEdge* edge = new GraphicEdge(tmp, node, 1);
            AddNewEdgeOnTable(edge);
            deleteTmp();
        }
        this->update();
    }
    else{
        deleteTmp();
        QGraphicsScene::mousePressEvent(event);
    }
}


//TODO: drawing a line when clicked on a node

//void GraphTable::mouseMoveEvent (QGraphicsSceneMouseEvent * event ){
//    if(m_drawingMode && tmp != nullptr){
//        this->removeItem(lineToDraw);

//        QLineF line(event->scenePos().x(), event->scenePos().y(), tmp->x(), tmp->y());
//        lineToDraw = new QGraphicsLineItem(line);
//        this->addItem(lineToDraw);
//        this->update();
//    }
//    else
//        QGraphicsScene::mouseMoveEvent(event);

//}

void GraphTable::setDrawingMode(bool x) {
    m_drawingMode = x;
}






