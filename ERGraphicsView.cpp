#include "ERGraphicsView.h"

ERGraphicsView::ERGraphicsView(QGraphicsView * parent):QGraphicsView(parent)
{
	this->scene = new QGraphicsScene();
	this->setScene(scene);

	this->topMenu = new QMenu(this);
	this->createSubMenu = new QMenu(topMenu);
	initView();
	initMenu();

	this->show();
}

void ERGraphicsView::initView()
{
	setRenderHint(QPainter::Antialiasing);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	setBackgroundBrush(QColor(253, 250, 195));
	setDragMode(QGraphicsView::RubberBandDrag);
	setAcceptDrops(true);
}

void ERGraphicsView::initMenu()
{
//	QVariant * v = new QVariant(int(0));
	QAction * a0 = new QAction(*(new QString("Создать стержневую")), 0);
	a0->setData(0);
	topMenu->addAction(a0);

	QAction * a1 = new QAction(*(new QString("Создать обозначение")), 0);
	a1->setData(1);
	topMenu->addAction(a1);

	QAction * a2 = new QAction(*(new QString("Создать характеристику")), 0);
	a2->setData(2);
	topMenu->addAction(a2);

	QAction * a3 = new QAction(*(new QString("Связать")), 0);
	a3->setData(3);
	topMenu->addAction(a3);

	QAction * a4 = new QAction(*(new QString("Включить в ассоциацию")), 0);
	a4->setData(4);
	topMenu->addAction(a4);

	QAction * a5 = new QAction(*(new QString("Удалить связь между...")), 0);
	a5->setData(5);
	topMenu->addAction(a5);

	QAction * a6 = new QAction(*(new QString("Изменить кардинальность")), 0);
	a6->setData(6);
	topMenu->addAction(a6);

//	createSubMenu->setTitle("Создать сущность");
//	topMenu->addMenu(createSubMenu);

	connect(topMenu, SIGNAL(triggered(QAction*)), this, SLOT(whatCreate(QAction*)));
}

void ERGraphicsView::contextMenuEvent(QContextMenuEvent * event)
{
	topMenu->exec(event->globalPos());
}

QGraphicsScene *ERGraphicsView::getScene() const
{
	return scene;
}

void ERGraphicsView::wheelEvent(QWheelEvent *event)
{
	// Scale the view / do the zoom
	const double scaleFactor = 1.15;
	if(event->delta() > 0)
	{
		// Zoom in
		scale(scaleFactor, scaleFactor);
	}
	else
	{
		// Zooming out
		scale(1.0 / scaleFactor, 1.0 / scaleFactor);
	}

}


void ERGraphicsView::whatCreate(QAction * action)
{
//	qDebug() << "Val: " <<action->data().toInt()<< "\n";

	switch (action->data().toInt()) {
		case 0:
			emit doCreation(essence_type::Base);
			//qDebug("Создаю: стержневую сущность");
			break;
		case 1:
			emit doCreation(essence_type::Designation);
//			qDebug("Создаю: обозначение");
			break;
		case 2:
			emit doCreation(essence_type::Characteristic);
//			qDebug("Создаю: характеристику");
			break;
		case 3:
			emit doRelationOperation(3);
//			qDebug("Создаю: связь");
			break;
		case 4:
			emit doRelationOperation(4);
//			qDebug("Включаю в ассоциацию");
			break;
		case 5:
			emit doRelationOperation(5);
//			qDebug("Удаляю связь");
			break;
		case 6:
			emit doRelationOperation(6);
//			qDebug("изменяю кардинальность");
			break;
		default:
//			qDebug("Ошибка в void ERGraphicsView::whatCreate(QAction * action), неверный тип сущности");
			break;
	}
}
