#ifndef ESSENCEGRAPHICSCONTROLLER_H
#define ESSENCEGRAPHICSCONTROLLER_H

#include <QObject>
#include <QList>
#include <QString>
#include "EREssence.h"
#include "EREssenceProperty.h"
#include <QDebug>
#include "Arrow.h"
#include <QGraphicsScene>
#include <DataController.h>
#include <EREssenceBase.h>
#include <EREssenceCharacteristic.h>
#include <EREssenceDesignation.h>
#include <EREssenceRelation.h>
#include <EREssenceProperty.h>
#include <Support.h>
#include <DataTable.h>

class EssenceGraphicsController : public QObject
{
		Q_OBJECT
	public:
		static EssenceGraphicsController * instance();
		static void setSceneToErModel(QGraphicsScene * _scene);
		static void setSceneToDataModel(QGraphicsScene * _scene);


		void syncWithDataContriller();
//		bool addEssence(EREssence * essence);
//		bool addProperty(EREssenceProperty * property);
//		bool addArrow(Arrow * arrow);

//		void renameEssence(QString old_name, QString new_name);

//		EREssence * getEssence(QString id);
//		EREssence * getProperty(QString parent, QString name_property);
//		Arrow * getArrow(QString parent1, QString parent2);
		void print();
	private:
		EssenceGraphicsController(EssenceGraphicsController const&){}
		EssenceGraphicsController& operator=(EssenceGraphicsController const&){}
		explicit EssenceGraphicsController(QObject *parent = 0);
		static EssenceGraphicsController * self;
		static QGraphicsScene * er_scene;
		static QGraphicsScene * data_scene;

		void clearAll();
		void fillERScene();
		void fillDataScene();

//		QList<std::tuple<EREssence *, QList<EREssenceProperty *>>> essenceList;
		QList<EREssence *> essenceList;
		QList<EREssenceProperty *> propertyList;
		QList<Arrow * > arrowList;
		QList<DataTable *> tableList;
		QList<Arrow * > arrowTableList;

		void createEssenceWithPropertyWithCordinate();



	signals:
		void startEditEssence(QString id);
		void startFocucedEssence(QString id);
	public slots:
		void emitEditEssenceSignal(QString);
		void emitFocucedEssenceSignal(QString id);
};

#endif // ESSENCEGRAPHICSCONTROLLER_H
