#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include <QObject>
#include <QList>
#include <QString>
#include <EREssenceData.h>
#include <ERRelationsData.h>

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
 *
 */
class DataController
{
	public:
		DataController();

		//checks
		int checkBeforeCreationEssence(QString id, int type, QList<QString> keys, QList<QString> attributes);
		int checkBeforeCreationRelation(QString id_first, QString id_second, int cord_one, int cord_two);
		bool essenceIsExist(QString id);
		bool relationIsExist(QString id_first, QString id_second);
		bool keyISattr(QList<QString> keys, QList<QString> attributes);
		bool keyOrAttributeIsExist(QList<QString> keys, QList<QString> attrs);
		bool keyOrAttributeDublication(QList<QString> keys, QList<QString> attrs);




		//actrions
		int createEssence(QString id, int type, QList<QString> keys, QList<QString> attributes);
		int removeEssence(QString id);

		int createRelation(QString id_first, QString id_second, int cord_one, int cord_two);
		int removeRelation(QString id_first, QString id_second);

		int removeAttribute(QString id, QString attr_name);
		int addAttribute(QString id, QString attr_name);

		int removeKey(QString id, QString key_name);
		int addKey(QString id, QString key_name);

		EREssenceData * search(QString id);

		//debug - print
		void printAllEssence();
		void printEssenceByID(QString id);
		void printRelations();
		void insertRelation(QString A, QString B);

	private:
		QList<EREssenceData*> list_essences;
		ERRelationsData relation_table;

};

#endif // DATACONTROLLER_H
