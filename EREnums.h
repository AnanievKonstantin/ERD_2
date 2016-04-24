#ifndef ERENUMS_H
#define ERENUMS_H
#include <QDebug>

enum essence_type
{
	Base,
	Association,
	Designation,
	Characteristic,
	Property_key,
	Property_combinated_key,
	Property_default
};

enum cordinalyty
{
	ZeroOne,
	OneZero,
	OneOne,
	ZeroMany,
	OneMany
};


#endif // ERENUMS_H
