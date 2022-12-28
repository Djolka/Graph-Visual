#include"Headers/graphicedge.h"
#include<climits>

#include <QPen>
#include <QPainter>
#include <QtMath>
#include <QPainterPath>
#include <math.h>

GraphicEdge::GraphicEdge(GraphicNode* start, GraphicNode* end, int weight, bool dir)
    :QGraphicsLineItem(),
    m_start (start),
    m_end (end),
    m_weight(weight),
    directed(dir){
    m_weightLineEdit = new QLineEdit(QString::fromStdString(std::to_string(weight)));
    connect(m_weightLineEdit, &QLineEdit::editingFinished, this, &GraphicEdge::editWeight);
    setFlags(GraphicsItemFlag::ItemIsSelectable);
    setAcceptHoverEvents(true);
    m_weightLineEdit->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    m_weightLineEdit->setMinimumHeight(20);
    QFont font = m_weightLineEdit->font();
    font.setPointSize(12);
    m_weightLineEdit->setFont(font);
    m_weightLineEdit->setMinimumWidth(15);
    m_weightLineEdit->setStyleSheet("background-color: rgb(228, 232, 214, 0)");
    connect(m_weightLineEdit, &QLineEdit::textEdited, this, &GraphicEdge::editWeight);

    QGraphicsLineItem::setZValue(-10);
}

GraphicEdge::~GraphicEdge(){
    delete m_weightLineEdit;
}

QColor GraphicEdge::m_color = QColor("black");


QRectF GraphicEdge::boundingRect() const {
    QPainterPath ret;
    QPolygonF nPolygon;
    auto line = QLineF(m_start->CenterPosition(), m_end->CenterPosition());
    qreal radAngle = line.angle()* M_PI / 180;
    qreal dx = sin(radAngle);
    qreal dy = cos(radAngle);
    QPointF offset1;
    QPointF offset2;

    if(directed){
        dx *= 40;
        dy *= 40;
        offset1 = QPointF(-dx, -dy);
        offset2 = QPointF(0, 0);
    }
    else {
        dx *= 20;
        dy *= 20;
        offset1 = QPointF(dx, dy);
        offset2 = QPointF(-dx, -dy);
    }
    nPolygon << line.p1() + offset1
             << line.p1() + offset2
             << line.p2() + offset2
             << line.p2() + offset1;
//    ret.addPolygon(nPolygon);
    return nPolygon.boundingRect();
}

QPointF GraphicEdge::getCenter(){
    return QPointF(m_start->CenterPosition().rx() - (m_start->CenterPosition().rx() - m_end->CenterPosition().rx())/2.0,
                   m_start->CenterPosition().ry() - (m_start->CenterPosition().ry() - m_end->CenterPosition().ry())/2.0);
}


QPainterPath GraphicEdge::shape() const{
    QPainterPath ret;
    QPolygonF nPolygon;
    auto line = QLineF(m_start->CenterPosition(), m_end->CenterPosition());
    qreal radAngle = line.angle()* M_PI / 180;
    qreal dx = sin(radAngle);
    qreal dy = cos(radAngle);
    QPointF offset1;
    QPointF offset2;

    if(directed){
        dx *= 40;
        dy *= 40;
        offset1 = QPointF(-dx, -dy);
        offset2 = QPointF(0, 0);
    }
    else {
        dx *= 20;
        dy *= 20;
        offset1 = QPointF(dx, dy);
        offset2 = QPointF(-dx, -dy);
    }
    nPolygon << line.p1() + offset1
             << line.p1() + offset2
             << line.p2() + offset2
             << line.p2() + offset1;
    ret.addPolygon(nPolygon);
    return ret;
}


void GraphicEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(m_pen != QPen(Qt::green) && m_pen != QPen(Qt::red)) {
        m_pen = QPen(GraphicEdge::m_color);
    }
    m_pen.setWidth(2);
    painter->setPen(QPen(m_pen));

    // painter->drawLine(m_start->CenterPosition(), m_end->CenterPosition());

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

        //limit edge to scene


        QPainterPath myPath;
        myPath.moveTo(m_start->x()+25,m_start->y()+25);
        myPath.cubicTo(m_start->x()+25, m_start->y()+25, targetNode->x(), targetNode->y(), m_end->x()+25, m_end->y()+25);


        painter->drawPath(myPath);
        m_weightLineEdit->move((targetNode->x()+edgeCenter->x())/2, (targetNode->y()+edgeCenter->y())/2);
        m_weightLineEdit->setStyleSheet("background: transparent;  border: 0px ;");
        auto text = m_weightLineEdit->text();
        auto width = text.length();

        m_weightLineEdit->resize(std::fmax(10*width, 20), 20);


//        arrow
//        QRectF rect = QRectF(0, 0, 20, 20);
//        QRectF rect = QRectF(m_end->x(), m_end->y(), 15, 15);

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
        m_weightLineEdit->setStyleSheet("background: transparent;  border: 0px ;");


        auto text = m_weightLineEdit->text();
        auto width = text.length();

        m_weightLineEdit->resize(std::fmax(10*width, 20), 20);
    }


}


void GraphicEdge::editWeight(){
    auto text = m_weightLineEdit->text();

    if(text.toStdString().empty()){
        m_weightLineEdit->setText(QString("1"));

        emit weightEdited(this, 1);
        emit needRedraw();
    }
    else if(text.toInt() == 0){
        m_weightLineEdit->setText(QString("1"));

        emit weightEdited(this, 1);
        emit needRedraw();
        emit needWarning(QString("Edge weight must be a number"));

    }
    else if(text.length() < 6){
        int weight = text.toInt();

        emit weightEdited(this, weight);
        emit needRedraw();
    }
    else{
        m_weightLineEdit->setText(QString("1"));

        emit weightEdited(this, 1);
        emit needRedraw();
        emit needWarning(QString("Edge weight too big"));
    }
}

void GraphicEdge::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {

    m_pen = QPen(Qt::green);
    emit needRedraw();
    QGraphicsLineItem::hoverEnterEvent(event);
}
void GraphicEdge::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    if(!m_algorithm) {
        m_pen = QPen(GraphicNode::m_color);
    }
    else {
        m_pen = QPen(Qt::red);
    }

    emit needRedraw();
    QGraphicsLineItem::hoverLeaveEvent(event);
}


int GraphicEdge::type() const {
    return 2;
}

