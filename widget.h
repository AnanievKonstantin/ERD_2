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
#include <RelationOperationWindow.h>
#include <QShortcut>
#include <QKeySequence>
#include <TreeModel.h>
#include <QTreeView>
#include <TreeModelForOneEssence.h>

class Widget : public QWidget
{
		Q_OBJECT

	public:
		Widget(QWidget *parent = 0);
		bool setUpSignalsAndSlots();
		~Widget();

	private:
		void initViev();

		void syncTreeViev();
		QHBoxLayout * layout;
		ERGraphicsView * erView;
		TreeModel * treeModel;
		QTreeView * treeViev;

		TreeModelForOneEssence* treeModelForOneEssence;
		QTreeView * treeVievOneEssence;

	public slots:
		void editEssence(QString id);
		void createEssence(int type);
		void addEssenceOnScreen(QString id);
		void removeEssence(QString id);
		void performRelationOperation(int action_code);
		void afterPerformRelationOperation(bool);
		void save();
		void treeViewEssenceUpdate(QString id);

};

#endif // WIDGET_H
