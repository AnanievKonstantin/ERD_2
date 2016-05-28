#include "Support.h"

QString Support::fontFamilie = "Arial";
int Support::fontSizeEssence =9;
int Support::fontSizeProperty = 9;
qreal Support::tableHeightRow = 15;
qreal Support::tableDeltaRow = 5;

Support::Support()
{

}

QString Support::typeToString(int type)
{
	switch (type)
	{
		case essence_type::Base:
			return "Стержневая";
			break;
		case essence_type::Association:
			return "Ассоциативная";
			break;
		case essence_type::Designation:
			return "Обозначающая";
			break;
		case essence_type::Characteristic:
			return "Характеризующая";
			break;
		case essence_type::Property_key:
			return "Propery_key";
			break;
		case essence_type::Property_combinated_key:
			return "Property_combinated_key";
			break;
		case essence_type::Property_default:
			return "Property_default";
			break;
		case essence_type::Property_foreign_key:
			return "Property_foreign_key";
			break;
		default:
			return "Error: unexpected type";
			break;
	}
}

QString Support::cardinalityToString(int cordinals)
{
	switch (cordinals) {
		case cordinalyty::ZeroOne:
			return "0/1";
			break;
		case cordinalyty::OneOne:
			return "1/1";
			break;
		case cordinalyty::OneMany:
			return "1/M";
			break;
		case cordinalyty::ZeroMany:
			return "0/M";
			break;
		case cordinalyty::hiddenCord:
			return "";
			break;
		default:
			return "Error: unexpected cordinality type";
			break;
	}
}

bool Support::checkTypeEssence(int type)
{
	if(type == essence_type::Base || type == essence_type::Association || type == essence_type::Designation
			|| type == essence_type::Property_combinated_key || type == essence_type::Property_default
			|| type == essence_type::Property_key || type == essence_type::Characteristic || type == essence_type::Property_foreign_key)
	{
		return true;
	}

	return false;
}

bool Support::checkTypeCordinality(int type)
{
	if(type == cordinalyty::ZeroOne || type == cordinalyty::OneOne
			|| type == cordinalyty::OneMany || type == cordinalyty::ZeroMany || type == cordinalyty::hiddenCord)
	{
		return true;
	}


	return false;
}

QString Support::getStrippedProperty(QString nonStrippedProperty)
{
	return nonStrippedProperty.right(nonStrippedProperty.length() - nonStrippedProperty.lastIndexOf(":") - 1);
}

qreal Support::getTableHeightRow()
{
	return tableHeightRow;
}

qreal Support::getTableDeltaRow()
{
	return tableDeltaRow;
}
