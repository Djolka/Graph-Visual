#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbAddNode_clicked();
    void on_pbDeleteAll_clicked();
    void on_lw_currentRowChanged(int currentRow);

private:
    Ui::MainWindow *ui;
    int itemSelected = -1;
};
#endif // MAINWINDOW_H
