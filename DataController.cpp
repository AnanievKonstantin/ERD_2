#include "DataController.h"

DataController * DataController::self = nullptr;

DataController::DataController()
{

}

int DataController::checkBeforeCreationEssence(QString id, int type, QList<QString> keys, QList<QString> attributes)
{


	bool error = false;
	if(id == "")
	{
		ConsoleOutput::getInstance()->printInfo("Имя сущности не может быть пустым");
		error = true;
	}

	if(essenceIsExist(id) == true)
	{
		ConsoleOutput::getInstance()->printInfo("Сущность с таким именем уже существует");
		error = true;
	}

	if(Support::checkTypeEssence(type) == false)
	{
		ConsoleOutput::getInstance()->printInfo("Указан не известный тип сущности");
		error = true;
	}

	if(keys.length() == 0)
	{
		ConsoleOutput::getInstance()->printInfo("Сущность должна содержать минимум один ключ");
		error = true;
	}

	if(attributes.length() == 0)
	{
		ConsoleOutput::getInstance()->printInfo("Сущность должна содержать минимум один атрибут");
		error = true;
	}

	if(keyISattr(keys, attributes) == true)
	{
		ConsoleOutput::getInstance()->printInfo("Имена свойств сущности должны быть уникальны");
		error = true;
	}

	if(keyOrAttributeIsExist(keys, attributes) == true)
	{
		ConsoleOutput::getInstance()->printInfo("Имена свойств сущности должны быть уникальны");
		error = true;
	}

	if(keyOrAttributeDublication(keys, attributes) == true)
	{
		ConsoleOutput::getInstance()->printInfo("Имена свойств сущности должны быть уникальны");
		error = true;
	}

	if(keyOrAttributeIsNameOfEssence(id, keys, attributes) == true)
	{
		ConsoleOutput::getInstance()->printInfo("Имена свойств сущности не могут быть идентичны имени сущности");
		error = true;
	}
	if(error == true)
	{
		return 10;
	}

	return 0;
}

int DataController::checkBeforeCreationRelation(QString id_first, QString id_second, int cord_one, int cord_two)
{
	if(essenceIsExist(id_first) != true || essenceIsExist(id_second) != true )
	{
		ConsoleOutput::getInstance()->printInfo("Имена(Имя) связуемых сущностей не существуют");
		return 9;
	}

	if(id_first == id_second)
	{
		ConsoleOutput::getInstance()->printInfo("Создание рекурсивных сущностей не разрешено");
		return 11;
	}

	if(relationIsExist(id_first, id_second) == true)
	{
		if(search(id_first)->getType() == essence_type::Base && search(id_second)->getType() == essence_type::Base)
		{
			ConsoleOutput::getInstance()->printInfo("Создаётся ассоциация");
			return 0;
		}
		QString msg("Связь между " + id_first + " и " + id_second + " уже существует.");
		ConsoleOutput::getInstance()->printInfo(msg);
		return 10;
	}



	return 0;
}



bool DataController::essenceIsExist(QString id)
{
	foreach (EREssenceData *e, list_essences)
	{
		if(e->getId() == id)
		{
			return true;
		}
	}

	return false;
}

bool DataController::relationIsExist(QString id_first, QString id_second)
{
	if(relation_table.isExist(id_first, id_second) == true)
	{
		return true;
	}

	return false;
}

bool DataController::keyISattr(QList<QString> keys, QList<QString> attributes)
{
	foreach (QString key, keys)
	{
		foreach (QString attr, attributes)
		{
			if(key == attr)
			{
				QString msg("Ошибка в именовании свойств сущности. Ключ: " + key + " идентичен атрибуту " + attr);
				ConsoleOutput::getInstance()->printInfo(msg);
				return true;
			}
		}
	}
	return false;
}

bool DataController::keyOrAttributeIsExist(QList<QString> keys, QList<QString> attrs)
{
	bool exist = false;
	foreach (EREssenceData * e, list_essences)
	{
		foreach (QString key, keys)
		{
			if(e->getKeys().contains(key) || e->getAttributes().contains(key))
			{
				ConsoleOutput::getInstance()->printInfo("Ключ: " + key +" уже существует в списке свойств сущности: " +e->getId());
				exist = true;
			}
		}
		foreach (QString attr, attrs)
		{
			if(e->getAttributes().contains(attr) || e->getKeys().contains(attr))
			{
				ConsoleOutput::getInstance()->printInfo("Атрибут: " + attr +" уже существует в списке свойств сущности: " + e->getId());
				exist = true;
			}
		}
	}

	if(exist == true)
	{
		return true;
	}

	return false;
}

bool DataController::keyOrAttributeDublication(QList<QString> keys, QList<QString> attrs)
{
	bool dublicatesIsExist = false;
	foreach (QString key, keys)
	{
		if(keys.count(key) > 1)
		{
			ConsoleOutput::getInstance()->printInfo("Ключ: "  + key + " дублируется.");
			dublicatesIsExist = true;
		}
	}

	foreach (QString attr, attrs)
	{
		if(attrs.count(attr) > 1)
		{
			ConsoleOutput::getInstance()->printInfo("Атрибут: " + attr + " дублируется.");
			dublicatesIsExist = true;
		}
	}

	return dublicatesIsExist;
}

bool DataController::keyOrAttributeIsNameOfEssence(QString id, QList<QString> keys, QList<QString> attrs)
{
	bool isName = false;
	foreach (QString key, keys)
	{
		if(key == id)
		{
			ConsoleOutput::getInstance()->printInfo("Ключ: " + key + " равен имени сущности. " + id);
			isName = true;
		}
	}

	foreach (QString attr, attrs)
	{
		if(attr == id)
		{
			ConsoleOutput::getInstance()->printInfo("Атрибут: " + attr + " равен имени сущности " + id);
			isName = true;
		}
	}

	foreach (EREssenceData * d, list_essences)
	{
		if(keys.contains(d->getId()))
		{
			isName = true;
		}
		if(attrs.contains(d->getId()))
		{
			isName = true;
		}
	}

	return isName;
}


bool DataController::oneOfTwoIs(int type_first, int type_second, int condition_type)
{
	if(Support::checkTypeEssence(type_first) && Support::checkTypeEssence(type_second) && Support::checkTypeEssence(condition_type))
	{
		if(type_first == condition_type)	return true;
		if(type_second == condition_type)	return true;
	}
	else
	{
		ConsoleOutput::getInstance()->printInfo("Указаны не известные кардинальности");
		return false;
	}

	return false;
}

