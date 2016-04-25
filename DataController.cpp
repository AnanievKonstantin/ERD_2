#include "DataController.h"

DataController::DataController()
{

}

int DataController::checkBeforeCreationEssence(QString id, int type, QList<QString> keys, QList<QString> attributes)
{
	bool error = false;
	if(essenceIsExist(id) == true)
	{
		qDebug() << "Сущность с таким именем уже существует";
		error = true;
	}

	if(Support::enumCheck(type) == false)
	{
		qDebug() << "Указан не известный тип сущности";
		error = true;
	}

	if(keys.length() == 0)
	{
		qDebug() << "Сущность должна сожержать минимум один ключ";
		error = true;
	}

	if(attributes.length() == 0)
	{
		qDebug() << "Сущность должна сожержать минимум один атрибут";
		error = true;
	}

	if(keyISattr(keys, attributes) == true)
	{
		qDebug() << "Имена свойств сущности должны быть уникальны";
		error = true;
	}

	if(keyOrAttributeIsExist(keys, attributes) == true)
	{
		qDebug() << "Имена свойств сущности должны быть уникальны";
		error = true;
	}

	if(keyOrAttributeDublication(keys, attributes) == true)
	{
		qDebug() << "Имена свойств сущности должны быть уникальны";
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
		qDebug() << "Имена(Имя) связуемых сущностей не существуют";
		return 9;
	}
	if(relationIsExist(id_first, id_second) == true)
	{
		qDebug() << "Связь между " << id_first << " и "<< id_second <<" уже существует.";
		return 10;
	}

	if(id_first == id_second)
	{
		qDebug() << "Создание рекурсивных сущностей не разрешено";
		return 11;
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
				qDebug() << "Ошибка в именовании свойств сущности. Ключ:\"" << key <<"\" идентичен атрибуту\"" << attr <<"\"";
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
				qDebug() << "Ключ: " << key << " уже существует в списке свойств сущности: " << e->getId();
				exist = true;
			}
		}
		foreach (QString attr, attrs)
		{
			if(e->getAttributes().contains(attr) || e->getKeys().contains(attr))
			{
				qDebug() << "Атрибут: " << attr << " уже существует в списке свойств сущности: " << e->getId();
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
			qDebug() << "Ключ: " << key << " дублируется.";
			dublicatesIsExist = true;
		}
	}

	foreach (QString attr, attrs)
	{
		if(attrs.count(attr) > 1)
		{
			qDebug() << "Атрибут: " << attr << " дублируется.";
			dublicatesIsExist = true;
		}
	}

	return dublicatesIsExist;
}

void DataController::insertKeyInCharacteristic(EREssenceData * e, QString key)
{
	qDebug() << "производится вставка ключа: " << key << " в " << e->getId();
	e->addKey(key);
	qDebug() << "Ключ: " << key<< " успешно добавлен в " << e->getId() <<" Процедура добавления ключа в характеристику выполнена";
}

void DataController::insertKeyInDesignation(EREssenceData * e, QString key)
{

	qDebug() << "производится вставка ключа: " << key << " в " << e->getId();
	e->addKey(key);
	QList<QString> adjList = relation_table.getAjasencyByName(e->getId());
	qDebug() << e->getId() << "смежен с: "<< adjList;

	foreach (QString next, adjList)
	{
		EREssenceData * e = search(next);
		if(e == nullptr)
		{
			qDebug() << "__ERROR__: in void DataController::insertKeyInDesignation(EREssenceData * e, QString key) поиск существующей сущности завершился неудачей;";
			exit(10);
		}

		switch (e->getType())
		{
			case essence_type::Base:
			{
				insertKeyInBase(e, e->getId() + "::" +key);
				break;
			}
			case essence_type::Association:
			{
				insertKeyInAssociation(e, e->getId() + "::" +key);
				break;
			}
			case essence_type::Designation:
			{
				qDebug() << "__ERROR__: in void DataController::insertKeyInDesignation(EREssenceData * e, QString key); Возникло обозначение обозначения;";
				exit(10);
			}
			case essence_type::Characteristic:
			{
				insertKeyInCharacteristic(e, e->getId() + "::" +key);
				break;
			}
			default:
				qDebug() << "__ERROR__: in void DataController::insertKeyInDesignation(EREssenceData * e, QString key); Неизвестный тип сущности";
				exit(11);
		}
	}

	qDebug() << "Ключ: " << key<< " успешно добавлен в " << e->getId() <<" Процедура добавления ключа в обозначение выполнена";

}

