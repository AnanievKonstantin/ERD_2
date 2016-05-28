#include "EssenceGraphicsController.h"

EssenceGraphicsController * EssenceGraphicsController::self = nullptr;
QGraphicsScene * EssenceGraphicsController::er_scene = nullptr;
QGraphicsScene * EssenceGraphicsController::data_scene = nullptr;

EssenceGraphicsController::EssenceGraphicsController(QObject *parent) : QObject(parent)
{

}

void EssenceGraphicsController::clearAll()
{
	//отчиска списков
	foreach (EREssence *e, essenceList)
	{
		er_scene->removeItem(e);
	}

	foreach (EREssenceProperty *e, propertyList)
	{
		er_scene->removeItem(e);
	}

	foreach (Arrow *e, arrowList)
	{
		er_scene->removeItem(e);
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

	foreach (Arrow *e, arrowTableList)
	{
		delete e;
	}

	foreach (DataTable *e, tableList)
	{
		delete e;
	}

	arrowTableList.clear();
	tableList.clear();
	essenceList.clear();
	propertyList.clear();
	arrowList.clear();
}

void EssenceGraphicsController::fillERScene()
{
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
		er_scene->addItem(a);
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
				er_scene->addItem(a);
				continue;
			}

			if(d->getAttributes().contains(p->getId()))
			{
				Arrow * a = new Arrow(e,p, Support::cardinalityToString(cordinalyty::hiddenCord), Support::cardinalityToString(cordinalyty::hiddenCord));
				arrowList.append(a);
				er_scene->addItem(a);
				continue;
			}
		}
	}


	foreach (EREssence * e, essenceList)
	{
		er_scene->addItem(e);
	}

	foreach (EREssence * e, propertyList)
	{
		er_scene->addItem(e);
	}
}

void EssenceGraphicsController::fillDataScene()
{
	foreach (QString s, DataController::getInstance()->getEssences())
	{
		EREssenceData * d = DataController::getInstance()->search(s);
		DataTable * t = new DataTable(d);
		tableList.append(t);
		data_scene->addItem(t);
	}

	//Создание и рисование стрелок. Заполнение списка стрелок
	QList<std::tuple<QString, QString, int, int> > table = DataController::getInstance()->getRelationTable();
	for(int i =0 ; i < table.length() ; i++)
	{
		std::tuple<QString, QString, int, int> row = table.at(i);
		EREssence * f;
		EREssence * s;
		foreach (EREssence * e, tableList)
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
		a->enableTableDrawMode();
		arrowTableList.append(a);
		data_scene->addItem(a);
	}
}

void EssenceGraphicsController::createEssenceWithPropertyWithCordinate()
{
	QPoint essence_pos = {-1000, -600};
	QPoint property_pos = {-500, -500};
	qreal dx = 10;
	qreal dy = 30;
	qreal dEPx = 0;
	qreal dEPy = 50;
	qreal shiftEssenceByX = 250;
	qreal shiftEssenceByY = 250;

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

		switch_pointer->setPos(essence_pos);

		essenceList.append(switch_pointer);
		QObject::connect(switch_pointer, SIGNAL(edit(QString)), this, SLOT(emitEditEssenceSignal(QString)));
		QObject::connect(switch_pointer, SIGNAL(focued(QString)), this, SLOT(emitFocucedEssenceSignal(QString)));

		property_pos.setX(essence_pos.x());
		property_pos.setY(essence_pos.y() + dEPy);
		essence_pos.setX(essence_pos.x() + shiftEssenceByX);

		foreach (QString attr, DataController::getInstance()->getProperties(s, 2))
		{
			EREssenceProperty * p = new EREssenceProperty(new EREssenceData(attr, essence_type::Property_default));
			p->setPos(property_pos);
			property_pos.setY(property_pos.y() + dy);
			propertyList.append(p);
		}
		foreach (QString key, DataController::getInstance()->getProperties(s, 1))
		{
			EREssenceProperty * p = new EREssenceProperty(new EREssenceData(key, essence_type::Property_key));
			p->setPos(property_pos);
			property_pos.setY(property_pos.y() + dy);
			propertyList.append(p);
			continue;
		}
		foreach (QString comb_key, DataController::getInstance()->getProperties(s, 3))
		{
			EREssenceProperty * p = new EREssenceProperty(new EREssenceData(comb_key, essence_type::Property_combinated_key));
			p->setPos(property_pos);
			property_pos.setY(property_pos.y() + dy);
			propertyList.append(p);
			continue;
		}

		if(essence_pos.x() > 0)
		{
			essence_pos.setX(-1000);
			essence_pos.setY(essence_pos.y()+ shiftEssenceByY);
		}
	}

}

void EssenceGraphicsController::emitEditEssenceSignal(QString id)
{
	emit startEditEssence(id);
}

void EssenceGraphicsController::emitFocucedEssenceSignal(QString id)
{
	emit startFocucedEssence(id);
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

void EssenceGraphicsController::setSceneToErModel(QGraphicsScene *_scene)
{
	if(_scene == nullptr)
	{
		ConsoleOutput::getInstance()->printSystemError("__ERROR__: in void EssenceGraphicsController::setSceneToErModel(QGraphicsScene *_scene) nullptr expection");
		return;
	}
	if(er_scene == nullptr)
	{
		er_scene = _scene;
	}
	else
	{
		return;
	}

}

void EssenceGraphicsController::setSceneToDataModel(QGraphicsScene *_scene)
{
	if(_scene == nullptr)
	{
		ConsoleOutput::getInstance()->printSystemError("__ERROR__: in void EssenceGraphicsController::setSceneToDataModel(QGraphicsScene *_scene) nullptr expection");
		return;
	}
	if(data_scene == nullptr)
	{
		data_scene = _scene;
	}
	else
	{
		return;
	}
}

void EssenceGraphicsController::syncWithDataContriller()
{
	clearAll();
	//заполнение списков
	createEssenceWithPropertyWithCordinate();
	//---------------
	fillERScene();
	fillDataScene();

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
