#include "EssenceGraphicsController.h"

EssenceGraphicsController * EssenceGraphicsController::self = nullptr;
QGraphicsScene * EssenceGraphicsController::scene = nullptr;

EssenceGraphicsController::EssenceGraphicsController(QObject *parent) : QObject(parent)
{

}

void EssenceGraphicsController::emitEditEssenceSignal(QString id)
{
	emit startEditEssence(id);
}

EssenceGraphicsController *EssenceGraphicsController::instance()
{
	if(self == nullptr)
	{
		self = new EssenceGraphicsController(0);
		return self;
	}
	else
	{
		return self;
	}
}

void EssenceGraphicsController::setScene(QGraphicsScene *_scene)
{
	if(_scene == nullptr)
	{
		qDebug() << "__ERROR__: in void EssenceGraphicsController::setScene(QGraphicsScene *scene) nullptr expection";
		return;
	}
	if(scene == nullptr)
	{
		scene = _scene;
	}
	else
	{
		return;
	}

}

void EssenceGraphicsController::syncWithDataContriller()
{

	//отчиска списков
	foreach (EREssence *e, essenceList)
	{
		scene->removeItem(e);
	}

	foreach (EREssenceProperty *e, propertyList)
	{
		scene->removeItem(e);
	}

	foreach (Arrow *e, arrowList)
	{
		scene->removeItem(e);
	}


	foreach (EREssence *e, essenceList)
	{
		delete e;
	}

	foreach (EREssenceProperty *e, propertyList)
	{
		delete e;
	}

	foreach (Arrow *e, arrowList)
	{
		delete e;
	}

	essenceList.clear();
	propertyList.clear();
	arrowList.clear();

	//заполнение списков
	foreach (QString s, DataController::getInstance()->getEssences())
	{
		EREssenceData * d = DataController::getInstance()->search(s);

		EREssence * switch_pointer;
		switch (d->getType())
		{
			case essence_type::Base:
			{
				switch_pointer  = new EREssenceBase(d);
				break;
			}
			case essence_type::Association:
			{
				switch_pointer  = new EREssenceRelation(d);
				break;
			}
			case essence_type::Designation:
			{
				switch_pointer  = new EREssenceDesignation(d);
				break;
			}
			case essence_type::Characteristic:
			{
				switch_pointer  = new EREssenceCharacteristic(d);
				break;
			}
			default:
				break;
			}
		essenceList.append(switch_pointer);
		QObject::connect(switch_pointer, SIGNAL(edit(QString)), this, SLOT(emitEditEssenceSignal(QString)));
	}

	foreach (QString s, DataController::getInstance()->getProperties(2))
	{
		EREssenceProperty * p = new EREssenceProperty(new EREssenceData(s, essence_type::Property_default));
		propertyList.append(p);
	}
	foreach (QString s, DataController::getInstance()->getProperties(1))
	{
		if(s.lastIndexOf("::") != -1)
		{
			EREssenceProperty * p = new EREssenceProperty(new EREssenceData(s, essence_type::Property_foreign_key));
			propertyList.append(p);
			continue;
		}
		EREssenceProperty * p = new EREssenceProperty(new EREssenceData(s, essence_type::Property_key));
		propertyList.append(p);
		continue;
	}
	//---------------

	//Создание и рисование стрелок. Заполнение списка стрелок
	QList<std::tuple<QString, QString, int, int> > table = DataController::getInstance()->getRelationTable();
	for(int i =0 ; i < table.length() ; i++)
	{
		std::tuple<QString, QString, int, int> row = table.at(i);
		EREssence * f;
		EREssence * s;
		foreach (EREssence * e, essenceList)
		{
			if(e->getId() == DataController::getInstance()->search(std::get<0>(row))->getId())
			{
				f = e;
			}
			if(e->getId() == DataController::getInstance()->search(std::get<1>(row))->getId())
			{
				s = e;
			}
		}

		Arrow * a = new Arrow(f,s,
							  Support::cardinalityToString(std::get<2>(row)),
							  Support::cardinalityToString(std::get<3>(row)));
		arrowList.append(a);
		scene->addItem(a);
	}


	//Рисование стрелок для свойств
	foreach (EREssence * e, essenceList)
	{
		EREssenceData * d = DataController::getInstance()->search(e->getId());
		foreach (EREssenceProperty * p, propertyList)
		{
			if(d->getKeys().contains(p->getId()))
			{
				Arrow * a = new Arrow(e,p, Support::cardinalityToString(cordinalyty::hiddenCord), Support::cardinalityToString(cordinalyty::hiddenCord));
				arrowList.append(a);
				scene->addItem(a);
				continue;
			}

			if(d->getAttributes().contains(p->getId()))
			{
				Arrow * a = new Arrow(e,p, Support::cardinalityToString(cordinalyty::hiddenCord), Support::cardinalityToString(cordinalyty::hiddenCord));
				arrowList.append(a);
				scene->addItem(a);
				continue;
			}
		}
	}


	foreach (EREssence * e, essenceList)
	{
		scene->addItem(e);
	}

	foreach (EREssence * e, propertyList)
	{
		scene->addItem(e);
	}
}


//bool EssenceGraphicsController::addEssence(EREssence * essence)
//{
//	essenceList.append(essence);
//}

//bool EssenceGraphicsController::addProperty(EREssenceProperty * property)
//{
//	propertyList.append(property);
//}

//bool EssenceGraphicsController::addArrow(Arrow * arrow)
//{
//	arrowList.append(arrow);
//}

//void EssenceGraphicsController::renameEssence(QString old_name, QString new_name)
//{

//	foreach (EREssenceProperty * p, propertyList)
//	{
//		p->getNonConstId().replace(old_name, new_name);
////		if(e->getNonConstId().replace(old_name, new_name));
//	}
//}

//EREssence *EssenceGraphicsController::getEssence(QString id)
//{
//	foreach (EREssence * e, essenceList)
//	{
//		if(e->getId() == id)
//		{
//			return e;
//		}
//	}

//	return nullptr;
//}

//EREssence *EssenceGraphicsController::getProperty(QString parent, QString name_property)
//{
//	foreach (EREssenceProperty * e, propertyList)
//	{
//		if(e->getId() == parent+"::"+name_property)
//		{
//			return e;
//		}
//	}

//	return nullptr;
//}

//Arrow *EssenceGraphicsController::getArrow(QString parent1, QString parent2)
//{
//	foreach (Arrow * e, arrowList)
//	{
//		if(e->startItem()->getId() == parent1 || e->endItem()->getId() == parent2)
//		{
//			return e;
//		}
//		if(e->startItem()->getId() == parent2 || e->endItem()->getId() == parent1)
//		{
//			return e;
//		}
//	}
//	return nullptr;
//}

void EssenceGraphicsController::print()
{
	qDebug("Essences");
	foreach (EREssence * e, essenceList)
	{
		qDebug() << e->getId() << ", ";
	}
	qDebug("\nProperties");
	foreach (EREssenceProperty * e, propertyList)
	{
		qDebug() << e->getId() << ", ";
	}

	qDebug("\nArrows");
	foreach (Arrow * e, arrowList)
	{
		qDebug() << e->startItem()->getId() << ", " << e->endItem()->getId() << "\n";
	}
}
