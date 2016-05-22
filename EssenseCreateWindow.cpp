#include "EssenseCreateWindow.h"

EssenceCreateWindow::EssenceCreateWindow(QString id, int type, QWidget *parent) : QWidget(parent)
{

	old_id = id;
	current_type = type;
	regExp.setPattern("[A-Z,a-z,А-Я,а-я]{1,15}");
	validator.setRegExp(regExp);
	createWindow();

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
	keys.clear();
	attributes.clear();

	qDebug() << "load\n";
//	EssenceDataController::instance()->getInfoAboutEssence(id);
	EREssenceData * p_data  = DataController::getInstance()->search(id);

	old_data = std::make_tuple(p_data->getId(), p_data->getType(), p_data->getKeys(), p_data->getAttributes());
	old_attrs = p_data->getAttributes();
	old_keys = p_data->getKeys();

	this->name.setText(std::get<0>(old_data));

//	for(int i = 0; i < std::get<2>(old_data).length(); i++)
//	{
//		if(std::get<2>(old_data).at(i).contains("::") == true || (std::get<2>(old_data).at(i).contains("_id") == true))
//		{
////			QTableWidgetItem * it = new QTableWidgetItem(std::get<2>(old_data).at(i));
//			QLineEdit * it = new QLineEdit(std::get<2>(old_data).at(i));
//			it->setDisabled(true);
////			it->setFlags(it->flags() &  ~Qt::ItemIsEditable);
////			keys.setItem(i,0, it);
//			it->setValidator(&validator);
//			keys.setCellWidget(i, 0, it);
//			it = nullptr;
//		}
//		else
//		{
//			QLineEdit * it = new QLineEdit(std::get<2>(old_data).at(i));
//			it->setValidator(&validator);
//			keys.setCellWidget(i,0, it);
//		}

//	}

//	for(int i = 0; i < std::get<3>(old_data).length(); i++)
//	{
//		attributes.setItem(i,0, new QTableWidgetItem(std::get<3>(old_data).at(i)));
//	}

	//keys col creation
	for(int i = 0; i < keys.rowCount(); i++)
	{
		if(i < std::get<2>(old_data).length())
		{
			if(std::get<2>(old_data).at(i).contains("::") == true || (std::get<2>(old_data).at(i).contains("_id") == true))
			{
				QLineEdit * it = new QLineEdit(std::get<2>(old_data).at(i));
				it->setDisabled(true);
				it->setValidator(&validator);
				keys.setCellWidget(i, 0, it);
				it = nullptr;
			}
			else
			{
				QLineEdit * it = new QLineEdit(std::get<2>(old_data).at(i));
				it->setValidator(&validator);
				keys.setCellWidget(i, 0, it);
				it = nullptr;
			}
		}
		else
		{
			QLineEdit * it = new QLineEdit();
			it->setValidator(&validator);
			keys.setCellWidget(i, 0, it);
			it = nullptr;
		}
	}

	//attrs col creation
	for(int i = 0; i < attributes.rowCount(); i++)
	{
		if(i < std::get<3>(old_data).length())
		{
			if(std::get<3>(old_data).at(i).contains("::") == true || (std::get<3>(old_data).at(i).contains("_id") == true))
			{
				QLineEdit * it = new QLineEdit(std::get<3>(old_data).at(i));
				it->setDisabled(true);
				it->setValidator(&validator);
				attributes.setCellWidget(i, 0, it);
				it = nullptr;
			}
			else
			{
				QLineEdit * it = new QLineEdit(std::get<3>(old_data).at(i));
				it->setValidator(&validator);
				attributes.setCellWidget(i, 0, it);
				it = nullptr;
			}
		}
		else
		{
			QLineEdit * it = new QLineEdit();
			it->setValidator(&validator);
			attributes.setCellWidget(i, 0, it);
			it = nullptr;
		}
	}

}

