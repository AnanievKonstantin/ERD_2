#ifndef DATAMODELGRAPHICSVIEW_H
#define DATAMODELGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMenu>
#include<QContextMenuEvent>
#include <QAction>
#include <QDebug>
#include <EREnums.h>

class DataModelGraphicsView: public QGraphicsView
{
	Q_OBJECT
	public:
		void wheelEvent(QWheelEvent *event);
		DataModelGraphicsView(QGraphicsView * parent = 0);
		void initView();
		QGraphicsScene * getScene() const;
	private:
		QGraphicsScene * scene;
};
#endif // DATAMODELGRAPHICSVIEW_H
