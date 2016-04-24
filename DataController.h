#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include <QObject>
#include <QList>
#include <QString>
#include <EREssenceData.h>
#include <ERRelationsData.h>

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

	private:
		QList<EREssenceData*> list_essences;
		ERRelationsData relation_table;

};

#endif // DATACONTROLLER_H
