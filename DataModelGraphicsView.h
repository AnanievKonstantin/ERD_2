#ifndef DATAMODELGRAPHICSVIEW_H
#define DATAMODELGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMenu>
#include<QContextMenuEvent>
#include <QAction>
#include <QDebug>
#include <EREnums.h>

/**
 * @brief The DataModelGraphicsView class
 *	описывает холст для Data модели
 */
class DataModelGraphicsView: public QGraphicsView
{
	Q_OBJECT
	public:
		/**
		 * @brief wheelEvent
		 *	масштабирует диаграмму
		 */
		void wheelEvent(QWheelEvent *event);

		DataModelGraphicsView(QGraphicsView * parent = 0);

		/**
		 * @brief initView
		 *	устанавливает параметры сцены
		 */
		void initView();
		QGraphicsScene * getScene() const;
	private:
		QGraphicsScene * scene;
};
#endif // DATAMODELGRAPHICSVIEW_H
