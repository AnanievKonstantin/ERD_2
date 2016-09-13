#include "EREssenceDesignation.h"

EREssenceDesignation::EREssenceDesignation(EREssenceData *data, QGraphicsWidget * parent):EREssence(data, parent)
{
	initEssence();
}

void EREssenceDesignation::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QLinearGradient linearGradient(QPointF(size().width()/4, -size().height()), QPointF(40, 40));
	linearGradient.setColorAt(0, Qt::yellow);
	linearGradient.setColorAt(1, Qt::white);

	QPen penOutLine(Qt::black, 1);
	painter->setBrush(*(new QBrush(linearGradient)));
	painter->setPen(penOutLine);

//	for(QPointF p:getPolygon())
//	{
//		painter->drawEllipse(p, 5,5);
//	}

	if (isSelected())
	{
		painter->setPen(QPen(QColor(0,255,100), 2, Qt::DashLine));
	}

	QPolygonF p;
	p << QPointF(10,0) << QPointF(size().width(),0) << QPointF(size().width(),0) <<  QPointF(size().width() - 10, size().height()) <<
	QPointF(size().width() - 10, size().height()) << QPointF(0,size().height()) << QPointF(0, size().height()) << QPointF(10,0);


	painter->drawPolygon(p);
	QPen pen(QColor(0,0,0));
	painter->setPen(pen);
	painter->drawText(0,0,size().width(),50,Qt::AlignCenter,getIdWithoutPath());
}

QRectF EREssenceDesignation::boundingRect() const
{
    qreal x = -50;
    qreal y =  -50;
    qreal w = this->size().width() + 50;
    qreal h = this->size().height() + 50;
	return QRectF(x,y, w,h);
}

QPolygonF EREssenceDesignation::getPolygon()
{
	return QPolygonF() << QPointF(pos().x() + 5,pos().y() + size().height()/2) << QPointF(pos().x() + size().width()/2,pos().y())
					   << QPointF(pos().x() + size().width() - 5,pos().y() + size().height()/2) << QPointF(pos().x() + size().width()/2, pos().y() + size().height())
					   << QPointF(pos().x() + 5,pos().y() + size().height()/2);

}

QPainterPath EREssenceDesignation::shape() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

void EREssenceDesignation::initEssence()
{
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
	setGeometry(0,0,180,50);
//	qDebug() << this->pos() <<"\n";
//	qDebug() << this->size() <<"\n";
}

void EREssenceDesignation::initMenu()
{

}

EREssenceDesignation::~EREssenceDesignation()
{
}
