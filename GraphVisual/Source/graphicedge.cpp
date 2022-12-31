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
    m_weightLineEdit->setStyleSheet("background: transparent");
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
        dx *= 50;
        dy *= 50;
        offset1 = QPointF(dx, dy);
        offset2 = QPointF(20, 20);
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
        dx *= 50;
        dy *= 50;
        offset1 = QPointF(dx, dy);
        offset2 = QPointF(20, 20);
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
    painter->setPen(QPen(m_pen));

    //draw arc
    if(directed){
        QPointF *edgeCenter = new QPointF((m_start->x()+m_end->x())/2, (m_start->y()+m_end->y())/2);


        qreal dX = m_end->CenterPosition().x() - m_start->CenterPosition().x();
        qreal dY = m_end->CenterPosition().y() - m_start->CenterPosition().y();
        qreal distance = sqrt(pow(dX, 2) + pow(dY, 2));


        QLineF *newLine =  new QLineF(m_start->CenterPosition(), m_end->CenterPosition());
        newLine->setLength(newLine->length() - GraphicNode::m_width/2);

        qreal mX = (m_start->CenterPosition().x() + newLine->p2().x()) / 2;
        qreal mY = (m_start->CenterPosition().y() + newLine->p2().y()) / 2;

        qreal cX = 90 * (-1 * (dY / distance)) + mX;
        qreal cY = 90 * (dX / distance) + mY;
        QPointF *controlPoint = new QPointF(cX, cY);

        QLineF *ghostLine = new QLineF(*controlPoint, m_end->CenterPosition());
        ghostLine->setLength(ghostLine->length() - GraphicNode::m_width/2);

        double angle = ::acos(ghostLine->dx() / ghostLine->length());
        if (ghostLine->dy() >= 0) {
            angle = (M_PI * 2) - angle;
        }

        setLine(*newLine);
        prepareGeometryChange();

        QPainterPath myPath;

        myPath.moveTo(m_start->CenterPosition());
        myPath.quadTo(*controlPoint, ghostLine->p2());
        painter->drawPath(myPath);

        m_weightLineEdit->move((controlPoint->x()+edgeCenter->x())/2, (controlPoint->y()+edgeCenter->y())/2);
        m_weightLineEdit->setStyleSheet("background: transparent;  border: 0px ;");

        auto text = m_weightLineEdit->text();
        auto width = text.length();
        m_weightLineEdit->resize(std::fmax(10*width, 20), 20);


//        arrow
        QPointF arrowP1 = ghostLine->p2() - QPointF(sin(angle + M_PI/3) * m_arrowSize,
                                            cos(angle + M_PI/3) * m_arrowSize);
        QPointF arrowP2 = ghostLine->p2() - QPointF(sin(angle + M_PI - M_PI/4) * m_arrowSize,
                                            cos(angle + M_PI - M_PI/4) * m_arrowSize);

        QPolygonF arrowHead;
        arrowHead.clear();
        arrowHead << ghostLine->p2() << arrowP1 << arrowP2;
        m_brush.setStyle(Qt::SolidPattern);
        painter->setBrush(m_brush);

        painter->drawPolygon(arrowHead);


        delete edgeCenter;
        delete controlPoint;
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

