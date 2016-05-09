#ifndef ERGRAPHICSVIEW_H
#define ERGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMenu>
#include<QContextMenuEvent>
#include <QAction>
#include <QDebug>
#include <EREnums.h>

class ERGraphicsView: public QGraphicsView
{
	Q_OBJECT
	public:
		ERGraphicsView(QGraphicsView * parent = 0);
		void initView();
		void initMenu();
		void contextMenuEvent(QContextMenuEvent *event);
		QGraphicsScene * getScene() const;
	private:
		QGraphicsScene * scene;
		QMenu * topMenu;
		QMenu * createSubMenu;
	signals:
		void doCreation(int type);
	public slots:
		void whatCreate(QAction* action);
};

#endif // ERGRAPHICSVIEW_H
