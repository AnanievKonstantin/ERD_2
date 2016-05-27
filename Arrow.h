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

	bool isTableDrawMode() const {return table_draw_mode;}
	void enableTableDrawMode() {table_draw_mode = true;}
	void updatePosition();

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;

private:

	void calcConnectPointInERMode(int indent, int delta, QLineF & line, QPointF & sTextPos, QPointF & eTextPos);
	void calcConnectPointInTableMode(QLineF & line, QPointF & sTextPos, QPointF & eTextPos);
	QString sText = "";
	QString eText = "";

	EREssence *myStartItem;
	EREssence *myEndItem;
	QColor myColor;
	bool table_draw_mode = false;
//	QPolygonF arrowHead;




};
#endif // ARROW_H
