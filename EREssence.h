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

/**
 * @brief The EREssence class
 *	базовый класс для графических обьектов диаграммы
 */
class EREssence: public QGraphicsWidget
{
	Q_OBJECT
	public:
		EREssence(EREssenceData * data, QGraphicsWidget * parent = 0);
		QString getId() const;

		/**
		 * @brief getIdWithoutPath
		 * @return
		 *	вернёт имя без системного пути
		 */
		QString getIdWithoutPath() const;
		QString & getNonConstId();

		/**
		 * @brief addArrow
		 *	добавит стрелку для обновления в список стрелок
		 * @param arrow
		 */
		void addArrow(Arrow *arrow);
		virtual QPolygonF getPolygon() = 0;
		QVariant itemChange(GraphicsItemChange change, const QVariant &value);
		void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
		void mousePressEvent(QGraphicsSceneMouseEvent * event);
		virtual void initEssence() = 0;
		int getType() const;
		QList<QString> getAttrs();
		QList<QString> getKeys();
	private:
		EREssenceData * data;
		QList<Arrow *> arrows;

	signals:
		void edit(QString);
		void focued(QString);
	public slots:

};

#endif // ERESSENCE_H
