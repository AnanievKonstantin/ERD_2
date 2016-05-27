#ifndef ERENUMS_H
#define ERENUMS_H
#include <QDebug>

enum essence_type
{
	Base = 0,
	Association,
	Designation,
	Characteristic,
	Property_key,
	Property_combinated_key,
	Property_foreign_key,
	Property_default,
	Table
};

enum cordinalyty
{
	ZeroOne = 0,
	OneOne,
	ZeroMany,
	OneMany,
	hiddenCord
};




#endif // ERENUMS_H
