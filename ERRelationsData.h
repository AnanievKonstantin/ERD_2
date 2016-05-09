#ifndef ERRELATIONSDATA_H
#define ERRELATIONSDATA_H

#include <QString>
#include <QDebug>
#include <QList>
#include <tuple>
#include <Support.h>

class ERRelationsData
{
	public:
		ERRelationsData();
		bool deleteRelation(QString first, QString second);
		int addRelation(QString first, QString second, int cordinalityFirst, int cordinalitySecond);
		QList<std::tuple<QString, QString, int, int>> getAllAjasencyFor(QString id);
		QList<QString> getAjasencyByName(QString id);
		bool isExist(QString first, QString second);
		bool renameEssence(QString old_name, QString new_name);


		void print();
		void printList(QList<std::tuple<QString, QString, int, int>> list);
		QList<std::tuple<QString, QString, int, int> > getCordinality_table() const;

private:
		QList<std::tuple<QString, QString, int, int>> cordinality_table;
};

#endif // ERRELATIONSDATA_H
