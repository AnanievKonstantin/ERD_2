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

void DataController::printAllEssence()
{
	qDebug() << "DataController output: ";
	foreach (EREssenceData * d, list_essences)
	{
		d->print();
	}

	relation_table.print();
}

void DataController::printEssenceByID(QString id)
{
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