void EssenceCreateWindow::createWindow()
{
	setWindowFlags( ( (this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint));
	attributes.setRowCount(200);
	attributes.setColumnCount(1);
	attributes.setColumnWidth(0, 400);

	QHeaderView * headKeysAttribut = new QHeaderView(Qt::Horizontal);
	headKeysAttribut->setSectionResizeMode(QHeaderView::Stretch);
	attributes.setHorizontalHeader(headKeysAttribut);

	QTableWidgetItem* item1 = new QTableWidgetItem("Название");
	item1->setText("Название");
	attributes.setHorizontalHeaderItem(0, item1);


	keys.setRowCount(50);
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
	name.setValidator(&validator);
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


	keys.clear();
	attributes.clear();

	for(int i = 0; i < keys.rowCount(); i++)
	{
		QLineEdit * it = new QLineEdit();
//		it->setDisabled(true);
//			it->setFlags(it->flags() &  ~Qt::ItemIsEditable);
//			keys.setItem(i,0, it);
		it->setValidator(&validator);
		keys.setCellWidget(i, 0, it);
	}

	for(int i = 0; i < attributes.rowCount(); i++)
	{
		QLineEdit * it = new QLineEdit();
//		it->setDisabled(true);
//			it->setFlags(it->flags() &  ~Qt::ItemIsEditable);
//			keys.setItem(i,0, it);
		it->setValidator(&validator);
		attributes.setCellWidget(i, 0, it);
	}

	this->setLayout(&lay);
}

void EssenceCreateWindow::submitCreation(bool)
{

//	old_attrs.clear();
//	old_keys.clear();

	qDebug() << "Проверка введенных данных";
	QString new_id = this->name.text();
	QList<QString> new_keys;
	QList<QString> new_attributes;

	for(int i = 0; i < this->keys.rowCount(); i++)
	{
		if(this->keys.cellWidget(i,0) == nullptr)
		{
			continue;
		}
		else
		{
			QLineEdit * data = (QLineEdit*)keys.cellWidget(i,0);
			if(data->text() == "")
			{
				continue;
			}
			new_keys.append(data->text());
		}
	}

	for(int i = 0; i < this->attributes.rowCount(); i++)
	{
		if(this->attributes.cellWidget(i,0) == nullptr)
		{
			continue;
		}
		else
		{
			QLineEdit * data = (QLineEdit*)attributes.cellWidget(i,0);
			if(data->text() == "")
			{
				continue;
			}
			new_attributes.append(data->text());
		}
	}

	if(editMode == true)
	{
		qDebug() << "\nПроверка при редактировании сущности: ";

		qDebug() <<"Old_keys: "<<old_keys;
		qDebug() <<"old_attrs: "<<old_attrs;
		qDebug() <<"old_id: "<<old_id;

		qDebug() <<"new_keys: "	<<	new_keys;
		qDebug() <<"new_attrs: "<<	new_attributes;
		qDebug() <<"new_id: "	<<	new_id;

		int error_dubl_key		= 0;
		int error_dubl_attr		= 0;
		int error_add_key		= 0;
		int error_add_attr		= 0;
		int error_remove_key	= 0;
		int error_remove_attr	= 0;

		//add new keys
		foreach (QString key, new_keys)
		{
			if(old_keys.contains(key) == false)
			{
				error_add_key = DataController::getInstance()->addKey(old_id, key);
				if(error_add_key != 0)
				{
					error_add_key = 1;
					break;
				}

			}
			if(new_keys.count(key) > 1)
			{
				qDebug() << "Ключ: " << key << "Дуюлируется. Проверьте ошибки";
				error_dubl_key = 1;
				break;
			}
		}

		//add new attrs
		foreach (QString attr, new_attributes)
		{
			if(old_attrs.contains(attr) == false)
			{
				error_add_attr = DataController::getInstance()->addAttribute(old_id, attr);
				if(error_add_attr != 0)
				{
					error_add_attr = 1;
					break;
				}
			}

			if(new_attributes.count(attr) > 1)
			{
				qDebug() << "Атрибут: " << attr<< "Дуюлируется. Проверьте ошибки";
				error_dubl_attr = 1; break;
			}
		}

		//remove key
		foreach (QString key, old_keys)
		{
			if(new_keys.contains(key) == false)
			{
				error_remove_key = DataController::getInstance()->removeKey(old_id, key);
				if(error_remove_key != 0)
				{
					error_remove_key = 1;
					break;
				}
			}
		}

		//remove attrs
		foreach (QString attr, old_attrs)
		{
			if(new_attributes.contains(attr) == false)
			{
				error_remove_attr = DataController::getInstance()->removeAttribute(old_id, attr);
				if(error_remove_attr != 0)
				{
					error_remove_attr = 1;
					break;
				}
			}
		}

		int error_rename = 0;
		if(old_id != new_id)
		{
			error_rename = DataController::getInstance()->renameEssence(old_id, new_id);
			if(error_rename != 0)
			{
				error_rename = 1;
			}
		}

		if(error_rename == 1	|| error_add_attr == 1		||
		   error_add_key == 1	|| error_dubl_attr == 1		||
		   error_dubl_key == 1	|| error_remove_attr == 1	||
		   error_remove_key == 1)
		{
			loadData(old_id);
			qDebug() << "error_dubl_key	  " << error_dubl_key	  ;
			qDebug() << "error_dubl_attr  " << error_dubl_attr    ;
			qDebug() << "error_add_key	  " << error_add_key	  ;
			qDebug() << "error_add_attr	  " << error_add_attr	  ;
			qDebug() << "error_remove_key " << error_remove_key   ;
			qDebug() << "error_remove_attr" << error_remove_attr  ;
			qDebug() << "\nERROR";
		}
		else
		{
			qDebug() << "\nПроверка пройдена";
			emit endSuccessEditation(new_id);
			this->close();
		}
	}

	if(editMode == false)
	{
		qDebug() << "\nПроверка при создании сущности: ";
		int error = DataController::getInstance()->createEssence(new_id, current_type, new_keys, new_attributes);
		DataController::getInstance()->printAllEssence();
		if(error == 0)
		{
			qDebug() << "\nПроверка пройдена";
			emit endSuccessCreation(new_id);
			this->close();
		}
	}
}


void EssenceCreateWindow::cancelCreation(bool)
{
	qDebug() << "Работа с обьектом прервана" << "\n";
	emit exitFromCreateWindow();
	this->close();
}

void EssenceCreateWindow::removeEssence()
{
	int error = 0;
	error = DataController::getInstance()->removeEssence(old_id);
	if(error == 0)
	{
		emit endDeletetion(old_id);
		this->close();
	}
}






























