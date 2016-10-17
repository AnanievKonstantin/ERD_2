#include "EREssenceProperty.h"

EREssenceProperty::EREssenceProperty(EREssenceData *data, QGraphicsWidget * parent): EREssence(data, parent)
{
	initEssence();
}

void EREssenceProperty::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QLinearGradient linearGradient(QPointF(size().width()/4, -size().height()), QPointF(40, 40));
	QFont font(Support::fontFamilie, Support::fontSizeProperty);
	if(getType() == essence_type::Property_default)
	{
		linearGradient.setColorAt(0, Qt::white);
		linearGradient.setColorAt(1, Qt::white);
	}
	if(getType() == essence_type::Property_key)
	{
		linearGradient.setColorAt(0, Qt::red);
		linearGradient.setColorAt(1, Qt::white);
		font.setUnderline(true);
	}

	if(getType() == essence_type::Property_combinated_key)
	{
		linearGradient.setColorAt(0, Qt::yellow);
		linearGradient.setColorAt(1, Qt::white);
		font.setUnderline(true);
	}


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
	painter->drawEllipse(0,0, size().width(), size().height());

	QPen pen(QColor(0,0,0));
	painter->setPen(pen);
	painter->setFont(font);
	painter->drawText(0,0,size().width(), size().height(),Qt::AlignCenter,getIdWithoutPath());
}

QRectF EREssenceProperty::boundingRect() const
{
    qreal x = 0;
    qreal y = 0;
    qreal w = this->size().width();
    qreal h = this->size().height();
	return QRectF(x,y, w,h);
}

QPolygonF EREssenceProperty::getPolygon()
{
	return QPolygonF() << QPointF(pos().x() ,pos().y() + size().height()/2) << QPointF(pos().x() + size().width()/2,pos().y())
					   << QPointF(pos().x() + size().width(), pos().y() + size().height()/2) << QPointF(pos().x() + size().width()/2, pos().y() + size().height())
					   << QPointF(pos().x() ,pos().y() + size().height()/2);
}

QPainterPath EREssenceProperty::shape() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

void EREssenceProperty::initEssence()
{
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
//	int width = getId().length()*10;
	setGeometry(0,0,190,40);



//	qDebug() << this->pos() <<"\n";
//	qDebug() << this->size() <<"\n";
}

void EREssenceProperty::initMenu()
{

}

EREssenceProperty::~EREssenceProperty()
{
}
