#ifndef ERESSENCEDESINATION_H
#define ERESSENCEDESINATION_H

#include <QObject>
#include <Arrow.h>
#include <EREssence.h>

/**
 * @brief The EREssenceBase class
 *	Описывает графический объект представляющий обозначающую сущность
 */

class EREssenceDesignation: public EREssence
{
	public:
		EREssenceDesignation(EREssenceData * data, QGraphicsWidget * parent = 0);
		//bool contains(const QPointF &point) const;
		void paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget);
		QRectF boundingRect() const;
		QPolygonF getPolygon();
		QPainterPath shape() const;
		void initEssence();
		void initMenu();
		~EREssenceDesignation();
	private:



};
#endif // ERESSENCEDESINATION_H
