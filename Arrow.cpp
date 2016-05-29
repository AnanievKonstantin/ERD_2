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
	myStartItem->addArrow(this);
	myEndItem->addArrow(this);
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
//	path.addPolygon(arrowHead);
	return path;
}


void Arrow::updatePosition()
{
	QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
//	qDebug()  << "void Arrow::updatePosition()";
//	if(isTableDrawMode() == true)
//	{
//		calcConnectPointInTableMode(line,);
//	}

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

	if(table_draw_mode == false)
	{
		calcConnectPointInERMode(10, 10, line, sTextPos, eTextPos);

	}
	else
	{
		calcConnectPointInTableMode(line, sTextPos, eTextPos, 30);
	}

	if (qFuzzyCompare(line.length(), qreal(0.)))
		return;
	painter->setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	this->setLine(line);
	painter->drawLine(line);

	painter->drawText(sTextPos, sText);
	painter->drawText(eTextPos, eText);

}

void Arrow::calcConnectPointInERMode(int indent, int delta, QLineF & line, QPointF & sTextPos, QPointF & eTextPos)
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

//		sTextPos = {line.p1().x() + indent, line.p1().y() - indent/2};
//		eTextPos = {line.p2().x() - indent*1.1, line.p2().y() - indent/2};
	}

	if(s.x() > e.x())
	{
		line.setP1(start_points.at(0));
		line.setP2(end_points.at(2));

//		sTextPos = {line.p1().x() - indent*1.1, line.p1().y() - indent/2};
//		eTextPos = {line.p2().x() + indent, line.p2().y() - indent/2};
	}

	if(((s.x() + delta) > e.x()) && ((s.x() - delta) < e.x()))
	{
		if(s.y() > e.y())
		{
			line.setP1(start_points.at(1));
			line.setP2(end_points.at(3));

//			sTextPos = {line.p1().x() + indent/2, line.p1().y() - indent/2};
//			eTextPos = {line.p2().x() + indent/2, line.p2().y() + indent/2};
		}
	}

	if(((e.x() + delta) > s.x()) && ((e.x() - delta) < s.x()))
	{
		if(e.y() > s.y())
		{
			line.setP1(start_points.at(3));
			line.setP2(end_points.at(1));

//			sTextPos = {line.p1().x() + indent/2, line.p1().y() + indent/2};
//			eTextPos = {line.p2().x() + indent/2, line.p2().y() - indent/2};
		}
	}

	qreal mx = (line.p1().x() + line.p2().x())/2;
	qreal my = (line.p1().y() + line.p2().y())/2;


	if(line.p1().x() >= line.p2().x())
	{
		sTextPos.setX(mx + indent);
		eTextPos.setX(mx - indent);
	}
	if(line.p1().x() < line.p2().x())
	{
		sTextPos.setX(mx - indent);
		eTextPos.setX(mx +  indent);
	}

	if(line.p1().y() >= line.p2().y())
	{
		sTextPos.setY(my - indent);
		eTextPos.setY(my + indent);
	}
	if(line.p1().y() < line.p2().y())
	{
		sTextPos.setY(my - indent);
		eTextPos.setY(my + indent);
	}
}

void Arrow::calcConnectPointInTableMode(QLineF &line, QPointF &sTextPos, QPointF &eTextPos, qreal indent)
{
	std::tuple<QString, int, QString, int> connection =
			DataController::getInstance()->getConnectionAttributesFor(myStartItem->getId(), myEndItem->getId());

	QPointF s = myStartItem->pos();
	QPointF e = myEndItem->pos();

	if(s.x() > e.x())
	{
		e.setX(e.x() + myEndItem->size().width());
	}
	else
	{
		s.setX(s.x() + myStartItem->size().width());
	}


	qreal delta_s = Support::getTableHeightRow() + Support::getTableDeltaRow() + std::get<1>(connection)*(Support::getTableHeightRow()+ Support::getTableDeltaRow());
	qreal delta_e = Support::getTableHeightRow() + Support::getTableDeltaRow() + std::get<3>(connection)*(Support::getTableHeightRow()+ Support::getTableDeltaRow());

//	qDebug() << "1: " + std::get<0>(connection) <<std::get<1>(connection);
//	qDebug() << "3: " + std::get<2>(connection) <<std::get<3>(connection);

	s.setY(s.y() +delta_s);

	e.setY(e.y() +delta_e);

	line.setP1(s);
	line.setP2(e);


	qreal mx = (s.x() + e.x())/2;
	qreal my = (s.y() + e.y())/2;

	if(s.x() >= e.x())
	{
		sTextPos.setX(mx + indent);
		eTextPos.setX(mx - indent);
	}
	if(s.x() < e.x())
	{
		sTextPos.setX(mx - indent);
		eTextPos.setX(mx +  indent);
	}

	if(s.y() >= e.y())
	{
		sTextPos.setY(my - indent);
		eTextPos.setY(my + indent);
	}
	if(s.y() < e.y())
	{
		sTextPos.setY(my - indent);
		eTextPos.setY(my + indent);
	}




}


