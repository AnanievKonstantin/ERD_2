#ifndef ERENUMS_H
#define ERENUMS_H
#include <QDebug>

/**
 * @brief The essence_type enum
	типы сущностей программы
 */
enum essence_type
{
	Base = 0,					// стержневая
	Association,				// ассоциативная
	Designation,				//обозначение
	Characteristic,				//характеристика
	Property_key,				//первичный ключ
	Property_combinated_key,	//составной ключ
	Property_foreign_key,		//внешний ключ
	Property_default,			//свойство
	Table						//таблица для Data model
};

/**
 * @brief The cordinalyty enum
	кардинальности ER модели
 */
enum cordinalyty
{
	ZeroOne = 0,
	OneOne,
	ZeroMany,
	OneMany,
	hiddenCord
};




#endif // ERENUMS_H
