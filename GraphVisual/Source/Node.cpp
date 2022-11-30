#include "Headers/node.h"
#include <utility>
#include <QPointF>


Node::Node(){
    this->m_in_deg=0;
    this->m_out_deg=0;
    this->m_deg=0;
}

Node::Node(std::string name){
    this->m_in_deg=0;
    this->m_out_deg=0;
    this->m_deg=0;
    this->m_name=name;
}

Node::Node(std::string name, QPointF position){
    this->m_in_deg=0;
    this->m_out_deg=0;
    this->m_deg=0;
    this->m_name=name;
    this->m_position=position;
}


unsigned Node::in_deg() const{
    return this->m_in_deg;
}

unsigned Node::out_deg() const{
    return this->m_out_deg;
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

void Node::set_position(const QPointF &position){
    this->m_position=position;
}

bool Node::operator==(const Node &second) const{
    return this->m_name==second.m_name;
}

bool Node::operator<(const Node &second) const{
    return this->m_name<second.m_name;
}

QList<Node> Node::neighbours(){
    return m_neighbours;
}


void Node::inc_in_deg(){
    this->m_in_deg++;
}

void Node::inc_out_deg(){
    this->m_out_deg++;
}

void Node::dec_in_deg(){
    if(m_in_deg>0){
        this->m_in_deg--;
    }else{
        std::cerr<<"Ovaj cvor nema ulaznih grana koje se mogu obrisati!!!"<<std::endl;
    }
}

void Node::dec_out_deg(){
    if(m_out_deg>0){
        this->m_out_deg--;
    }else{
        std::cerr<<"Ovaj cvor nema izlaznih grana koje se mogu obrisati!!!"<<std::endl;
    }
}

void Node::inc_deg(){
    this->m_deg++;
}

void Node::dec_deg(){
    if(m_deg>0){
        this->m_deg--;
    }else{
        std::cerr<<"Ovaj cvor nema grana koje se mogu obrisati!!!"<<std::endl;
    }
}

void Node::set_name(const std::string name){
    this->m_name=name;
}
