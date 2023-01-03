#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include <QPointF>
#include <QVariant>

#include "graph.h"
#include "graphicedge.h"

class Node;
class GraphicNode;
class QGraphicsScene;

QT_BEGIN_NAMESPACE
namespace Ui {
    class GraphWindow;
}
QT_END_NAMESPACE

class GraphWindow : public QMainWindow {
	Q_OBJECT

public:
	GraphWindow(QWidget *parent = nullptr);
	~GraphWindow();
	QMap<QString, QString> m_colors;
	QMap<QString, int> m_indices;
	void fillMap();
	void indexColors();
	void SaveAsPic(const QString &m_ext);
	void gravityDelay();
	bool nodeExists(std::string name);
	void enterValue(std::string key, std::string key2, std::string value);
	void fromVariant(const QVariant &variant);
	QVariant toVariant() const;
	void setDirection(QString direction);
	void invalidateRegion();
	std::map<std::string, int> fillGraphInfo(int *colorInfo, std::ifstream *openFile);
	void readFromFile(std::ifstream *openFile);
	void saveInfoIntoFile(std::ofstream *saveFile);

signals:
	void AddedNewNode(GraphicNode *);
	void AddedNewEdge(GraphicEdge *);
	void DeletedGraph();
	void NeedRedraw();
	void colorDFS(QList<Node *>, bool x);
	void colorBFS(QList<Node *> result, bool x);
	void colorArticulation(QSet<Node *> result, bool x);
	void colorBridge(QList<Edge *> result, bool x);
	void changeToDir();
	void changeToUndir();
	void colorMST(QList<Edge *>, bool x);
	void colorBridges(QList<Edge *>, bool x);
	void colorDijkstra(QList<Node *>, QList<Node *>, QList<Edge *>, bool x);
	void colorEulerCycle(QList<Edge *>, bool x);

private slots:
	void AddNewEdge();
	void DeleteGraphFromTable();
	void ChangeMode(int index);
	void AddNode(Node *node);
	void AddEdge(Node *n1, Node *n2, int weight);
	void changeWeight(Node *n1, Node *n2, int weight);
	void deleteNode(Node *node);
	void deleteEdge(Node *node1, Node *node2);
	void warning(QString s);
	void nodeNameLength();
	void algorithm();

	void graphDirected();
	void graphUndirected();

	void onActionSaveAsPngTriggered();
	void onActionSaveAsJpgTriggered();
	void onActionSaveAsJsonTriggered();
	void onActionLoadFromJsonTriggered();

	void onPbUndirectedPressed();
	void onPbDirectedPressed();
	void onActionCloseTriggered();
	void onActionSaveTriggered();
	void onActionOpenTriggered();
	void onPbSaveClicked();
	void onPbBeautifyClicked();

private:
	Ui::GraphWindow *ui;
	Graph *m_graph;
	QGraphicsScene *m_GraphTable;
	bool shouldPopUpUndir = true;
	bool shouldPopUpDir = true;
	std::string m_path = "";
};
#endif // GRAPHWINDOW_H
