#ifndef ARROW_H
#define ARROW_H


#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include "EREssenceData.h"
#include <EREssence.h>
#include <DataController.h>
#include <QTextItem>

class EREssence;
class DataController;
class Arrow : public QGraphicsLineItem
{
public:

	Arrow(EREssence *startItem, EREssence *endItem,QString sText, QString eText,
	  QGraphicsItem *parent = 0);
	~Arrow();
//	void mousePressEvent(QGraphicsSceneMouseEvent *event);
//	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	int type() const Q_DECL_OVERRIDE { return Type; }
	QRectF boundingRect() const Q_DECL_OVERRIDE;
	QPainterPath shape() const Q_DECL_OVERRIDE;
	void setColor(const QColor &color) { myColor = color; }
	EREssence *startItem() const { return myStartItem; }
	EREssence *endItem() const { return myEndItem; }


	/**
	 * @brief createCadinalityForAssociation
	 * Получает на вход кардинальность и положение сущности типа не ассоциация(любой другой тип).
	 * Разделяет кардинальность от не ассоциативной сущности в соотвествии:
	 * 1/1 -> 1/1 - 1/1
	 * 1/M -> 1/1 - 1/M
	 * 0/1 -> 0/1 - 1/M
	 * 0/M -> 0/1 - 1/M
	 * @param cord_to_split кадинальность от не ассоциации для разделения на две кардинальности для табличного представления
	 *
	 *
	 */
	std::pair<QString, QString>	createCadinalityForAssociation(QString cord_to_split);
	bool isTableDrawMode() const {return table_draw_mode;}
	void enableTableDrawMode() {table_draw_mode = true;}
	void updatePosition();

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;

private:

	void calcConnectPointInERMode(int indent, int delta, QLineF & line, QPointF & sTextPos, QPointF & eTextPos);
	void calcConnectPointInTableMode(QLineF & line, QPointF & sTextPos, QPointF & eTextPos, qreal indent);
	QString sText = "";
	QString eText = "";

	EREssence *myStartItem;
	EREssence *myEndItem;
	QColor myColor;
	bool table_draw_mode = false;
//	QPolygonF arrowHead;




};
#endif // ARROW_H
