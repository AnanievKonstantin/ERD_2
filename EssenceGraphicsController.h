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

/**
 * @brief The EssenceGraphicsController class
 *	описывает контроллер графических представлений.
 */
class EssenceGraphicsController : public QObject
{
		Q_OBJECT
	public:
		static EssenceGraphicsController * instance();
		static void setSceneToErModel(QGraphicsScene * _scene);
		static void setSceneToDataModel(QGraphicsScene * _scene);


		/**
		 * @brief syncWithDataContriller
		 *	синхронизирует графическое представление с данными диаграммы
		 */
		void syncWithDataContriller();

		//debug print in termonal
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
