#ifndef ERESSENCEPROPERTY_H
#define ERESSENCEPROPERTY_H

#include <QObject>
#include <Arrow.h>
#include <EREssence.h>
#include <DataController.h>

class EREssenceProperty: public EREssence
{
	public:
		EREssenceProperty(EREssenceData * data, QGraphicsWidget * parent = 0);
		//bool contains(const QPointF &point) const;
		void paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget);
		QRectF boundingRect() const;
		QPolygonF getPolygon();
		QPainterPath shape() const;
		void initEssence();
		void initMenu();
		~EREssenceProperty();
	private:
};
#endif // ERESSENCEPROPERTY_H
