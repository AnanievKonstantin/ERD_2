#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include <QObject>
#include <QList>
#include <QString>
#include <EREssenceData.h>
#include <ERRelationsData.h>
#include <QRegExp>



/**
 * @brief The DataController class
 * Запрещается:
 *	дублирование имен сущностей
 *	дублирование имен атрубутов
 *	дублирование имен ключей
 *		за исключением создания системных дублей при установке связей.
 *	Запрещается ручное редактирование системных ключей и атрубутов. Системный атрибет имеет в имени название родителя. A::id
 *	запрещается характеризовать характеристику
 *  запрещается обозначать обозначение
 *	рекурсивно соединять сущность с собой
 *  Ассоциацию можно создавать при соединении двух сущностей. Затем к ней можно только подключать или отключать сущности
 *
 */
class DataController
{
	public:

		static DataController * getInstance();

		QList<std::tuple<QString, QString, int, int> > getRelationTable();
		//actrions
		int createEssence(QString id, int type, QList<QString> keys, QList<QString> attributes);
		int removeEssence(QString id);

		int createRelation(QString id_first, QString id_second, int cord_one, int cord_two);
		int removeRelation(QString id_first, QString id_second);

		int removeAttribute(QString id, QString attr_name);
		int addAttribute(QString id, QString attr_name);

		int removeKey(QString id, QString key_name);
		int addKey(QString id, QString key_name);

		int joinBaseToExistAssociation(QString essence, QString association, int cord);
		int setCordinality(QString id_a, QString id_b, int cord_A, int cord_B);

		int renameEssence(QString id_to_rename, QString new_id);
		//debug - print
		void printAllEssence();
		void printEssenceByID(QString id);
		void printRelations();

		QList<QString> getEssences();

		/**
		 * @brief getProperties
		 * вернет ключи соотвествено mode
		 * @param mode	1 - ключи единоличные - красные
		 *				2 - свойства - белые
		 *				3 - ключи составные
		 *
		 * @return
		 */
		QList<QString> getProperties(QString id, int mode);
		QList<QString> getAjesencyFor(QString id);

		EREssenceData * search(QString id);

	private:
		DataController();
		DataController(DataController const&){}
		DataController& operator=(DataController const&){}
		static DataController * self;

		//checks
		int checkBeforeCreationEssence(QString id, int type, QList<QString> keys, QList<QString> attributes);
		int checkBeforeCreationRelation(QString id_first, QString id_second, int cord_one, int cord_two);

		bool essenceIsExist(QString id);
		bool relationIsExist(QString id_first, QString id_second);

		bool keyISattr(QList<QString> keys, QList<QString> attributes);
		bool keyOrAttributeIsExist(QList<QString> keys, QList<QString> attrs);
		bool keyOrAttributeDublication(QList<QString> keys, QList<QString> attrs);
		bool keyOrAttributeIsNameOfEssence(QString id, QList<QString> keys = QList<QString>(), QList<QString> attrs = QList<QString>());

		bool oneOfTwoIs(int type_first, int type_second, int condition_type);
		int checkCordinality(QString first, QString second, int first_type, int second_type, int &cord_first, int &cord_second);

		//to perform action
		void insertKeyInCharacteristic(EREssenceData * e, QString key);
		void insertKeyInDesignation(EREssenceData * e, QString key);
		void insertKeyInBase(EREssenceData * e, QString key);
		void insertKeyInAssociation(EREssenceData * e, QString key);

		int createRelationBetweenBaseAndDesignation(			EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two);
		int createRelationBetweenBaseAndCharacteristic(			EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two);
		int createRelationBetweeAssociationAndDesignation(		EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two);
		int createRelationBetweenAssociationAndCharacteristic(	EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two);
		int createRelationBetweenBaseAndBaseWithNewRelation(	EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two);
		int createRelationBetweenDesignationAndCharacteristic(	EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two);


		int removeRelationBetweenEssences(EREssenceData * e1, EREssenceData * e2);
		int removeRelationBetweenBaseAndDesignation(EREssenceData * e1, EREssenceData * e2);

		int removeKeyFrom(QString id, QString key);




		QList<EREssenceData*> list_essences;
		ERRelationsData relation_table;

};

#endif // DATACONTROLLER_H
