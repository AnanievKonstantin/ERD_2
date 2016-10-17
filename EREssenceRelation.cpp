#include "EREssenceRelation.h"

EREssenceRelation::EREssenceRelation(EREssenceData *data, QGraphicsWidget * parent):EREssence(data, parent)
{
	initEssence();
}

void EREssenceRelation::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QLinearGradient linearGradient(QPointF(size().width()/4, -size().height()), QPointF(40, 40));
	linearGradient.setColorAt(0, Qt::green);
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
	p << QPointF(0,size().height()/2) << QPointF(size().width()/2, 0) << QPointF(size().width(),size().height()/2)
	  << QPointF(size().width()/2, size().height())
	  << QPointF(0,size().height()/2);



	painter->drawPolygon(p);

	QPen pen(QColor(0,0,0));
	painter->setPen(pen);
	painter->setFont(QFont(Support::fontFamilie, Support::fontSizeEssence));
	painter->drawText(0,0,size().width(),size().height(),Qt::AlignCenter,getIdWithoutPath());
}

QRectF EREssenceRelation::boundingRect() const
{
    qreal x = 0;
    qreal y = 0;
    qreal w = this->size().width();
    qreal h = this->size().height();
	return QRectF(x,y, w,h);
}

QPolygonF EREssenceRelation::getPolygon()
{
	return QPolygonF() << QPointF(pos().x(), pos().y() + size().height()/2) << QPointF(pos().x() + size().width()/2,pos().y())
					   << QPointF(pos().x() + size().width(),pos().y() + size().height()/2)
					   << QPointF(pos().x() + size().width()/2, pos().y() + size().height())
					   << QPointF(pos().x() ,pos().y() + size().height()/2);
}

QPainterPath EREssenceRelation::shape() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

void EREssenceRelation::initEssence()
{
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
	setGeometry(0,0,180,60);
//	qDebug() << this->pos() <<"\n";
//	qDebug() << this->size() <<"\n";
}

void EREssenceRelation::initMenu()
{

}

EREssenceRelation::~EREssenceRelation()
{
}
