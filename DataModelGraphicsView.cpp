#include "DataModelGraphicsView.h"

DataModelGraphicsView::DataModelGraphicsView(QGraphicsView * parent):QGraphicsView(parent)
{
	this->scene = new QGraphicsScene();
	this->setScene(scene);
	initView();
	this->show();
}

void DataModelGraphicsView::initView()
{
	setRenderHint(QPainter::Antialiasing);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	setBackgroundBrush(QColor(253, 250, 195));
	setDragMode(QGraphicsView::RubberBandDrag);
	setAcceptDrops(true);
}

QGraphicsScene *DataModelGraphicsView::getScene() const
{
	return scene;
}