int DataController::checkCordinality(QString first, QString second, int first_type, int second_type, int & cord_first, int & cord_second)
{
	if(Support::checkTypeCordinality(cord_first) != true || Support::checkTypeCordinality(cord_second) != true)
	{
		ConsoleOutput::getInstance()->printInfo("Задана неизвестная кардинальность");
		return -10;
	}

	if(oneOfTwoIs(first_type, second_type, essence_type::Designation) == true && oneOfTwoIs(first_type, second_type, essence_type::Characteristic) == true)
	{
		if(	(cord_first == cordinalyty::OneOne	&&	cord_second == cordinalyty::OneOne)		||
			(cord_first == cordinalyty::OneOne	&&	cord_second == cordinalyty::OneMany))
		{
			if((first_type == essence_type::Designation && cord_first != cordinalyty::OneOne) ||
			   (second_type == essence_type::Designation && cord_second != cordinalyty::OneOne))
			{
				ConsoleOutput::getInstance()->printInfo("Для обозначений и характеристик возможны только следующие сочетания кардинальностей: 1/1 - 1/M или 1/1 - 1/1");
				return -10;
			}
			return 0;
		}
		else
		{
			ConsoleOutput::getInstance()->printInfo("Для обозначений и характеристик возможны только следующие сочетания кардинальностей: 1/1 - 1/M или 1/1 - 1/1");
			return -10;
		}
	}

	if(oneOfTwoIs(first_type, second_type, essence_type::Designation) == true && oneOfTwoIs(first_type, second_type, essence_type::Association) == true)
	{
		if(	(cord_first == cordinalyty::OneOne	&&	cord_second == cordinalyty::OneOne)		||
			(cord_first == cordinalyty::OneOne	&&	cord_second == cordinalyty::OneMany)	||
			(cord_first == cordinalyty::OneMany	&&	cord_second == cordinalyty::OneOne))
		{
			return 0;
		}
		else
		{
			ConsoleOutput::getInstance()->printInfo("Для обозначений и Ассоциации возможны только следующие сочетания кардинальностей: 1/1 - 1/M или 1/1 - 1/1 или 1/M - 1/1");
			return -20;
		}
	}

	if(oneOfTwoIs(first_type, second_type, essence_type::Designation) == true && oneOfTwoIs(first_type, second_type, essence_type::Base) == true)
	{
		if(	(cord_first == cordinalyty::OneOne	&&	cord_second == cordinalyty::OneOne)		||
			(cord_first == cordinalyty::OneOne	&&	cord_second == cordinalyty::OneMany)	||
			(cord_first == cordinalyty::OneMany	&&	cord_second == cordinalyty::OneOne))
		{
			if((first_type == essence_type::Designation && cord_first != cordinalyty::OneOne) ||
			   (second_type == essence_type::Designation && cord_second != cordinalyty::OneOne))
			{
				ConsoleOutput::getInstance()->printInfo("Для обозначений и стержневых сущностей возможны только следующие сочетания кардинальностей: 1/1 - 1/M или 1/1 - 1/1");
				return -30;
			}
			return 0;
		}
		else
		{
			ConsoleOutput::getInstance()->printInfo("Для обозначений и стержневых сущностей возможны только следующие сочетания кардинальностей: 1/1 - 1/M или 1/1 - 1/1");
			return -30;
		}
	}

	if(oneOfTwoIs(first_type, second_type, essence_type::Characteristic) == true && oneOfTwoIs(first_type, second_type, essence_type::Base) == true)
	{
		if(	(cord_first == cordinalyty::OneOne	&&	cord_second == cordinalyty::OneOne)		||
			(cord_first == cordinalyty::OneOne	&&	cord_second == cordinalyty::OneMany)	||
			(cord_first == cordinalyty::OneMany	&&	cord_second == cordinalyty::OneOne))
		{
			if((first_type == essence_type::Base && cord_first != cordinalyty::OneOne) ||
			   (second_type == essence_type::Base && cord_second != cordinalyty::OneOne))
			{
				ConsoleOutput::getInstance()->printInfo("Для характеристик и стержневых сущностей возможны только следующие сочетания кардинальностей: 1/M - 1/1 или 1/1 - 1/1");
				return -40;
			}
			return 0;
		}
		else
		{
			ConsoleOutput::getInstance()->printInfo("Для характеристик и стержневых сущностей возможны только следующие сочетания кардинальностей: 1/M - 1/1 или 1/1 - 1/1");
			return -40;
		}
	}

	if(oneOfTwoIs(first_type, second_type, essence_type::Characteristic) == true && oneOfTwoIs(first_type, second_type, essence_type::Association) == true)
	{
		if(	(cord_first == cordinalyty::OneOne	&&	cord_second == cordinalyty::OneOne)		||
			(cord_first == cordinalyty::OneOne	&&	cord_second == cordinalyty::OneMany)	||
			(cord_first == cordinalyty::OneMany	&&	cord_second == cordinalyty::OneOne))
		{
			if((first_type == essence_type::Association && cord_first != cordinalyty::OneOne) ||
			   (second_type == essence_type::Association && cord_second != cordinalyty::OneOne))
			{
				ConsoleOutput::getInstance()->printInfo("Для характеристик и ассоцтаций возможны только следующие сочетания кардинальностей: 1/M - 1/1 или 1/1 - 1/1");
				return -50;
			}
			return 0;
		}
		else
		{
			ConsoleOutput::getInstance()->printInfo("Для характеристик и ассоцтаций возможны только следующие сочетания кардинальностей: 1/M - 1/1 или 1/1 - 1/1");
			return -50;
		}
	}

	if(oneOfTwoIs(first_type, second_type, essence_type::Base) == true && oneOfTwoIs(first_type, second_type, essence_type::Association) == true)
	{
		if(cord_first == cordinalyty::hiddenCord	||	cord_second == cordinalyty::hiddenCord)
		{
			return 0;
		}
		else
		{
			EREssenceData * e1 = search(first);
			EREssenceData * e2 = search(second);
			if(e1->getType() == essence_type::Association)
			{
				ConsoleOutput::getInstance()->printStartActionInfo("Для ассоциации " + first + " устновлена скрытая кардинальность");
				cord_first = cordinalyty::hiddenCord;
				return 0;
			}
			if(e2->getType() == essence_type::Association)
			{
				ConsoleOutput::getInstance()->printStartActionInfo("Для ассоциации " + second + " устновлена скрытая кардинальность");
				cord_second = cordinalyty::hiddenCord;
				return 0;
			}
			return -10;
		}
	}

	if(oneOfTwoIs(first_type, second_type, essence_type::Base) == true && oneOfTwoIs(first_type, second_type, essence_type::Base) == true)
	{
		return 0;
	}

	ConsoleOutput::getInstance()->printInfo( "Не известная кардинальность");
	return -70;
}

