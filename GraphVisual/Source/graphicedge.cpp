#include"Headers/graphicedge.h"
#include<climits>

#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <math.h>

GraphicEdge::GraphicEdge(GraphicNode* start, GraphicNode* end, int weight, bool dir)
    :QGraphicsLineItem(),
    m_start (start),
    m_end (end),
    m_weight(weight),
    directed(dir){
    m_weightLineEdit = new QLineEdit(QString::fromStdString(std::to_string(weight)));
    connect(m_weightLineEdit, &QLineEdit::textEdited, this, &GraphicEdge::editWeight);
    setFlags(GraphicsItemFlag::ItemIsSelectable | GraphicsItemFlag::ItemIsMovable);
    QGraphicsLineItem::setZValue(-10);
}

GraphicEdge::~GraphicEdge(){
    delete m_weightLineEdit;
}

QRectF GraphicEdge::boundingRect() const {
    return QRectF();
}

QPointF GraphicEdge::getCenter(){
    return QPointF(m_start->CenterPosition().rx() - (m_start->CenterPosition().rx() - m_end->CenterPosition().rx())/2.0,
                   m_start->CenterPosition().ry() - (m_start->CenterPosition().ry() - m_end->CenterPosition().ry())/2.0);
}

void GraphicEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    //draw arc
    if(directed){
        double angleRad= 90 * (M_PI/ 180);
        double cosTheta = cos(-angleRad);
        double sinTheta = sin(-angleRad);

        //center of start and end edge
        QPointF *edgeCenter = new QPointF((m_start->x()+m_end->x())/2, (m_start->y()+m_end->y())/2);
        //control point for bezier curve
        QPointF *targetNode = new QPointF(m_end->x(), m_end->y());


        //translating edgeCenter to (0,0) and targetNode with it
        targetNode->setX(targetNode->x()-(m_start->x()+m_end->x())/2);
        targetNode->setY(targetNode->y()-(m_start->y()+m_end->y())/2);
        edgeCenter->setX(edgeCenter->x()-(m_start->x()+m_end->x())/2);
        edgeCenter->setY(edgeCenter->y()-(m_start->y()+m_end->y())/2);



        //rotating aroung edgeCenter targetNode
        double x = targetNode->x();
        targetNode->setX(targetNode->x()*cosTheta - targetNode->y()*sinTheta);
        targetNode->setY(x*sinTheta + targetNode->y()*cosTheta);


        //translating back
        targetNode->setX(targetNode->x()+(m_start->x()+m_end->x())/2);
        targetNode->setY(targetNode->y()+(m_start->y()+m_end->y())/2);
        edgeCenter->setX(edgeCenter->x()+(m_start->x()+m_end->x())/2);
        edgeCenter->setY(edgeCenter->y()+(m_start->y()+m_end->y())/2);





        targetNode->setX((targetNode->x()+edgeCenter->x())/2);
        targetNode->setY((targetNode->y()+edgeCenter->y())/2);


        QPainterPath myPath;
        myPath.moveTo(m_start->x()+25,m_start->y()+25);
        myPath.cubicTo(m_start->x()+25, m_start->y()+25, targetNode->x(), targetNode->y(), m_end->x()+25, m_end->y()+25);


        painter->drawPath(myPath);
        m_weightLineEdit->move((targetNode->x()+edgeCenter->x())/2, (targetNode->y()+edgeCenter->y())/2);

        auto text = m_weightLineEdit->text();
        auto width = text.length();

        m_weightLineEdit->resize(std::fmax(10*width, 20), 20);


//        arrow
//        QRectF rect = QRectF(0, 0, 20, 20);
//        QRectF rect = QRectF(m_end->x()+15, m_end->y()-15, 15, 15);

//        QPainterPath path;
//        path.moveTo(rect.left() + (rect.width() / 2), rect.bottom());
//        path.lineTo(rect.topLeft());
//        path.lineTo(rect.topRight());
//        path.lineTo(rect.left() + (rect.width() / 2), rect.bottom());

//        painter->fillPath(path, QBrush(QColor ("blue")));

        delete edgeCenter;
        delete targetNode;
    }else{
        painter->drawLine(m_start->CenterPosition(), m_end->CenterPosition());

        m_weightLineEdit->move(getCenter().x(), getCenter().y());

        auto text = m_weightLineEdit->text();
        auto width = text.length();

        m_weightLineEdit->resize(std::fmax(10*width, 20), 20);
    }


}

void GraphicEdge::editWeight(const QString &text){
    if(text.toStdString().empty()){
        m_weightLineEdit->setText(QString("1"));
        emit weightEdited(this, 1);
        emit needRedraw();
    }
    else{ // TODO: postavljena max duzina grane na 100000, da li zelimo nesto drugo? Ne, dobro je
        int weight = std::stoi(text.toStdString());
        if(weight < 100000){
            emit weightEdited(this, weight);
            emit needRedraw();
        }
        else{
            m_weightLineEdit->setText(QString("1"));
            emit weightEdited(this, 1);
            emit needRedraw();
        }
    }
}
