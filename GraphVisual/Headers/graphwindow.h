#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include<QPointF>

QT_BEGIN_NAMESPACE
namespace Ui { class GraphWindow; }
QT_END_NAMESPACE

class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    GraphWindow(QWidget *parent = nullptr);
    ~GraphWindow();

private slots:
    void on_pbAddNode_clicked();
    void on_pbDeleteAll_clicked();
    void on_lw_currentRowChanged(int currentRow);

private:
    Ui::GraphWindow *ui;
    int itemSelected = -1;
};
#endif // GRAPHWINDOW_H