void DataController::insertKeyInBase(EREssenceData * e, QString key)
{
	qDebug() << "производится вставка ключа: " << key << " в " << e->getId();
	e->addKey(key);
	QList<QString> adjList = relation_table.getAjasencyByName(e->getId());
	qDebug() << e->getId() << "смежен с: " << adjList;

	foreach (QString next, adjList)
	{
		EREssenceData * e = search(next);
		if(e == nullptr)
		{
			qDebug() << "__ERROR__: in void DataController::insertKeyInBase(EREssenceData * e, QString key) поиск существующей сущности завершился неудачей;";
			exit(10);
		}

		switch (e->getType())
		{
			case essence_type::Base:
			{
				qDebug() << "__ERROR__: in void DataController::insertKeyInBase(EREssenceData * e, QString key) обнаружено стержень - стердень соединение;";
				exit(11);
			}
			case essence_type::Association:
			{
				insertKeyInAssociation(e, e->getId() + "::" +key);
				break;
			}
			case essence_type::Designation:
			{
				qDebug() << "Передача ключей от стержневых сущностей к обозначениям не производится";
				break;
			}
			case essence_type::Characteristic:
			{
				insertKeyInCharacteristic(e, e->getId() + "::" +key);
				break;
			}
			default:
				qDebug() << "__ERROR__: in void void DataController::insertKeyInBase(EREssenceData * e, QString key); Неизвестный тип сущности";
				exit(11);
		}
	}
	qDebug() << "Ключ: " << key<< " успешно добавлен в " << e->getId() <<" Процедура добавления ключа в стержневую сущность выполнена";
}

void DataController::insertKeyInAssociation(EREssenceData * e, QString key)
{
	qDebug() << "производится вставка ключа: " << key << " в " << e->getId();

	e->addKey(key);
	QList<QString> adjList = relation_table.getAjasencyByName(e->getId());
	qDebug() << e->getId() << "смежен с: " << adjList;

	foreach (QString next, adjList)
	{
		EREssenceData * e = search(next);
		if(e == nullptr)
		{
			qDebug() << "__ERROR__: in void DataController::insertKeyInAssociation(EREssenceData * e, QString key) поиск существующей сущности завершился неудачей;";
			exit(10);
		}

		switch (e->getType())
		{
			case essence_type::Base:
			{
				qDebug() << "Передача ключей от ассоциаций к стержневым сущностям не производится";
				break;
			}
			case essence_type::Association:
			{
				qDebug() << "__ERROR__: in void DataController::insertKeyInAssociation(EREssenceData * e, QString key) обнаружено соединение ассоциация - ассоциация;";
				exit(11);
			}
			case essence_type::Designation:
			{
				qDebug() << "Передача ключей от ассаоциативных сущностей к обозначениям не производится";
				break;
			}
			case essence_type::Characteristic:
			{
				insertKeyInCharacteristic(e, e->getId() + "::" +key);
				break;
			}
			default:
				qDebug() << "__ERROR__: in void DataController::insertKeyInAssociation(EREssenceData * e, QString key); Неизвестный тип сущности";
				exit(11);
		}
	}

	qDebug() << "Ключ: " << key<< " успешно добавлен в " << e->getId() <<" Процедура добавления ключа в ассоциацию выполнена";
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
		addKey(as->getId(), des->getId() + "::" + key);
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
		addKey(ch->getId(), as->getId() + "::" + key);
	}

	relation_table.addRelation(e1->getId(), e2->getId(), cord_one, cord_two);
	return 0;
}

