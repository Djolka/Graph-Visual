#include "popup.h"
#include "ui_popup.h"

Popup::Popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Popup)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();
}

Popup::~Popup()
{
    delete ui;
}

QString Popup::getNodeName(){
    return ui->lineEdit->text().trimmed();
}
