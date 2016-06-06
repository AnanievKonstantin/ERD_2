#ifndef ERESSENCECHARACTERISTIC_H
#define ERESSENCECHARACTERISTIC_H

#include <QObject>
#include <Arrow.h>
#include <EREssence.h>


/**
 * @brief The EREssenceBase class
 *	Описывает графический объект представляющий характеристическую сущность
 */
class EREssenceCharacteristic: public EREssence
{
	public:
		EREssenceCharacteristic(EREssenceData * data, QGraphicsWidget * parent = 0);
		//bool contains(const QPointF &point) const;
		void paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget);
		QRectF boundingRect() const;
		QPolygonF getPolygon();
		QPainterPath shape() const;
		void initEssence();
		void initMenu();
		~EREssenceCharacteristic();
	private:
};
#endif // ERESSENCECHARACTERISTIC_H