int DataController::createRelationBetweenBaseAndBaseWithNewRelation(EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two)
{
	QList<QString> keys; keys << e1->getId() + "<->" + e2->getId()+"_id";
	QList<QString> attrs; attrs << e1->getId() + "<->" + e2->getId()+"_date";

	this->createEssence(e1->getId() + "<->" + e2->getId(), essence_type::Association, keys, attrs);
	foreach (QString key, e1->getKeys())
	{
		addKey((e1->getId() + "<->" + e2->getId()), (e1->getId() + "<->" + e2->getId()) + "::" + key);
	}

	foreach (QString key, e2->getKeys())
	{
		addKey((e1->getId() + "<->" + e2->getId()), (e1->getId() + "<->" + e2->getId()) + "::" + key);
	}

	relation_table.addRelation(e1->getId(), e1->getId() + "<->" + e2->getId(), cord_one, cordinalyty::hiddenCord);
	relation_table.addRelation(e2->getId(), e1->getId() + "<->" + e2->getId(), cord_two, cordinalyty::hiddenCord);
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

int DataController::createEssence(QString id, int type, QList<QString> keys, QList<QString> attributes)
{

	qDebug() << "Создание сущности: " << id;
	qDebug() << "-------------------------------------";
	if(checkBeforeCreationEssence(id, type, keys, attributes) == 0)
	{
		switch (type) {
			case essence_type::Base:
			{
				EREssenceData * eBase = new EREssenceData(id, type);
				eBase->setKeys(keys);
				eBase->setAttributes(attributes);
				list_essences.append(eBase);
				qDebug() << "Сущность " << id << " успешно создана";
				qDebug() << "-------------------------------------\n";
				return 0;
			}

			case essence_type::Characteristic:
			{
				EREssenceData * eChar = new EREssenceData(id, type);
				eChar->setKeys(keys);
				eChar->setAttributes(attributes);
				list_essences.append(eChar);
				qDebug() << "Сущность " << id << " успешно создана";
				qDebug() << "-------------------------------------\n";
				return 0;
			}

			case essence_type::Designation:
			{
				EREssenceData * eDes = new EREssenceData(id, type);
				eDes->setKeys(keys);
				eDes->setAttributes(attributes);
				list_essences.append(eDes);
				qDebug() << "Сущность " << id << " успешно создана";
				qDebug() << "-------------------------------------\n";
				return 0;
			}

			case essence_type::Association:
			{
				EREssenceData * eAss = new EREssenceData(id, type);
				eAss->setKeys(keys);
				eAss->setAttributes(attributes);
				list_essences.append(eAss);
				qDebug() << "Сущность " << id << " успешно создана";
				qDebug() << "-------------------------------------\n";
				return 0;
			}
			default:
				break;
		}
	}

	qDebug() << "Сущность " << id << " не создана. Проверьте ошибки!";
	qDebug() << "-------------------------------------\n";
	return -1;
}

int DataController::createRelation(QString id_first, QString id_second, int cord_one, int cord_two)
{
	if(checkBeforeCreationRelation(id_first, id_second, cord_one, cord_two) == 0)
	{
		EREssenceData * f = search(id_first);
		EREssenceData * s = search(id_second);

		if(f != nullptr && s != nullptr)
		{
			if(f->getType() == essence_type::Base && s->getType() == essence_type::Base)
			{
				qDebug() << "Создание связи между стержневой и стержневой сущностями:";
				qDebug() << "Для соединения будет создана новая ассоциация с именем: " << id_first + "<->" +id_second;
				createRelationBetweenBaseAndBaseWithNewRelation(f,s,cord_one, cord_two);
				return 0;
			}

			if(f->getType() == essence_type::Base && s->getType() == essence_type::Designation ||
			   s->getType() == essence_type::Base && f->getType() == essence_type::Designation)
			{
				qDebug() << "Создание связи между стержневой и обозначающей сущностями:";
				createRelationBetweenBaseAndDesignation(f,s,cord_one, cord_two);
				return 0;
			}

			if(f->getType() == essence_type::Base && s->getType() == essence_type::Characteristic||
			   s->getType() == essence_type::Base && f->getType() == essence_type::Characteristic)
			{
				qDebug() << "Создание связи между стержневой и характерисической сущностями:";
				createRelationBetweenBaseAndCharacteristic(f,s,cord_one, cord_two);
				return 0;
			}

			if(f->getType() == essence_type::Association && s->getType() == essence_type::Designation ||
			   s->getType() == essence_type::Association && f->getType() == essence_type::Designation)
			{
				qDebug() << "Создание связи между ассоциативной и обозначающей сущностями:";
				createRelationBetweeAssociationAndDesignation(f,s,cord_one, cord_two);
				return 0;
			}

			if(f->getType() == essence_type::Association && s->getType() == essence_type::Characteristic||
			   s->getType() == essence_type::Association && f->getType() == essence_type::Characteristic)
			{
				qDebug() << "Создание связи между ассоциативной и характерисической сущностями:";
				createRelationBetweenAssociationAndCharacteristic(f,s,cord_one, cord_two);
				return 0;
			}

			qDebug() << "Попытка cоздания неизвестного типа соединения. Проверьте ошибки.";
		}
	}

	qDebug() << "Cоздание связи между " << id_first << " и " << id_second <<" прервано. Проверьте ошибки";
	return -1;

}

int DataController::removeAttribute(QString id, QString attr_name)
{
	EREssenceData * e = search(id);
	if(e != nullptr)
	{
		if(e->getAttributes().contains(attr_name) == false)
		{
			qDebug() << "Атрибут: " << attr_name << " не принадлежит сущности (возможно он внешний) " << id << " в качестве атрибута";
			return 10;
		}
		else if(e->getAttributes().length() == 1)
		{
			qDebug() << "Сущность должна содержать как минимум один атрибут (Попытка удалить единственный атрибут)";
			return 11;
		}
		else
		{
			e->getAttributes().removeOne(attr_name);
			qDebug() << "Атрибут: " << attr_name << " удалён из " << id;
			return 0;
		}
	}
	else
	{
		qDebug() << "Сущность: " << id << "не существует";
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
			qDebug() << "Имя атрибута должно быть уникально";
			return 10;
		}
		else
		{
			e->addAtribute(attr_name);
			qDebug() << "Атрибут: " << attr_name << " добавлен к: " << id;
		}
	}
	else
	{
		qDebug() << "Сущность: " << id << "не существует";
	}
}

