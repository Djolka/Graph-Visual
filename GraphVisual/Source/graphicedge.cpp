#include"Headers/graphicedge.h"
#include<climits>

#include <QPen>
#include <QPainter>
#include <QtMath>

GraphicEdge::GraphicEdge(GraphicNode* start, GraphicNode* end, int weight)
    :QGraphicsLineItem(),
    m_start (start),
    m_end (end),
    m_weight(weight){
    m_weightLineEdit = new QLineEdit(QString::fromStdString(std::to_string(weight)));
    connect(m_weightLineEdit, &QLineEdit::returnPressed, this, &GraphicEdge::editWeight);
    setFlags(GraphicsItemFlag::ItemIsSelectable);
    setAcceptHoverEvents(true);
    QGraphicsLineItem::setZValue(-10);
}

QColor GraphicEdge::m_color = QColor("black");

QRectF GraphicEdge::boundingRect() const {
    QPolygonF nPolygon;
    auto line = QLineF(m_start->CenterPosition(), m_end->CenterPosition());
    qreal radAngle = line.angle()* M_PI / 180;
    qreal dx = 20 * sin(radAngle);
    qreal dy = 20 * cos(radAngle);
    QPointF offset1 = QPointF(dx, dy);
    QPointF offset2 = QPointF(-dx, -dy);
    nPolygon << line.p1() + offset1
             << line.p1() + offset2
             << line.p2() + offset2
             << line.p2() + offset1;
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
    qreal dx = 20 * sin(radAngle);
    qreal dy = 20 * cos(radAngle);
    QPointF offset1 = QPointF(dx, dy);
    QPointF offset2 = QPointF(-dx, -dy);
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

    if(m_pen != QPen(Qt::green)) {
        m_pen = QPen(GraphicEdge::m_color);
    }
    painter->setPen(m_pen);

    painter->drawLine(m_start->CenterPosition(), m_end->CenterPosition());

    m_weightLineEdit->move(getCenter().x(), getCenter().y());

    auto text = m_weightLineEdit->text();
    auto width = text.length();

    m_weightLineEdit->resize(std::fmax(10*width, 20), 20);
}


void GraphicEdge::editWeight(){
    if(m_weightLineEdit->text().toStdString().empty()){
        m_weightLineEdit->setText(QString("1"));
        emit weightEdited(this, 1);
        emit needRedraw();
    }
    else{
        if(m_weightLineEdit->text().length() < 6){
            int weight = std::stoi(m_weightLineEdit->text().toStdString());

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

void GraphicEdge::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {

    m_pen = QPen(Qt::green);
    emit needRedraw();
    QGraphicsLineItem::hoverEnterEvent(event);
}
void GraphicEdge::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {

    m_pen = QPen(GraphicEdge::m_color);
    emit needRedraw();
    QGraphicsLineItem::hoverLeaveEvent(event);
}


int GraphicEdge::type() const {
    return 2;
}

