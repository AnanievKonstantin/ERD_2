#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include "ERGraphicsView.h"
#include "EREssenceBase.h"
#include "ERGraphicsView.h"
#include <QGraphicsRectItem>
#include "EREssenceDesignation.h"
#include "EREssenceCharacteristic.h"
#include "EREssenceRelation.h"
#include "EREssenceProperty.h"
#include <Arrow.h>
#include <DataController.h>
#include <EssenceGraphicsController.h>
#include <EssenseCreateWindow.h>

class Widget : public QWidget
{
		Q_OBJECT

	public:
		Widget(QWidget *parent = 0);
		bool setUpSignalsAndSlots();
		~Widget();

	private:
		void initViev();

		QHBoxLayout * layout;
		ERGraphicsView * erView;
	public slots:
		void editEssence(QString id);
		void createEssence(int type);
		void addEssenceOnScreen(QString id);
		void removeEssence(QString id);

};

#endif // WIDGET_H
