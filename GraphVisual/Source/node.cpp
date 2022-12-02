#include "Headers/node.h"
#include<utility>
#include<QPointF>
#include<QList>

Node::Node(){
    this->m_inDeg=0;
    this->m_outDeg=0;
    this->m_deg=0;
}


Node::Node(std::string name){
    this->m_inDeg=0;
    this->m_outDeg=0;
    this->m_deg=0;
    this->m_name=name;
}

Node::Node(std::string name, QPointF position){
    this->m_inDeg=0;
    this->m_outDeg=0;
    this->m_deg=0;
    this->m_name=name;
    this->m_position=position;
}

unsigned Node::inDeg() const{
    return this->m_inDeg;
}

unsigned Node::outDeg() const{
    return this->m_outDeg;
}

unsigned Node::deg() const{
    return this->m_deg;
}

QPointF Node::position() const{
    return this->m_position;
}

std::string Node::name() const{
    return m_name;
}

void Node::setPosition(const QPointF &position){
    this->m_position=position;
}

bool Node::operator==(const Node &second) const{
    return this->m_name==second.m_name;
}

bool Node::operator<(const Node &second) const{
    return this->m_name<second.m_name;
}

QList<Node*> Node::neighbors(){
    return m_neighbors;
}

void Node::addNeighbour(Node* n){
    m_neighbors.append(n);
}

void Node::incInDeg(){
    this->m_inDeg++;
}

void Node::incOutDeg(){
    this->m_outDeg++;
}

void Node::decInDeg(){
    if(m_inDeg>0){
        this->m_inDeg--;
    }else{
        std::cerr<<"Ovaj cvor nema ulaznih grana koje se mogu obrisati!!!"<<std::endl;
    }
}

void Node::decOutDeg(){
    if(m_outDeg>0){
        this->m_outDeg--;
    }else{
        std::cerr<<"Ovaj cvor nema izlaznih grana koje se mogu obrisati!!!"<<std::endl;
    }
}

void Node::incDeg(){
    this->m_deg++;
}

void Node::decDeg(){
    if(m_deg>0){
        this->m_deg--;
    }else{
        std::cerr<<"Ovaj cvor nema grana koje se mogu obrisati!!!"<<std::endl;
    }
}

void Node::setName(const std::string name){
    this->m_name=name;
}



std::ostream &operator<< (std::ostream &os, const Node &n){
    os<<n.name()<<" "<< n.inDeg()<<" "<< n.outDeg()<<" "<<n.deg()<<std::endl;
    return os;
}
