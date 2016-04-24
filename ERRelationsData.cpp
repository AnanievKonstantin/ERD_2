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

QList<std::tuple<QString, QString, int, int> > &ERRelationsData::getAllAjasencyFor(QString id)
{

	QList<std::tuple<QString, QString, int, int>> ajesency;
	for(int i = 0; i < cordinality_table.length(); i++)
	{
		std::tuple<QString, QString, int, int> row = cordinality_table.at(i);
		if(std::get<0>(row) == id)
		{
			ajesency.append(row);
		}
	}

	return ajesency;
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

void ERRelationsData::print()
{
	for(int i = 0; i < cordinality_table.length(); i++)
	{
		std::tuple<QString, QString, int, int> row = cordinality_table.at(i);
		qDebug() <<std::get<0>(row) <<" <-> "<<std::get<1>(row) <<": "<<Support::cardinalityToString(std::get<2>(row)) <<", "<<Support::cardinalityToString(std::get<3>(row)) <<";\n";
	}
}