void DataController::insertKeyInCharacteristic(EREssenceData * e, QString key)
{
	//ConsoleOutput::getInstance()->printStartActionInfo("производится вставка ключа: " + key + " в " + e->getId());
	e->addKey(key);
	//ConsoleOutput::getInstance()->printInfo("Ключ: " + key + " успешно добавлен в " + e->getId() + " Процедура добавления ключа в характеристику выполнена");
}

void DataController::insertKeyInDesignation(EREssenceData * e, QString key)
{

	//ConsoleOutput::getInstance()->printStartActionInfo("производится вставка ключа: " + key + " в " + e->getId());
	e->addKey(key);
	QList<QString> adjList = relation_table.getAjasencyByName(e->getId());
	//ConsoleOutput::getInstance()->printInfoList(e->getId() + " смежен с: ", adjList);

	foreach (QString next, adjList)
	{
		EREssenceData * e = search(next);
		if(e == nullptr)
		{
			ConsoleOutput::getInstance()->printSystemError("__ERROR__: in void DataController::insertKeyInDesignation(EREssenceData * e, QString key) поиск существующей сущности завершился неудачей;");
			exit(10);
		}

		switch (e->getType())
		{
			case essence_type::Base:
			{
//				insertKeyInBase(e, e->getId() + "::" +key);
				e->addAtribute(e->getId() + "::" +key);
				break;
			}
			case essence_type::Association:
			{
				insertKeyInAssociation(e, e->getId() + "::" +key);
				break;
			}
			case essence_type::Designation:
			{
				ConsoleOutput::getInstance()->printSystemError("__ERROR__: in void DataController::insertKeyInDesignation(EREssenceData * e, QString key); Возникло обозначение обозначения;");
				exit(10);
			}
			case essence_type::Characteristic:
			{
				insertKeyInCharacteristic(e, e->getId() + "::" +key);
				break;
			}
			default:
				ConsoleOutput::getInstance()->printSystemError("__ERROR__: in void DataController::insertKeyInDesignation(EREssenceData * e, QString key); Неизвестный тип сущности");
				exit(11);
		}
	}

	//ConsoleOutput::getInstance()->printInfo("Ключ: " + key + " успешно добавлен в " + e->getId() + " Процедура добавления ключа в обозначение выполнена");

}

void DataController::insertKeyInBase(EREssenceData * e, QString key)
{
	//ConsoleOutput::getInstance()->printStartActionInfo("производится вставка ключа: " + key + " в " + e->getId());
	e->addKey(key);
	QList<QString> adjList = relation_table.getAjasencyByName(e->getId());
	//ConsoleOutput::getInstance()->printInfoList(e->getId() + " смежен с: " , adjList);

	foreach (QString next, adjList)
	{
		EREssenceData * e = search(next);
		if(e == nullptr)
		{
			ConsoleOutput::getInstance()->printSystemError( "__ERROR__: in void DataController::insertKeyInBase(EREssenceData * e, QString key) поиск существующей сущности завершился неудачей;");
			exit(10);
		}

		switch (e->getType())
		{
			case essence_type::Base:
			{
				ConsoleOutput::getInstance()->printSystemError("__ERROR__: in void DataController::insertKeyInBase(EREssenceData * e, QString key) обнаружено стержень - стердень соединение;");
				exit(11);
			}
			case essence_type::Association:
			{
				insertKeyInAssociation(e, e->getId() + "::" +key);
				break;
			}
			case essence_type::Designation:
			{
				//ConsoleOutput::getInstance()->printInfo("Передача ключей от стержневых сущностей к обозначениям не производится");
				break;
			}
			case essence_type::Characteristic:
			{
				insertKeyInCharacteristic(e, e->getId() + "::" +key);
				break;
			}
			default:
				ConsoleOutput::getInstance()->printSystemError("__ERROR__: in void void DataController::insertKeyInBase(EREssenceData * e, QString key); Неизвестный тип сущности");
				exit(11);
		}
	}
	//ConsoleOutput::getInstance()->printInfo("Ключ: " + key + " успешно добавлен в " + e->getId() + " Процедура добавления ключа в стержневую сущность выполнена");
}

void DataController::insertKeyInAssociation(EREssenceData * e, QString key)
{
	//ConsoleOutput::getInstance()->printStartActionInfo("производится вставка ключа: " + key + " в " + e->getId());

	e->addKey(key);
	QList<QString> adjList = relation_table.getAjasencyByName(e->getId());
	//ConsoleOutput::getInstance()->printInfoList(e->getId() + " смежен с: ", adjList);

	foreach (QString next, adjList)
	{
		EREssenceData * e = search(next);
		if(e == nullptr)
		{
			ConsoleOutput::getInstance()->printSystemError("__ERROR__: in void DataController::insertKeyInAssociation(EREssenceData * e, QString key) поиск существующей сущности завершился неудачей;");
			exit(10);
		}

		switch (e->getType())
		{
			case essence_type::Base:
			{
				//ConsoleOutput::getInstance()->printInfo("Передача ключей от ассоциаций к стержневым сущностям не производится");
				break;
			}
			case essence_type::Association:
			{
				ConsoleOutput::getInstance()->printSystemError("__ERROR__: in void DataController::insertKeyInAssociation(EREssenceData * e, QString key) обнаружено соединение ассоциация - ассоциация;");
				exit(11);
			}
			case essence_type::Designation:
			{
				//ConsoleOutput::getInstance()->printInfo("Передача ключей от ассаоциативных сущностей к обозначениям не производится");
				break;
			}
			case essence_type::Characteristic:
			{
				insertKeyInCharacteristic(e, e->getId() + "::" +key);
				break;
			}
			default:
				ConsoleOutput::getInstance()->printSystemError("__ERROR__: in void DataController::insertKeyInAssociation(EREssenceData * e, QString key); Неизвестный тип сущности");
				exit(11);
		}
	}

	//ConsoleOutput::getInstance()->printInfo("Ключ: " + key + " успешно добавлен в " + e->getId() + " Процедура добавления ключа в ассоциацию выполнена");
}

