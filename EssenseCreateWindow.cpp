#include "EssenseCreateWindow.h"

EssenceCreateWindow::EssenceCreateWindow(QString id, int type, QWidget *parent) : QWidget(parent)
{

	currentID = id;
	currentType = type;
	setWindowFlags( ( (this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowCloseButtonHint));
	attributes.setRowCount(200);
	attributes.setColumnCount(1);
	attributes.setColumnWidth(0, 400);

	QHeaderView * headKeysAttribut = new QHeaderView(Qt::Horizontal);
	headKeysAttribut->setSectionResizeMode(QHeaderView::Stretch);
	attributes.setHorizontalHeader(headKeysAttribut);

	QTableWidgetItem* item1 = new QTableWidgetItem("Название");
	item1->setText("Название");
	attributes.setHorizontalHeaderItem(0, item1);


	keys.setRowCount(200);
	keys.setColumnCount(1);

	QHeaderView * headKeys = new QHeaderView(Qt::Horizontal);
	headKeys->setSectionResizeMode(QHeaderView::Stretch);
	keys.setHorizontalHeader(headKeys);

	QTableWidgetItem* item0 = new QTableWidgetItem("Название");
	item0->setText("Название");
	keys.setHorizontalHeaderItem(0, item0);

	submit.setText("Готово");
	cancel.setText("Отмена");
	remove.setText("Удалить");

	this->setWindowTitle("Создание сущности");
	lay.addWidget(new QLabel("Имя"), 0,0);
	lay.addWidget(&name, 1,0);

	lay.addWidget(&remove, 1,1);

	lay.addWidget(new QLabel("Ключи"), 2,0);
	lay.addWidget(&keys, 3,0);
	lay.addWidget(new QLabel("Атрибуты"), 2,1);
	lay.addWidget(&attributes, 3,1);
	lay.addWidget(&submit, 4,1);
	lay.addWidget(&cancel, 4,0);

	QObject::connect(&submit, SIGNAL(clicked(bool)), this, SLOT(submitCreation(bool)));
	QObject::connect(&cancel, SIGNAL(clicked(bool)), this, SLOT(cancelCreation(bool)));
	QObject::connect(&remove, SIGNAL(clicked()), this, SLOT(removeEssence()));

	this->setLayout(&lay);

	if(id == "")
	{
		editMode = false;
		qDebug("Создаётся новая сущность");
	}
	else
	{
		qDebug("Редактируется существующая сущность");
		editMode = true;
		loadData(id);
	}

}

bool EssenceCreateWindow::loadData(QString id)
{
	qDebug() << "load\n";
//	EssenceDataController::instance()->getInfoAboutEssence(id);
	EREssenceData * p_data  = DataController::getInstance()->search(id);

	old_data = std::make_tuple(p_data->getId(), p_data->getType(), p_data->getKeys(), p_data->getAttributes());

	this->name.setText(std::get<0>(old_data));

	for(int i = 0; i < std::get<2>(old_data).length(); i++)
	{
		keys.setItem(i,0, new QTableWidgetItem(std::get<2>(old_data).at(i)));
	}

	for(int i = 0; i < std::get<3>(old_data).length(); i++)
	{
		attributes.setItem(i,0, new QTableWidgetItem(std::get<3>(old_data).at(i)));
	}

}

void EssenceCreateWindow::submitCreation(bool)
{
	QString new_id = this->name.text();
	QList<QString> new_keys;
	QList<QString> new_attributes;

	for(int i = 0; i < this->keys.rowCount(); i++)
	{
		if(this->keys.item(i,0) == nullptr || this->keys.item(i,0)->text() == "")
		{
			continue;
		}
		else
		{
			new_keys.append(this->keys.item(i,0)->text());
		}
	}

	for(int i = 0; i < this->attributes.rowCount(); i++)
	{
		if(this->attributes.item(i,0) == nullptr || this->attributes.item(i,0)->text() == "")
		{
			continue;
		}
		else
		{
			new_attributes.append(this->attributes.item(i,0)->text());
		}
	}

	if(editMode == true)
	{
		qDebug() << "Проверка при редактировании сущности";

		if(currentID != new_id)
		{
			DataController::getInstance()->renameEssence(currentID, new_id);
//			EssenceGraphicsController::instance()->renameEssence(currentID, new_id);
		}
//		foreach (QString new_key, new_keys)
//		{
//			if(std::get<2>(old_data).contains(new_key))
//			{
//				continue;
//			}
//			else
//			{

//			}
//		}
		DataController::getInstance()->printAllEssence();
	}
	else
	{
		qDebug() << "Проверка при создании сущности";

		int error = DataController::getInstance()->createEssence(new_id, currentType, new_keys, new_attributes);
		DataController::getInstance()->printAllEssence();
		qDebug() << "Error: " << error;
		if(error == 0)
		{
			emit succesCreation(true);
		}
	}
}

void EssenceCreateWindow::succesCreation(bool)
{
	qDebug("Загрузка из формы создания сущности");

	QString new_id = this->name.text();

	emit endSuccessCreation(new_id);

	this->hide();
}

void EssenceCreateWindow::cancelCreation(bool)
{
	qDebug() << "Работа с обьектом прервана" << "\n";
	this->close();
}

void EssenceCreateWindow::removeEssence()
{
	qDebug() <<"in void EssenceCreateWindow::removeEssence(bool) delete" << currentID;
//	emit toDeleteEssence(currentID);
}






























