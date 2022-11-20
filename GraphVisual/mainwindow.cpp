#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pbAddNode_clicked()
{
    QString node1 = ui->teNode1->toPlainText();
    QString node2 = ui->teNode2->toPlainText();
    QString weight = ui->teWeight->toPlainText();

    if (node1 == "" || node2 == "" || weight == ""){
        return;
    }
    ui->lw->addItem(node1 + " -> " + node2 + " : " + weight);

    ui->teNode1->clear();
    ui->teNode2->clear();
    ui->teWeight->clear();
}


void MainWindow::on_pbDeleteAll_clicked()
{
    if(itemSelected != -1){
        QListWidgetItem *item = ui->lw->takeItem(itemSelected);
        delete item;

        ui->lw->setCurrentRow(-1);
    }

}


void MainWindow::on_lw_currentRowChanged(int currentRow)
{
    itemSelected = currentRow;
}