int DataController::createRelationBetweenBaseAndDesignation(EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two)
{
	EREssenceData * base;
	EREssenceData * des;
	if(e1->getType() == essence_type::Base)
	{
		base = e1;
		des = e2;
	}
	else
	{
		base = e2;
		des = e1;
	}

	foreach (QString key, des->getKeys())
	{
		addAttribute(base->getId(), base->getId() + "::" + key);
	}

	relation_table.addRelation(e1->getId(), e2->getId(), cord_one, cord_two);
	return 0;
}

int DataController::createRelationBetweenBaseAndCharacteristic(EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two)
{
	EREssenceData * base;
	EREssenceData * ch;
	if(e1->getType() == essence_type::Base)
	{
		base = e1;
		ch = e2;
	}
	else
	{
		base = e2;
		ch = e1;
	}

	foreach (QString key, base->getKeys())
	{
		addKey(ch->getId(), ch->getId() + "::" + key);
	}

	relation_table.addRelation(e1->getId(), e2->getId(), cord_one, cord_two);
	return 0;
}

int DataController::createRelationBetweeAssociationAndDesignation(EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two)
{
	EREssenceData * as;
	EREssenceData * des;
	if(e1->getType() == essence_type::Association)
	{
		as = e1;
		des = e2;
	}
	else
	{
		as = e2;
		des = e1;
	}

	foreach (QString key, des->getKeys())
	{
		addKey(as->getId(), as->getId() + "::" + key);
	}

	relation_table.addRelation(e1->getId(), e2->getId(), cord_one, cord_two);
	return 0;
}

int DataController::createRelationBetweenAssociationAndCharacteristic(EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two)
{
	EREssenceData * as;
	EREssenceData * ch;
	if(e1->getType() == essence_type::Association)
	{
		as = e1;
		ch = e2;
	}
	else
	{
		as = e2;
		ch = e1;
	}

	foreach (QString key, as->getKeys())
	{
		addKey(ch->getId(), ch->getId() + "::" + key);
	}

	relation_table.addRelation(e1->getId(), e2->getId(), cord_one, cord_two);
	return 0;
}

int DataController::createRelationBetweenBaseAndBaseWithNewRelation(EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two)
{
	QList<QString> keys;
	QString name;
	name.append(e1->getId().at(0));
	name.append("rel");
	name.append(e2->getId().at(0));
	QList<QString> attrs; attrs << name + "_date";

	this->createEssence(name, essence_type::Association, keys, attrs);
	foreach (QString key, e1->getKeys())
	{
		addKey(name,name+"::" + key);
	}

	foreach (QString key, e2->getKeys())
	{
		addKey(name,name+"::" + key);
	}

	relation_table.addRelation(e1->getId(),name, cord_one, cordinalyty::hiddenCord);
	relation_table.addRelation(e2->getId(),name, cord_two, cordinalyty::hiddenCord);
	return 0;
}

int DataController::createRelationBetweenDesignationAndCharacteristic(EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two)
{
	EREssenceData * des;
	EREssenceData * ch;
	if(e1->getType() == essence_type::Designation)
	{
		des = e1;
		ch = e2;
	}
	else
	{
		des = e2;
		ch = e1;
	}

//	qDebug() << "Insert in:" << ch->getId();
	foreach (QString key, des->getKeys())
	{
		addKey(ch->getId(), ch->getId() + "::" + key);
	}

	relation_table.addRelation(e1->getId(), e2->getId(), cord_one, cord_two);
	return 0;
}

int DataController::removeRelationBetweenEssences(EREssenceData *e1, EREssenceData *e2)
{

	if((e1->getType() == essence_type::Designation && e2->getType() == essence_type::Base) ||
			(e1->getType() == essence_type::Base && e2->getType() == essence_type::Designation))
	{
//		qDebug() <<"между стержневой и обозначающей сущностями:" << e1->getId() << " " << e2->getId();
		if(removeRelationBetweenBaseAndDesignation(e1, e2) == 0)
		{
			return 0;
		}
		else
		{
			return -10;
		}
	}

//	qDebug() <<"между :" << e1->getId() << " и " << e2->getId();

	foreach (QString key, e1->getKeys())
	{
		removeKeyFrom(e2->getId(), e2->getId()+"::"+key);
	}

	foreach (QString key, e2->getKeys())
	{
		removeKeyFrom(e1->getId(), e1->getId()+"::"+key);
	}

	if(relation_table.deleteRelation(e1->getId(), e2->getId()) == true)
	{
		ConsoleOutput::getInstance()->printInfo("Связь удалена успешно\n ===================");
		return 0;
	}
	else
	{
		ConsoleOutput::getInstance()->printUserError("Ошибка при удалении связи\n ===================");
		return -10;
	}

	return 0;


}

int DataController::removeRelationBetweenBaseAndDesignation(EREssenceData *e1, EREssenceData *e2)
{
	EREssenceData * des;
	EREssenceData * base;

	if(e1->getType() == essence_type::Base)
	{
		base = e1;
		des = e2;
	}
	else
	{
		base = e2;
		des = e1;
	}

	foreach (QString key, des->getKeys())
	{
		removeAttribute(base->getId(), base->getId()+"::"+key);
	}

	if(relation_table.deleteRelation(base->getId(), des->getId()) == true)
	{
		ConsoleOutput::getInstance()->printInfo("Связь удалена успешно");
		return 0;
	}
	else
	{
		ConsoleOutput::getInstance()->printUserError("Ошибка при удалении связи");
		return -10;
	}

	return -20;
}



