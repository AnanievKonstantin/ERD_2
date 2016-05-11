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
		qDebug() << "Связь между " << first  << "и " << second<< "уже существует\n";
		return 1;
	}

	if(first ==  second)
	{
		qDebug() << "Рекурсивные связи запрещены. Рекурсия в" << first << "\n";
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

QList<QString> ERRelationsData::getAjasencyByName(QString id)
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

bool ERRelationsData::setCordFromAToB(QString A, QString B, int cord)
{
	for(int i =0; i < cordinality_table.length() ; i++)
	{
		std::tuple<QString, QString, int, int> & row = cordinality_table[i];
		if(std::get<0>(row) == A && std::get<1>(row) == B )
		{
			std::get<2>(row) = cord;
			break;
		}
		if(std::get<0>(row) == B && std::get<1>(row) == A )
		{
			std::get<3>(row) = cord;
			break;
		}
	}
}

void ERRelationsData::print()
{
	for(int i = 0; i < cordinality_table.length(); i++)
	{
		std::tuple<QString, QString, int, int> row = cordinality_table.at(i);
		qDebug() <<std::get<0>(row) <<" <-> "<<std::get<1>(row) <<": "<<Support::cardinalityToString(std::get<2>(row)) <<", "<<Support::cardinalityToString(std::get<3>(row)) <<";";
	}
}

void ERRelationsData::printList(QList<std::tuple<QString, QString, int, int> > list)
{
	for(int i = 0; i < list.length(); i++)
	{
		std::tuple<QString, QString, int, int> row = list.at(i);
		qDebug() <<std::get<0>(row) <<" <-> "<<std::get<1>(row) <<": "<<Support::cardinalityToString(std::get<2>(row)) <<", "<<Support::cardinalityToString(std::get<3>(row)) <<";";
	}
}

QList<std::tuple<QString, QString, int, int> > ERRelationsData::getCordinality_table() const
{
	return cordinality_table;
}
