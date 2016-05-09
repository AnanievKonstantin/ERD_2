#ifndef ERESSENCEBASE_H
#define ERESSENCEBASE_H
#include <QObject>
#include <Arrow.h>
#include <EREssence.h>
#include <QMenu>

class EREssenceBase: public EREssence
{
	public:
		EREssenceBase(EREssenceData * data, QGraphicsWidget * parent = 0);
		//bool contains(const QPointF &point) const;
		void paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget);
		QRectF boundingRect() const;
		QPolygonF getPolygon();
		QPainterPath shape() const;
		void initEssence();
		~EREssenceBase();
	private:
};
#endif // ERESSENCEBASE_H