int DataController::removeKeyFrom(QString id, QString key)
{

	EREssenceData * e = search(id);
	if(e == nullptr)
	{
		//ConsoleOutput::getInstance()->printInfo("Попытка удаления ключа из не существующей сущности");
		//ConsoleOutput::getInstance()->printInfo("Удаление ключа прервано.");
		return 10;
	}

	if(e->getKeys().contains(key) != true)
	{
		//ConsoleOutput::getInstance()->printInfo("В сущности: " + e->getId() + "нет ключа: +key");
		//ConsoleOutput::getInstance()->printInfo("Удаление ключа прервано.");
		return 11;
	}

	foreach (EREssenceData * e, list_essences)
	{
		QList<QString> & keys = e->getKeys();
		foreach (QString k, keys)
		{
//            QString stripped_k = Support::getStrippedProperty(k);
//            QString stripped_key = Support::getStrippedProperty(key);
            if(key == k)
			{
                ConsoleOutput::getInstance()->printSystemMassage("Удаляю " + k);
                e->removeKey(k);
			}
		}
	}

	if(e->getType() == essence_type::Designation)
	{
		QList<QString> adj = relation_table.getAjasencyByName(e->getId());
		foreach (QString name, adj)
		{
			EREssenceData * adjEssence = search(name);
			if(adjEssence != nullptr)
			{
				if(adjEssence->getType() == essence_type::Base)
				{
					adjEssence->removeAttributeWithSubStr(key);
					//ConsoleOutput::getInstance()->printInfo("Удаление атрибута " + key + " из " + adjEssence->getId() + " выполнено.");
					return 0;
				}
			}
			else
			{
				ConsoleOutput::getInstance()->printSystemError("__ERROR__: in int DataController::removeKeyFrom(QString id, QString key). Bad designation pointer");
				return 10;
			}
		}
	}


	ConsoleOutput::getInstance()->printInfo("Удаление ключа " + key + " выполнено.");
	return 0;
}



EREssenceData *DataController::search(QString id)
{
	foreach (EREssenceData *e, list_essences)
	{
		if(e->getId() == id)
		{
			return e;
		}
	}

	return nullptr;
}

bool DataController::saveState(QString path)
{

	if(path == "")
	{
		path = "save.json";
	}

	QFile saveFile(path+".json");

	if (!saveFile.open(QIODevice::WriteOnly))
	{
	   ConsoleOutput::getInstance()->printSystemError("Couldn't open save file.");
	   return false;
	}


	QJsonObject json;
	write(json);
	QJsonDocument saveDoc(json);
	saveFile.write(saveDoc.toJson());
	saveFile.close();

    ConsoleOutput::getInstance()->printSystemMassage("Файл сохранён");
	return true;
}

bool DataController::loadState(QString path)
{
	QFile openFile(path);
	if (!openFile.open(QIODevice::ReadOnly)) {
	   ConsoleOutput::getInstance()->printSystemError("Couldn't open file.");
	   return false;
	}

	QByteArray saveData = openFile.readAll();

	QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
	read(loadDoc.object());
	return true;
}

void DataController::clear()
{
	list_essences.clear();
    relation_table.clear();
}

bool DataController::saveIsPermit() const
{
    for(EREssenceData * essence: list_essences)
    {
        if(getAjesencyFor(essence->getId()).length() == 0)
        {
            ConsoleOutput::getInstance()->printUserError("Обнаружена висячая сущность: " + essence->getId());
            return false;
        }
    }
    return true;

}

void DataController::read(const QJsonObject &json)
{

	QJsonArray essences = json["EssencesArray"].toArray();
	QJsonObject relations = json["RelationsTable"].toObject();

	list_essences.clear();

	for(int i = 0; i < essences.size(); i++)
	{
		EREssenceData * e = new EREssenceData("load", 0);
		e->read(essences.at(i).toObject());
		list_essences.append(e);

	}

	relation_table.read(relations);


}

void DataController::write(QJsonObject &json) const
{
	QJsonArray essences;
	foreach (EREssenceData * e, list_essences)
	{
		QJsonObject obj;
		e->write(obj);
		essences.append(obj);
	}

	json["EssencesArray"] = essences;


	QJsonObject relations;
	relation_table.write(relations);
	json["RelationsTable"] = relations;

}


DataController *DataController::getInstance()
{
	if(self == nullptr)
	{
		self = new DataController;
		return self;
	}

	return self;
}

QList<std::tuple<QString, QString, int, int> > DataController::getRelationTable()
{
	return relation_table.getCordinality_table();
}


int DataController::createEssence(QString id, int type, QList<QString> keys, QList<QString> attributes)
{

	if(keys.contains(id+"_id") == true)
	{
		//ConsoleOutput::getInstance()->printUserError("Создание ключа вида: <Имя сущности>_id запрещено. Ключ автоматически добавится системмой.");
		return -10;
	}

	keys.append(id+"_id");
	ConsoleOutput::getInstance()->printStartActionInfo("Создание сущности: " + id);
	ConsoleOutput::getInstance()->printInfo("-------------------------------------");
	if(checkBeforeCreationEssence(id, type, keys, attributes) == 0)
	{
		switch (type) {
			case essence_type::Base:
			{
				EREssenceData * eBase = new EREssenceData(id, type);
				eBase->setKeys(keys);
				eBase->setAttributes(attributes);
				list_essences.append(eBase);
				ConsoleOutput::getInstance()->printInfo("Сущность " + id + " успешно создана");
				ConsoleOutput::getInstance()->printInfo("-------------------------------------\n");
				return 0;
			}

			case essence_type::Characteristic:
			{
				EREssenceData * eChar = new EREssenceData(id, type);
				eChar->setKeys(keys);
				eChar->setAttributes(attributes);
				list_essences.append(eChar);
				ConsoleOutput::getInstance()->printInfo("Сущность " + id + " успешно создана");
				qDebug() << "-------------------------------------\n";
				return 0;
			}

			case essence_type::Designation:
			{
				EREssenceData * eDes = new EREssenceData(id, type);
				eDes->setKeys(keys);
				eDes->setAttributes(attributes);
				list_essences.append(eDes);
				ConsoleOutput::getInstance()->printInfo("Сущность " + id + " успешно создана");
				ConsoleOutput::getInstance()->printInfo("-------------------------------------\n");
				return 0;
			}

			case essence_type::Association:
			{
				EREssenceData * eAss = new EREssenceData(id, type);
				eAss->setKeys(keys);
				eAss->setAttributes(attributes);
				list_essences.append(eAss);
				ConsoleOutput::getInstance()->printInfo("Сущность " + id + " успешно создана");
				ConsoleOutput::getInstance()->printInfo("-------------------------------------\n");
				return 0;
			}
			default:
				ConsoleOutput::getInstance()->printSystemError("__ERROR__: in int DataController::createEssence(QString id, int type, QList<QString> keys, QList<QString> attributes) def brunch");
				break;
		}
	}

	ConsoleOutput::getInstance()->printUserError("Сущность " + id + " не создана. Проверьте ошибки!");
	ConsoleOutput::getInstance()->printInfo("-------------------------------------\n");
	return -1;
}

