#include "DataTable.h"

DataTable::DataTable(EREssenceData * data, QGraphicsWidget * parent ):EREssence(data, parent)
{
	initEssence();
}

void DataTable::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->drawRect(5,5,size().width(),size().height());

	QLinearGradient linearGradient(QPointF(size().width()/4, -size().height()), QPointF(40, 40));
	linearGradient.setColorAt(0, Qt::yellow);
	linearGradient.setColorAt(1, Qt::white);

	QPen penOutLine(Qt::black, 1);
	painter->setBrush(*(new QBrush(linearGradient)));
	painter->setPen(penOutLine);

	if (isSelected())
	{
		painter->setPen(QPen(QColor(0,255,100), 2, Qt::DashLine));
	}
	painter->drawRect(0,0,size().width(),size().height());


	QPen pen(QColor(0,0,0));
	painter->setPen(pen);
	painter->setFont(QFont(Support::fontFamilie, Support::fontSizeEssence));


	qreal x = 0;
	qreal y = deltaRow;

	painter->drawText(x,y,size().width(),50,Qt::AlignHCenter,getIdWithoutPath());

	y+=heightRow + deltaRow;
	painter->drawLine(0,y,size().width(),y);
	y+=deltaRow;

	foreach (QString key, getKeys())
	{
		painter->drawText(x,y,size().width(),50,Qt::AlignLeft,"    "+key);
		y+=heightRow + deltaRow;
	}

	painter->drawLine(0,y,size().width(),y);
	y+=deltaRow;
	foreach (QString attrs, getAttrs())
	{
		painter->drawText(x,y,size().width(),50,Qt::AlignLeft,"    "+attrs);
		y+=heightRow + deltaRow;
	}

}

QRectF DataTable::boundingRect() const
{
	qreal x = 0;
	qreal y =  0;
	qreal w = this->size().width()+20;
	qreal h = this->size().height()+20;
	return QRectF(x,y, w,h);
}

QPolygonF DataTable::getPolygon()
{
	return QPolygonF() << QPointF(pos().x(),pos().y() + size().height()/2) << QPointF(pos().x() + size().width()/2,pos().y())
					   << QPointF(pos().x() + size().width(),pos().y() + size().height()/2)
					   << QPointF(pos().x() + size().width()/2, pos().y() + size().height())
					   << QPointF(pos().x(),pos().y() + size().height()/2);
}

QPainterPath DataTable::shape() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

void DataTable::initEssence()
{
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

	qreal rows = getAttrs().length()+getKeys().length()+2;
	setGeometry(0, 0, 200,rows*(heightRow+deltaRow));



}

DataTable::~DataTable()
{

}
