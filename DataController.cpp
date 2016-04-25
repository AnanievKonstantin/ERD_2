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
	QList<std::tuple<QString, QString, int, int> > ajasencyList = relation_table.getAllAjasencyFor(e->getId());

	qDebug() << e->getId() << "смежен с:";
	relation_table.printList(ajasencyList);
	QList<QString> adjList = relation_table.getAjasencyByName(e->getId());
	qDebug() << e->getId() << "смежен с:";
	qDebug() << adjList;

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

	qDebug() << "Ключ: " << key<< " успешно добавлен в " << e->getId() <<" Процедура добавления ключа в стержневую сущность выполнена";
}

void DataController::insertKeyInAssociation(EREssenceData * e, QString key)
{
	qDebug() << "производится вставка ключа: " << key << " в " << e->getId();



	qDebug() << "Ключ: " << key<< " успешно добавлен в " << e->getId() <<" Процедура добавления ключа в ассоциацию выполнена";
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
			relation_table.addRelation(f->getId(), s->getId(), cord_one, cord_two);
			return 0;
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
			insertKeyInCharacteristic(e, key_name);
			return 0;
		}

		case essence_type::Designation:
		{
			insertKeyInDesignation(e, key_name);
			return 0;
		}
	}

	qDebug() << "__ERROR__: in int DataController::addKey(QString id, QString key_name); Undifine behavior;";
	return 100;
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