int DataController::removeEssence(QString id)
{

	ConsoleOutput::getInstance()->printStartActionInfo("Удаление сущности " + id);
	EREssenceData * e = search(id);

	if(e == nullptr)
	{
		ConsoleOutput::getInstance()->printInfo("Удаляемая сущность не сущенствует");
		return -10;
	}

	QList<QString> adj = relation_table.getAjasencyByName(id);

	//ConsoleOutput::getInstance()->printStartActionInfo("Производится удаление связей со смежными сущностями");
	foreach (QString name, adj)
	{
		removeRelation(id, name);
	}
	//ConsoleOutput::getInstance()->printInfo("Удаление смежных связей завершено");

	list_essences.removeOne(e);

	ConsoleOutput::getInstance()->printInfo("Сущность удалена успешно");

	return 0;
}

int DataController::createRelation(QString id_first, QString id_second, int cord_one, int cord_two)
{
	if(checkBeforeCreationRelation(id_first, id_second, cord_one, cord_two) == 0)
	{
		EREssenceData * f = search(id_first);
		EREssenceData * s = search(id_second);

		if(f != nullptr && s != nullptr)
		{

			if(checkCordinality(f->getId(), s->getId(), f->getType(), s->getType(), cord_one, cord_two) == 0)
			{
				if(f->getType() == essence_type::Base && s->getType() == essence_type::Base)
				{
					ConsoleOutput::getInstance()->printStartActionInfo("Создание связи между стержневой и стержневой сущностями:");
					QString name = id_first.at(0);
					name.append("rel");
					name.append(id_second.at(0));
					ConsoleOutput::getInstance()->printStartActionInfo("Для соединения будет создана новая ассоциация с именем: " + name);
					createRelationBetweenBaseAndBaseWithNewRelation(f,s,cord_one, cord_two);
					return 0;
				}

				if((f->getType() == essence_type::Base && s->getType() == essence_type::Designation) ||
				   (s->getType() == essence_type::Base && f->getType() == essence_type::Designation))
				{
					ConsoleOutput::getInstance()->printStartActionInfo("Создание связи между стержневой и обозначающей сущностями:");
					createRelationBetweenBaseAndDesignation(f,s,cord_one, cord_two);
					return 0;
				}

				if((f->getType() == essence_type::Base && s->getType() == essence_type::Characteristic) ||
				   (s->getType() == essence_type::Base && f->getType() == essence_type::Characteristic))
				{
					ConsoleOutput::getInstance()->printStartActionInfo("Создание связи между стержневой и характерисической сущностями:");
					createRelationBetweenBaseAndCharacteristic(f,s,cord_one, cord_two);
					return 0;
				}

				if((f->getType() == essence_type::Association && s->getType() == essence_type::Designation) ||
					(s->getType() == essence_type::Association && f->getType() == essence_type::Designation))
				{
					ConsoleOutput::getInstance()->printStartActionInfo("Создание связи между ассоциативной и обозначающей сущностями:");
					createRelationBetweeAssociationAndDesignation(f,s,cord_one, cord_two);
					return 0;
				}

				if((f->getType() == essence_type::Association && s->getType() == essence_type::Characteristic) ||
				   (s->getType() == essence_type::Association && f->getType() == essence_type::Characteristic))
				{
					ConsoleOutput::getInstance()->printStartActionInfo("Создание связи между ассоциативной и характерисической сущностями:");
					createRelationBetweenAssociationAndCharacteristic(f,s,cord_one, cord_two);
					return 0;
				}

				if((f->getType() == essence_type::Designation && s->getType() == essence_type::Characteristic) ||
				   (s->getType() == essence_type::Designation && f->getType() == essence_type::Characteristic))
				{
					ConsoleOutput::getInstance()->printStartActionInfo("Создание связи между обозначающей и характерисической сущностями:");
					createRelationBetweenDesignationAndCharacteristic(f,s,cord_one, cord_two);
					return 0;
				}

				if((f->getType() == essence_type::Association && s->getType() == essence_type::Base) ||
				   (s->getType() == essence_type::Association && f->getType() == essence_type::Base))
				{
					ConsoleOutput::getInstance()->printUserError("Создание связи между ассоциацией и стержневой сущностью производится черех функцию включения в ассоциацию");
//					createRelationBetweenDesignationAndCharacteristic(f,s,cord_one, cord_two);
					return 0;
				}
			}
			ConsoleOutput::getInstance()->printUserError("Попытка cоздания неизвестного типа соединения. Проверьте ошибки.");
		}
	}

	ConsoleOutput::getInstance()->printUserError("Cоздание связи между " + id_first + " и " + id_second + " прервано. Проверьте ошибки\n");
	return -1;

}

int DataController::removeRelation(QString id_first, QString id_second)
{
	EREssenceData * e1 = search(id_first);
	EREssenceData * e2 = search(id_second);

	ConsoleOutput::getInstance()->printStartActionInfo("Удаление связи между: " + id_first + " , " + id_second + "\n ===================");
	if(e1 == nullptr || e2 == nullptr)
	{
		//ConsoleOutput::getInstance()->printInfo("Не удалось найти сущность(ти) \n ===================");
		return -10;
	}

	if(relation_table.isExist(id_first, id_second) == true)
	{
		if(removeRelationBetweenEssences(e1,e2) == 0)
		{
			return 0;
		}
	}
	else
	{
		ConsoleOutput::getInstance()->printUserError("Удаляемая связь не обнаружена. Проверьте ошибки.\n ===================");
		return -11;
	}

	return -20;
}

int DataController::removeAttribute(QString id, QString attr_name)
{
	EREssenceData * e = search(id);
	if(e != nullptr)
	{
		if(e->getAttributes().contains(attr_name) == false)
		{
			ConsoleOutput::getInstance()->printInfo("Атрибут: " + attr_name + " не принадлежит сущности (возможно он внешний) " + id + " в качестве атрибута");
			return 10;
		}
		else if(e->getAttributes().length() == 1)
		{
			ConsoleOutput::getInstance()->printUserError("Сущность должна содержать как минимум один атрибут (Попытка удалить единственный атрибут)");
			return 11;
		}
		else
		{
			e->getAttributes().removeOne(attr_name);
			ConsoleOutput::getInstance()->printInfo("Атрибут: " + attr_name + " удалён из " + id);
			return 0;
		}
	}
	else
	{
		ConsoleOutput::getInstance()->printInfo("Сущность: " + id + "не существует");
		return 12;
	}

	return 13;
}

