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

std::pair<QString, QString> Arrow::createCadinalityForAssociation(QString cord_to_split)
{

	ConsoleOutput::printSystemMassage(cord_to_split);
	if(cord_to_split == Support::cardinalityToString(cordinalyty::OneOne))
	{
		return std::make_pair(Support::cardinalityToString(cordinalyty::OneOne), Support::cardinalityToString(cordinalyty::OneOne));
	}
	if(cord_to_split == Support::cardinalityToString(cordinalyty::OneMany))
	{
		return std::make_pair(Support::cardinalityToString(cordinalyty::OneOne), Support::cardinalityToString(cordinalyty::OneMany));
	}
	if(cord_to_split == Support::cardinalityToString(cordinalyty::ZeroOne))
	{
		return std::make_pair(Support::cardinalityToString(cordinalyty::ZeroOne), Support::cardinalityToString(cordinalyty::OneMany));
	}
	if(cord_to_split == Support::cardinalityToString(cordinalyty::ZeroMany))
	{
		return std::make_pair(Support::cardinalityToString(cordinalyty::ZeroOne), Support::cardinalityToString(cordinalyty::OneMany));
	}

	ConsoleOutput::printSystemError("std::pair<QString, QString> Arrow::createCadinalityForAssociation(QString & cord_to_split) bad cardinality");
	return std::make_pair("__ERROR__", "__ERROR__");
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
        calcConnectPointInERMode(30, 10, line, sTextPos, eTextPos);
		if (qFuzzyCompare(line.length(), qreal(0.)))
			return;
		painter->setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		this->setLine(line);
		painter->drawLine(line);

		painter->drawText(sTextPos, sText);
		painter->drawText(eTextPos, eText);
	}
	else
	{
		QString toDrawSTesxt = sText;
		QString toDrawETesxt = eText;
		if(myStartItem->getType() == essence_type::Association)
		{
			std::pair<QString, QString> new_splited_cord = createCadinalityForAssociation(eText);
			toDrawSTesxt = std::get<0>(new_splited_cord);
			toDrawETesxt = std::get<1>(new_splited_cord);
		}
		else if(myEndItem->getType() == essence_type::Association)
		{
			std::pair<QString, QString> new_splited_cord = createCadinalityForAssociation(sText);
			toDrawSTesxt = std::get<0>(new_splited_cord);
			toDrawETesxt = std::get<1>(new_splited_cord);
		}
		calcConnectPointInTableMode(line, sTextPos, eTextPos, 30);

		if (qFuzzyCompare(line.length(), qreal(0.)))
			return;
		painter->setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		this->setLine(line);
		painter->drawLine(line);

		painter->drawText(sTextPos, toDrawSTesxt);
		painter->drawText(eTextPos, toDrawETesxt);
	}

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

    ///расчет точки привязки для линии
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
    ///конец расчета


    ///расчет точек привязки для текста кординальностей
    qreal mx = (line.p1().x() + line.p2().x())/2;
    qreal my = (line.p1().y() + line.p2().y())/2;

    qreal middle_x_p1_mx = (mx + line.p1().x())/2;
    qreal middle_y_p1_my = (my + line.p1().y())/2;

    qreal middle_x_p2_mx = (mx + line.p2().x())/2;
    qreal middle_y_p2_my = (my + line.p2().y())/2;


    if(line.p1().x() > line.p2().x())
	{
        sTextPos.setX(middle_x_p1_mx - indent);
        eTextPos.setX(middle_x_p2_mx + indent);
	}
	if(line.p1().x() < line.p2().x())
	{
        sTextPos.setX(middle_x_p1_mx + indent);
        eTextPos.setX(middle_x_p2_mx - indent);
	}

    if(line.p1().y() > line.p2().y())
    {
        sTextPos.setY(middle_y_p1_my - indent);
        eTextPos.setY(middle_y_p2_my + indent);
    }
    if(line.p1().y() < line.p2().y())
    {
        sTextPos.setY(middle_y_p1_my + indent);
        eTextPos.setY(middle_y_p2_my - indent);
    }

    ///конец расчета
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

    qreal mx_between_s_mx = (s.x() + mx)/2;
    qreal my_between_s_my = (s.y() + my)/2;
    qreal mx_between_e_mx = (e.x() + mx)/2;
    qreal my_between_e_my = (e.y() + my)/2;

	if(s.x() >= e.x())
	{
        sTextPos.setX(mx_between_s_mx + indent);
        eTextPos.setX(mx_between_e_mx - indent);
	}
	if(s.x() < e.x())
	{
        sTextPos.setX(mx_between_s_mx - indent);
        eTextPos.setX(mx_between_e_mx +  indent);
	}

	if(s.y() >= e.y())
	{
        sTextPos.setY(my_between_s_my - indent);
        eTextPos.setY(my_between_e_my + indent);
	}
	if(s.y() < e.y())
	{
        sTextPos.setY(my_between_s_my - indent);
        eTextPos.setY(my_between_e_my + indent);
	}




}


