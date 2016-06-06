#ifndef ERESSENCERELATION_H
#define ERESSENCERELATION_H

#include <QObject>
#include <Arrow.h>
#include <EREssence.h>


/**
 * @brief The EREssenceBase class
 *	Описывает графический объект представляющий ассоциативную сущность
 */
class EREssenceRelation: public EREssence
{
	public:
		EREssenceRelation(EREssenceData * data, QGraphicsWidget * parent = 0);
		//bool contains(const QPointF &point) const;
		void paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget);
		QRectF boundingRect() const;
		QPolygonF getPolygon();
		QPainterPath shape() const;
		void initEssence();
		void initMenu();
		~EREssenceRelation();
	private:
};
#endif // ERESSENCERELATION_H