int DataController::addAttribute(QString id, QString attr_name)
{
	EREssenceData * e = search(id);
	if(e != nullptr)
	{
		QList<QString> l1,l2;
		l2 << attr_name;
		if(keyOrAttributeIsExist(l1, l2) == true)
		{
			ConsoleOutput::getInstance()->printInfo("Имя атрибута должно быть уникально");
			return 10;
		}
		else
		{
			e->addAtribute(attr_name);
			ConsoleOutput::getInstance()->printInfo("Атрибут: " + attr_name + " добавлен к: " + id);
			return 0;
		}
	}
	else
	{
		ConsoleOutput::getInstance()->printInfo("Сущность: " + id +  "не существует");
		return 20;
	}

	return 30;
}

int DataController::removeKey(QString id, QString key_name)
{

	//ConsoleOutput::getInstance()->printStartActionInfo("\nУдаление ключа: " + key_name + " из " + id);
	if(key_name.lastIndexOf("::") != -1 || key_name.lastIndexOf("_") != -1)
	{
		ConsoleOutput::getInstance()->printSystemError("Попытка напрямую удалить системный ключ. Удаление системных ключей производится через операции редактирования диаграмы");
		return 10;
	}

    removeKeyFrom(id, key_name);

    QList<QString> adj_list = DataController::getInstance()->getAjesencyFor(id);
    for(QString & name: adj_list)
    {
        removeKeyFrom(name, name+ "::" +key_name);
    }


    return 0;
}

int DataController::addKey(QString id, QString key_name)
{
	if(essenceIsExist(id) == false)
	{
		ConsoleOutput::getInstance()->printUserError("Сущность: " + id + " не существует. Ключ не добавлен");
		return 10;
	}

	QList<QString> l1,l2;
	l1.append(key_name);
	if(keyOrAttributeIsExist(l1, l2) == true)
	{
		ConsoleOutput::getInstance()->printUserError("Ключ должен быть уникальным. Ключ не добавлен. Проверьте ошибки");
		return 11;
	}



	EREssenceData * e = search(id);
	if(e == nullptr)
	{
		ConsoleOutput::getInstance()->printSystemError("__ERROR__: in int DataController::addKey(QString id, QString key_name); e == nullptr;");
		return 12;
	}


	QList<QString> list;
	list << key_name;
	if(keyOrAttributeIsNameOfEssence(id, list) == true)
	{
		ConsoleOutput::getInstance()->printUserError("Проверьте ошибки");
		return 13;
	}
	switch (e->getType())
	{
		case essence_type::Characteristic:
		{
			//ConsoleOutput::getInstance()->printStartActionInfo("\nПроизводится вставка ключа в характеристику \n======================");
			insertKeyInCharacteristic(e, key_name);
			ConsoleOutput::getInstance()->printInfo("Ключ: " + key_name + " добавлен к " + e->getId());
			//ConsoleOutput::getInstance()->printInfo("\nВставка ключа в характеристику завершена \n======================");
			return 0;
		}

		case essence_type::Designation:
		{
			//ConsoleOutput::getInstance()->printStartActionInfo("\nПроизводится вставка ключа в обозначение \n======================");
			insertKeyInDesignation(e, key_name);
			ConsoleOutput::getInstance()->printInfo("Ключ: " + key_name + " добавлен к " + e->getId());
			//ConsoleOutput::getInstance()->printInfo("\nВставка ключа в обозначение завершена\n======================");
			return 0;
		}

		case essence_type::Base:
		{
			//ConsoleOutput::getInstance()->printStartActionInfo("\nПроизводится вставка ключа в стержневую сущность\n======================");
			insertKeyInBase(e, key_name);
			ConsoleOutput::getInstance()->printInfo("Ключ: " + key_name + " добавлен к " + e->getId());
			//ConsoleOutput::getInstance()->printInfo("\nВставка ключа в стержневую сущность завершена\n======================");
			return 0;
		}

		case essence_type::Association:
		{
			//ConsoleOutput::getInstance()->printStartActionInfo("\nПроизводится вставка ключа в ассоциацию\n======================");
			insertKeyInAssociation(e, key_name);
			ConsoleOutput::getInstance()->printInfo("Ключ: " + key_name + " добавлен к " + e->getId());
			//ConsoleOutput::getInstance()->printInfo("\nВставка ключа в ассоциацию завершена\n======================");
			return 0;
		}
	}

	ConsoleOutput::getInstance()->printSystemError("__ERROR__: in int DataController::addKey(QString id, QString key_name); Undifine behavior;");
	return 100;
}

int DataController::joinBaseToExistAssociation(QString essence, QString association, int cord)
{

	ConsoleOutput::getInstance()->printStartActionInfo("\nПроизводится включение сущности: " + essence + " в состав ассоциации: " + association);
	EREssenceData * e = search(essence);
	EREssenceData * a = search(association);

	if(e == nullptr || a == nullptr)
	{
		ConsoleOutput::getInstance()->printSystemError("__ERROR__:  in DataController::joinBaseToExistAssociation: сущностей: " + essence + " и(или) " + association + "не существует");
		return 10;
	}

	if(e->getType() != essence_type::Base)
	{
		ConsoleOutput::getInstance()->printSystemError("__ERROR__:  in DataController::joinBaseToExistAssociation: сущность: " + essence + " не является стержневой");
		return 20;
	}

	if(a->getType() != essence_type::Association)
	{
		ConsoleOutput::getInstance()->printSystemError("__ERROR__:  in DataController::joinBaseToExistAssociation: сущность: " + association + " не является ассаоциативной");
		return 30;
	}

	QList<QString> adj = relation_table.getAjasencyByName(association);
	if(adj.contains(essence) == true)
	{
		ConsoleOutput::getInstance()->printUserError("Сущность: " + essence + "уже входит в состав: " + association);
		return 40;
	}

	foreach (QString key, e->getKeys())
	{
		addKey(a->getId(), association+"::"+key);
	}

	relation_table.addRelation(essence, association, cord, cordinalyty::hiddenCord);
	ConsoleOutput::getInstance()->printInfo("Сущность: " + essence + "включена в связь: " + association + "\n");
	return 0;
}

