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
    connect(m_weightLineEdit, &QLineEdit::editingFinished, this, &GraphicEdge::editWeight);
    setFlags(GraphicsItemFlag::ItemIsSelectable);
    setAcceptHoverEvents(true);
    m_weightLineEdit->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    m_weightLineEdit->setMinimumWidth(15);
    connect(m_weightLineEdit, &QLineEdit::textEdited, this, &GraphicEdge::editWeight);

    QGraphicsLineItem::setZValue(-10);
}
GraphicEdge::~GraphicEdge(){
    delete m_weightLineEdit;
}

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

    painter->setPen(m_pen);

    painter->drawLine(m_start->CenterPosition(), m_end->CenterPosition());

    m_weightLineEdit->move(getCenter().x(), getCenter().y());

    auto text = m_weightLineEdit->text();
    auto width = text.length();

    m_weightLineEdit->resize(std::fmax(10*width, 20), 20);
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
    m_pen = QPen(Qt::black);
    emit needRedraw();
    QGraphicsLineItem::hoverLeaveEvent(event);
}


int GraphicEdge::type() const {
    return 2;
}
