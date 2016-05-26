#include "Arrow.h"
#include <math.h>
#include <QPen>
#include <QPainter>


Arrow::Arrow(EREssence *startItem, EREssence *endItem, QString sText, QString eText, QGraphicsItem *parent)
	: QGraphicsLineItem(parent)
{
	myStartItem = startItem;
	myEndItem = endItem;
	myColor = Qt::black;
	setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	startItem->addArrow(this);
	endItem->addArrow(this);
	this->eText = eText;
	this->sText = sText;

}

Arrow::~Arrow()
{
}

//void Arrow::mousePressEvent(QGraphicsSceneMouseEvent * event)
//{
//	if(event->button() == Qt::MouseButton::LeftButton)
//	{
//		qDebug() << "void Arrow::mousePressEvent(QGraphicsSceneMouseEvent * event)\n";
//		myColor.setRgb(0,255,0);
//		update();
//	}
//}

//void Arrow::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
//{
//	qDebug() << "void Arrow::mouseMoveEvent(QGraphicsSceneMouseEvent * event)\n";
//	myColor.setRgb(255,0,0);
//	update();
//}
//! [0]

//! [1]
QRectF Arrow::boundingRect() const
{
	qreal extra = (pen().width() + 20) / 2.0;

	return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
									  line().p2().y() - line().p1().y()))
		.normalized()
		.adjusted(-extra, -extra, extra, extra);
}

QPainterPath Arrow::shape() const
{
	QPainterPath path = QGraphicsLineItem::shape();
	path.addPolygon(arrowHead);
	return path;
}


void Arrow::updatePosition()
{
	QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
	setLine(line);
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
		  QWidget *)
{
	if (!startItem() || !endItem())
			return;
	QLineF line;

	QPointF sTextPos;
	QPointF eTextPos;

	calcConnectPoint(50, 30, line, sTextPos, eTextPos);

	if (qFuzzyCompare(line.length(), qreal(0.)))
		return;
	painter->setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	this->setLine(line);
	painter->drawLine(line);

	painter->drawText(sTextPos, sText);
	painter->drawText(eTextPos, eText);

}

void Arrow::calcConnectPoint(int indent, int delta, QLineF & line, QPointF & sTextPos, QPointF & eTextPos)
{

	QPointF s = startItem()->pos();
	s.setX(s.x() + startItem()->size().width()/2);
	s.setY(s.y() + startItem()->size().height()/2);
	QPointF e = endItem()->pos();
	e.setX(e.x() + endItem()->size().width()/2);
	e.setY(e.y() + endItem()->size().height()/2);


	QPolygonF start_points = startItem()->getPolygon();
	QPolygonF end_points = endItem()->getPolygon();
	if(s.x() < e.x())
	{
		line.setP1(start_points.at(2));
		line.setP2(end_points.at(0));

		sTextPos = {line.p1().x() + indent, line.p1().y() - indent/2};
		eTextPos = {line.p2().x() - indent*1.1, line.p2().y() - indent/2};
	}

	if(s.x() > e.x())
	{
		line.setP1(start_points.at(0));
		line.setP2(end_points.at(2));

		sTextPos = {line.p1().x() - indent*1.1, line.p1().y() - indent/2};
		eTextPos = {line.p2().x() + indent, line.p2().y() - indent/2};
	}

	if(((s.x() + delta) > e.x()) && ((s.x() - delta) < e.x()))
	{
		if(s.y() > e.y())
		{
			line.setP1(start_points.at(1));
			line.setP2(end_points.at(3));

			sTextPos = {line.p1().x() + indent/2, line.p1().y() - indent/2};
			eTextPos = {line.p2().x() + indent/2, line.p2().y() + indent/2};
		}
	}

	if(((e.x() + delta) > s.x()) && ((e.x() - delta) < s.x()))
	{
		if(e.y() > s.y())
		{
			line.setP1(start_points.at(3));
			line.setP2(end_points.at(1));

			sTextPos = {line.p1().x() + indent/2, line.p1().y() + indent/2};
			eTextPos = {line.p2().x() + indent/2, line.p2().y() - indent/2};
		}
	}
}