int DataController::setCordinality(QString id_a, QString id_b, int cord_A, int cord_B)
{
	ConsoleOutput::getInstance()->printStartActionInfo("Производится установка кардинальностей: " +
													   Support::cardinalityToString(cord_A) + " "+Support::cardinalityToString(cord_A) + " от " + id_a + " к " + id_b);

	if(essenceIsExist(id_a) == false || essenceIsExist(id_b) == false)
	{
		ConsoleOutput::getInstance()->printInfo("Сущностей(ти) с таким именем не обнаружено");
		return -20;
	}
	QList<QString> adj = relation_table.getAjasencyByName(id_a);
	if(adj.contains(id_b) == false)
	{
		ConsoleOutput::getInstance()->printUserError("Сущности не смежны. Проверьте ошибки");
		return -10;
	}

	if(checkCordinality(id_a, id_b,search(id_a)->getType(), search(id_b)->getType(),cord_A, cord_B) == 0)
	{
		relation_table.setCord(id_a, id_b, cord_A, cord_B);
		ConsoleOutput::getInstance()->printInfo("Кардинальности установлены");
		return 0;
	}

	return -10;

}

int DataController::renameEssence(QString id_to_rename, QString new_id)
{
	ConsoleOutput::getInstance()->printStartActionInfo("Переименование сущности " + id_to_rename + " в " + new_id);

	if(essenceIsExist(id_to_rename) == false)
	{
		ConsoleOutput::getInstance()->printInfo("Сущность " + id_to_rename + " не существует");
		return -10;
	}

	if(essenceIsExist(new_id) == true)
	{
		ConsoleOutput::getInstance()->printInfo("Новое имя перекрывает старое - уже существующее");
		return -20;
	}


	EREssenceData * esse = search(id_to_rename);

	esse->setId(new_id);
	ConsoleOutput::getInstance()->printInfo("Сущность переименована");

	foreach (EREssenceData * e, list_essences)
	{
		QList<QString>  & keys = e->getKeys();

		for (QList<QString>::iterator i = keys.begin(); i != keys.end(); ++i)
		{
			(*i).replace(id_to_rename, new_id);
		}

		QList<QString>  & attrs = e->getAttributes();

		for (QList<QString>::iterator i = attrs.begin(); i != attrs.end(); ++i)
		{
			(*i).replace(id_to_rename, new_id);
		}
	}
	ConsoleOutput::getInstance()->printInfo("Ключи и атрибуты переименованы");



	relation_table.renameEssence(id_to_rename, new_id);
	ConsoleOutput::getInstance()->printInfo("Связи переименованы");

	return 0;
}

void DataController::printAllEssence()
{
	qDebug() << "\nСущности диаграммы:";
	foreach (EREssenceData * d, list_essences)
	{
		d->print();
	}
	qDebug() <<"\n";
//	relation_table.print();
}

void DataController::printEssenceByID(QString id)
{
	qDebug() << "\nСущность: " << id;
	EREssenceData * e = this->search(id);
	if(e != nullptr)
	{
		e->print();
	}
	qDebug() <<"\n";
}

void DataController::printRelations()
{
	qDebug()<<"\nСвязи диаграмы: ";
	relation_table.print();
	qDebug() <<"\n";
}

std::tuple<QString, int, QString, int> DataController::getConnectionAttributesFor(QString id_first, QString id_second)
{
	EREssenceData * f = search(id_first);
	EREssenceData * s = search(id_second);

	if(f == nullptr || s == nullptr)
	{
		ConsoleOutput::getInstance()->printSystemError("__ERRER__: in std::pair<QString, QString> DataController::getConnectionAttributesFor(QString id_first, QString id_second) nullptr exeption");
		return std::make_tuple("__ERROR__",-1, "__ERROR__", -1);
	}

	//соеженены по ключам
	int i = 1;
	int j = 1;
	foreach (QString f_key, f->getKeysConst())
	{
		foreach (QString s_key, s->getKeysConst())
		{
			QString stripped_f = Support::getStrippedProperty(f_key);
			QString stripped_s = Support::getStrippedProperty(s_key);

			if(stripped_f == stripped_s)
			{
				return std::make_tuple(f_key, i, s_key, j);
			}
			j++;
		}
		i++;
	}

	i = 0;
	j = 1;
	//соеденины по атрибутам
	foreach (QString f_key, f->getKeysConst())
	{
		foreach (QString s_attr, s->getAttrsConst())
		{
			QString stripped_f = Support::getStrippedProperty(f_key);
			QString stripped_s = Support::getStrippedProperty(s_attr);

			if(stripped_f == stripped_s)
			{
				if(i == 0) i++;
				if(j == 0) j++;
				return std::make_tuple(f_key, i, s_attr, j + s->getKeysConst().length());
			}
			j++;
		}
		i++;
	}

	i = 1;
	j = 0;
	foreach (QString f_attr, f->getAttrsConst())
	{
		foreach (QString s_key, s->getKeysConst())
		{
			QString stripped_f = Support::getStrippedProperty(f_attr);
			QString stripped_s = Support::getStrippedProperty(s_key);

			if(stripped_f == stripped_s)
			{

//				qDebug() << "This one";
//				qDebug() << f_attr;
//				qDebug() << s_key;
//				qDebug() << s->getKeysConst().indexOf(s_key);
				if(i == 0) {i++;}
				if(j == 0) {j++;}
				return std::make_tuple(f_attr, i + f->getKeysConst().length(), s_key, s->getKeysConst().indexOf(s_key) + 1);
			}
			j++;
		}
		i++;
	}

	ConsoleOutput::getInstance()->printSystemError("Сущности " + id_first + " и " + id_second + "не имеют связи");
	return std::make_tuple("__ERROR__",-1, "__ERROR__", -1);
}

QList<QString> DataController::getEssences()
{
	QList<QString> essences;
	foreach (EREssenceData * e, list_essences)
	{
		essences.append(e->getId());
	}

	return essences;
}

QList<QString> DataController::getProperties(QString id, int mode)
{
	QList<QString> properties;
	EREssenceData * e = search(id);
	if(e != nullptr)
	{
		if(mode == 1)
		{
			if(e->getKeysConst().length() == 1)
			{
				properties.append(e->getKeys().at(0));
				return properties;
			}
			else
				return properties;
		}

		if(mode == 2)
		{
			return e->getAttrsConst();
		}

		if(mode == 3)
		{
			if(e->getKeysConst().length() > 1)
			{
				return e->getKeysConst();
			}
			else
				return properties;
		}

	}

	ConsoleOutput::getInstance()->printSystemError("__ERROR__: in QList<QString> DataController::getProperties(QString id, int mode) null pointer expection");
	return properties;




}

QList<QString> DataController::getAjesencyFor(QString id) const
{
	return relation_table.getAjasencyByName(id);
}

