#include "ERRelationsData.h"

ERRelationsData::ERRelationsData()
{

}

bool ERRelationsData::deleteRelation(QString first, QString second)
{
	int one = 0;
	int two = 1;
	for(int i = 0; i < cordinality_table.length(); i++)
	{
		std::tuple<QString, QString, int, int> row = cordinality_table.at(i);
		if(std::get<0>(row) == first && std::get<1>(row) == second)
		{
			cordinality_table.removeOne(row);
			return true;
		}
		if(std::get<1>(row) == first && std::get<0>(row) == second)
		{
			cordinality_table.removeOne(row);
			return true;
		}
	}

	return false;
}

int ERRelationsData::addRelation(QString first, QString second, int cordinalityFirst, int cordinalitySecond)
{
	if(isExist(first, second) == true)
	{
		ConsoleOutput::getInstance()->printInfo("Связь между " + first  + "и "  + second + "уже существует\n");
		return 1;
	}

	if(first ==  second)
	{
		ConsoleOutput::getInstance()->printInfo("Рекурсивные связи запрещены. Рекурсия в" + first + "\n");
		return 2;
	}
	std::tuple<QString, QString, int, int> row = std::make_tuple(first, second, cordinalityFirst, cordinalitySecond);
	cordinality_table.append(row);

	return 0;

}

QList<std::tuple<QString, QString, int, int> > ERRelationsData::getAllAjasencyFor(QString id)
{

	QList<std::tuple<QString, QString, int, int>> ajesency;
	for(int i = 0; i < cordinality_table.length(); i++)
	{
		std::tuple<QString, QString, int, int> row = cordinality_table.at(i);
		if(std::get<0>(row) == id || std::get<1>(row) == id)
		{
			ajesency.append(row);
		}
	}

	return ajesency;
}

QList<QString> ERRelationsData::getAjasencyByName(QString id) const
{
	QList<std::tuple<QString, QString, int, int>> ajesency;
	QList<QString> names;

	for(int i = 0; i < cordinality_table.length(); i++)
	{
		std::tuple<QString, QString, int, int> row = cordinality_table.at(i);

		if(std::get<0>(row) == id)
		{
			names.append(std::get<1>(row));
			continue;
		}
		if(std::get<1>(row) == id)
		{
			names.append(std::get<0>(row));
			continue;
		}
	}

	return names;
}

bool ERRelationsData::isExist(QString first, QString second)
{
	for(int i = 0; i < cordinality_table.length(); i++)
	{
		std::tuple<QString, QString, int, int> row = cordinality_table.at(i);
		if(std::get<0>(row) == first && std::get<1>(row) == second)
		{
			return true;
		}
		if(std::get<0>(row) == second && std::get<1>(row) == first)
		{
			return true;
		}
	}

	return false;
}

bool ERRelationsData::renameEssence(QString old_name, QString new_name)
{
	for(std::tuple<QString, QString, int, int> & t: cordinality_table)
	{
		if(std::get<0>(t) == old_name)
		{
			std::get<0>(t) = new_name;
		}

		if(std::get<1>(t) == old_name)
		{
			std::get<1>(t) = new_name;
		}
	}
}

bool ERRelationsData::setCord(QString A, QString B, int cord_a, int cord_b)
{
	for(int i =0; i < cordinality_table.length() ; i++)
	{
		std::tuple<QString, QString, int, int> & row = cordinality_table[i];
		if(std::get<0>(row) == A && std::get<1>(row) == B )
		{
			std::get<2>(row) = cord_a;
			std::get<3>(row) = cord_b;
			break;
		}
		if(std::get<0>(row) == B && std::get<1>(row) == A )
		{
			std::get<2>(row) = cord_b;
			std::get<3>(row) = cord_a;
			break;
		}
	}
}

void ERRelationsData::print()
{
	for(int i = 0; i < cordinality_table.length(); i++)
	{
		std::tuple<QString, QString, int, int> row = cordinality_table.at(i);
//		qDebug() <<std::get<0>(row) <<" RELATE "<<std::get<1>(row) <<": "<<Support::cardinalityToString(std::get<2>(row)) <<", "<<Support::cardinalityToString(std::get<3>(row)) <<";";
	}
}

void ERRelationsData::printList(QList<std::tuple<QString, QString, int, int> > list)
{
	for(int i = 0; i < list.length(); i++)
	{
		std::tuple<QString, QString, int, int> row = list.at(i);
//		qDebug() <<std::get<0>(row) <<" RELATE "<<std::get<1>(row) <<": "<<Support::cardinalityToString(std::get<2>(row)) <<", "<<Support::cardinalityToString(std::get<3>(row)) <<";";
	}
}

QList<std::tuple<QString, QString, int, int> > ERRelationsData::getCordinality_table() const
{
	return cordinality_table;
}

void ERRelationsData::read(const QJsonObject &json)
{
	cordinality_table.clear();
	QJsonArray relations = json["relationsArray"].toArray();
	for(int i = 0; i < relations.size(); i++)
	{
		QJsonArray relation = relations.at(i).toArray();

		QString A	= relation.at(0).toString();
		QString B	= relation.at(1).toString();
		int cord_a	= relation.at(2).toInt();
		int cord_b	= relation.at(3).toInt();

		std::tuple<QString, QString, int, int> row;
		std::get<0>(row) = A;
		std::get<1>(row) = B;
		std::get<2>(row) = cord_a;
		std::get<3>(row) = cord_b;
		cordinality_table.append(row);
	}
}

void ERRelationsData::write(QJsonObject &json) const
{
	QJsonArray relations;
	for(int i = 0; i < cordinality_table.length(); i++)
	{
		QJsonArray relation;
		std::tuple<QString, QString, int, int> row = cordinality_table.at(i);
		relation << std::get<0>(row);
		relation << std::get<1>(row);
		relation << std::get<2>(row);
		relation << std::get<3>(row);
		relations << relation;
	}
	json["relationsArray"] = relations;
}

void ERRelationsData::clear()
{
	cordinality_table.clear();
}
