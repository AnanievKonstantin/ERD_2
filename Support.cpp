#include "Support.h"

Support::Support()
{

}

QString Support::typeToString(int type)
{
	switch (type)
	{
		case essence_type::Base:
			return "Base";
			break;
		case essence_type::Association:
			return "Association";
			break;
		case essence_type::Designation:
			return "Designation";
			break;
		case essence_type::Characteristic:
			return "Characteristic";
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
		default:
			return "Error: unexpected type";
			break;
	}
}

QString Support::cardinalityToString(int cordinals)
{
	switch (cordinals) {
		case cordinalyty::ZeroOne:
			return "ZeroOne";
			break;
		case cordinalyty::OneZero:
			return "OneZero";
			break;
		case cordinalyty::OneOne:
			return "OneOne";
			break;
		case cordinalyty::OneMany:
			return "OneMany";
			break;
		case cordinalyty::ZeroMany:
			return "ZeroMany";
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
			|| type == essence_type::Property_key || type == essence_type::Characteristic)
	{
		return true;
	}

	return false;
}

bool Support::checkTypeCordinality(int type)
{
	if(type == cordinalyty::ZeroOne || type == cordinalyty::OneZero|| type == cordinalyty::OneOne
			|| type == cordinalyty::OneMany || type == cordinalyty::ZeroMany || type == cordinalyty::hiddenCord)
	{
		return true;
	}

	return false;
}
