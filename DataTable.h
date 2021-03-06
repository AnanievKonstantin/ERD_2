#ifndef DATATABLE_H
#define DATATABLE_H

#include <EREssence.h>
#include <QGraphicsGridLayout>

/**
 * @brief The DataTable class
 *	описввает графическую таблицу
 */
class DataTable: public EREssence
{
	public:
		DataTable(EREssenceData * data, QGraphicsWidget * parent = 0);
		void paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget);
		QRectF boundingRect() const;
		QPolygonF getPolygon();
		QPainterPath shape() const;
		void initEssence();
		~DataTable();

	private:


};

#endif // DATATABLE_H
