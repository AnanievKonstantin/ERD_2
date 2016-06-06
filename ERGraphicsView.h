#ifndef ERGRAPHICSVIEW_H
#define ERGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMenu>
#include<QContextMenuEvent>
#include <QAction>
#include <QDebug>
#include <EREnums.h>

/**
 * @brief The ERGraphicsView class
 *	описывает холст для ER модели
 */
class ERGraphicsView: public QGraphicsView
{
	Q_OBJECT
	public:
		ERGraphicsView(QGraphicsView * parent = 0);

		/**
		 * @brief initView
		 *	устанавливает параметры холста
		 */
		void initView();

		/**
		 * @brief initMenu
		 *	устанавливает меню на холст
		 */
		void initMenu();

		/**
		 * @brief contextMenuEvent
		 *	активирует контекстное меню
		 */
		void contextMenuEvent(QContextMenuEvent *event);
		QGraphicsScene * getScene() const;

		/**
		 * @brief wheelEvent
		 *	масштабирует сцену
		 */
		void wheelEvent(QWheelEvent *event);
	private:
		QGraphicsScene * scene;
		QMenu * topMenu;
		QMenu * createSubMenu;
	signals:
		void doCreation(int type);
		void doRelationOperation(int type);
	public slots:
		void whatCreate(QAction* action);
};

#endif // ERGRAPHICSVIEW_H
