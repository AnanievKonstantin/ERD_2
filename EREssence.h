#ifndef ERESSENCE_H
#define ERESSENCE_H

#include <QGraphicsWidget>
#include <QString>
#include <QPolygon>
#include <QRectF>
#include <QPainterPath>
#include <QVariant>
#include <QPointF>
#include <QStyleOptionGraphicsItem>
#include <Arrow.h>
#include <QMenu>
#include <QContextMenuEvent>
#include <QDebug>
#include <QPen>
#include <QPainter>
#include <QColor>
#include <QVector>
#include <EREssenceData.h>
class Arrow;

class EREssence: public QGraphicsWidget
{
	Q_OBJECT
	public:
		EREssence(EREssenceData * data, QGraphicsWidget * parent = 0);
		QString getId() const;
		QString getIdWithoutPath() const;
		QString & getNonConstId();
		void addArrow(Arrow *arrow);
		virtual QPolygonF getPolygon() = 0;
		QVariant itemChange(GraphicsItemChange change, const QVariant &value);
		void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
		void mousePressEvent(QGraphicsSceneMouseEvent * event);
		virtual void initEssence() = 0;
		int getType() const;
	private:
		EREssenceData * data;
		QList<Arrow *> arrows;

	signals:
		void edit(QString);
		void focued(QString);
	public slots:

};

#endif // ERESSENCE_H