int DataController::addKey(QString id, QString key_name)
{
	if(essenceIsExist(id) == false)
	{
		qDebug() << "Сущность: " << id <<" не существует";
		return 10;
	}

	QList<QString> l1,l2;
	l1.append(key_name);
	if(keyOrAttributeIsExist(l1, l2) == true)
	{
		qDebug() << "Ключ должен быть уникальным";
		return 11;
	}

	EREssenceData * e = search(id);
	if(e == nullptr)
	{
		qDebug() << "__ERROR__: in int DataController::addKey(QString id, QString key_name); e == nullptr;";
		return 12;
	}

	switch (e->getType())
	{
		case essence_type::Characteristic:
		{
			qDebug() << "\ninsertKeyInCharacteristic START ======================";
			insertKeyInCharacteristic(e, key_name);
			qDebug() << "insertKeyInCharacteristic END     ======================\n";
			return 0;
		}

		case essence_type::Designation:
		{
			qDebug() << "\ninsertKeyInDesignation START ======================";
			insertKeyInDesignation(e, key_name);
			qDebug() << "insertKeyInDesignation END     ======================\n";
			return 0;
		}

		case essence_type::Base:
		{
			qDebug() << "\ninsertKeyInBase START ======================";
			insertKeyInBase(e, key_name);
			qDebug() << "\ninsertKeyInBase END   ======================";
			return 0;
		}

		case essence_type::Association:
		{
			qDebug() << "\ninsertKeyInAssociation START ======================";
			insertKeyInAssociation(e, key_name);
			qDebug() << "\ninsertKeyInAssociation END   ======================";
			return 0;
		}
	}

	qDebug() << "__ERROR__: in int DataController::addKey(QString id, QString key_name); Undifine behavior;";
	return 100;
}

int DataController::joinBaseToExistAssociation(QString essence, QString association, int cord)
{

	qDebug() << "\nПроизводится включение сущности: " << essence <<" в состав ассоциации: " << association;
	EREssenceData * e = search(essence);
	EREssenceData * a = search(association);

	if(e == nullptr || a == nullptr)
	{
		qDebug() << "__RROR__:  in DataController::joinBaseToExistAssociation: сущностей: " << essence << " и(или) " << association << "не существует";
		return 10;
	}

	if(e->getType() != essence_type::Base)
	{
		qDebug() << "__RROR__:  in DataController::joinBaseToExistAssociation: сущность: " << essence << " не является стержневой";
		return 20;
	}

	if(a->getType() != essence_type::Association)
	{
		qDebug() << "__RROR__:  in DataController::joinBaseToExistAssociation: сущность: " << association << " не является ассаоциативной";
		return 30;
	}

	QList<QString> adj = relation_table.getAjasencyByName(association);
	if(adj.contains(essence) == true)
	{
		qDebug() << "Сущность: " << essence << "уже входит в состав: " << association;
		return 40;
	}

	foreach (QString key, e->getKeys())
	{
		addKey(a->getId(), association+"::"+key);
	}

	relation_table.addRelation(essence, association, cord, cordinalyty::hiddenCord);
	qDebug() << "Сущность: " << essence << "включена в связь: " << association << "\n";
	return 0;
}

void DataController::printAllEssence()
{
	qDebug() << "Сущности диаграммы:";
	foreach (EREssenceData * d, list_essences)
	{
		d->print();
	}

//	relation_table.print();
}

void DataController::printEssenceByID(QString id)
{
	qDebug() << "Сущность: " << id;
	EREssenceData * e = this->search(id);
	if(e != nullptr)
	{
		e->print();
	}
}

void DataController::printRelations()
{
	qDebug()<<"Связи диаграмы: ";
	relation_table.print();
}

void DataController::insertRelation(QString A, QString B)
{

}
