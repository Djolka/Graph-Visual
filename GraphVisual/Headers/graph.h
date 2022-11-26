#ifndef GRAPH_H
#define GRAPH_H

#include <QMainWindow>
#include<QPointF>

QT_BEGIN_NAMESPACE
namespace Ui { class Graph; }
QT_END_NAMESPACE

class Graph : public QMainWindow
{
    Q_OBJECT

public:
    Graph(QWidget *parent = nullptr);
    ~Graph();

private slots:
    void on_pbAddNode_clicked();
    void on_pbDeleteAll_clicked();
    void on_lw_currentRowChanged(int currentRow);

private:
    Ui::Graph *ui;
    int itemSelected = -1;
};
#endif // GRAPH_H
