#include "DataModelGraphicsView.h"

void DataModelGraphicsView::wheelEvent(QWheelEvent *event)
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
