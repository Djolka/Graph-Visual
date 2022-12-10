#include"Headers/graphicedge.h"
#include<climits>

#include <QPen>
#include <QPainter>

GraphicEdge::GraphicEdge(GraphicNode* start, GraphicNode* end, int weight)
    :QGraphicsLineItem(),
    m_start (start),
    m_end (end),
    m_weight(weight){

    m_weightLineEdit = new QLineEdit(QString::fromStdString(std::to_string(weight)));
    connect(m_weightLineEdit, &QLineEdit::textEdited, this, &GraphicEdge::editWeight);

    setFlags(GraphicsItemFlag::ItemIsSelectable | GraphicsItemFlag::ItemIsMovable);
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

    QPen pen;

    if(collidesWithItem(m_start) or collidesWithItem(m_end)) {
        pen.setColor(Qt::white);
    } else {
        pen.setColor(Qt::black);
    }

    painter->setPen(pen);

    painter->drawLine(m_start->CenterPosition(), m_end->CenterPosition());

    m_weightLineEdit->move(getCenter().x(), getCenter().y());

    auto text = m_weightLineEdit->text();
    auto width = text.length();

    m_weightLineEdit->resize(std::max(10*width, 20), 20);
}


void GraphicEdge::editWeight(const QString &text){
    if(text.toStdString().empty()){
        m_weightLineEdit->setText(QString("1"));
        emit weightEdited(this, 1);
        emit needRedraw();
    }
    else{ // TODO: postavljena max duzina grane na 100000, da li zelimo nesto drugo?
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

int GraphicEdge::type() const {
    return 2;
}
