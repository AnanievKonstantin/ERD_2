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

class EssenceGraphicsController : public QObject
{
		Q_OBJECT
	public:
		static EssenceGraphicsController * instance();
		static void setScene(QGraphicsScene * _scene);


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
		static QGraphicsScene * scene;


//		QList<std::tuple<EREssence *, QList<EREssenceProperty *>>> essenceList;
		QList<EREssence *> essenceList;
		QList<EREssenceProperty *> propertyList;
		QList<Arrow * > arrowList;


	signals:
		void startEditEssence(QString id);
	public slots:
		void emitEditEssenceSignal(QString);
};

#endif // ESSENCEGRAPHICSCONTROLLER_H
