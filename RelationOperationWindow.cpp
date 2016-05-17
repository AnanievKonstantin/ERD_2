#include "RelationOperationWindow.h"

RelationOperationWindow::RelationOperationWindow(int mode, QWidget *parent) : QWidget(parent)
{

	this->mode = mode;
	l = new QGridLayout();
	cancel = new QPushButton();
	submit = new QPushButton();
	menuEssenceA		= new QComboBox();
	menuEssenceB		= new QComboBox();
	menuCordinalityA	= new QComboBox();
	menuCordinalityB	= new QComboBox();
	col_1 = new QLabel();
	col_2 = new QLabel();
	col_3 = new QLabel();
	col_4 = new QLabel();

	l->addWidget(menuEssenceA, 1,0);
	l->addWidget(menuCordinalityA, 1, 1);
	l->addWidget(menuCordinalityB, 1, 2);
	l->addWidget(menuEssenceB, 1,3);

	cancel->setText("Cancel");
	submit->setText("Create");
	l->addWidget(cancel, 2,1);
	l->addWidget(submit, 2,2);

	l->addWidget(col_1, 0, 0);
	l->addWidget(col_2, 0, 1);
	l->addWidget(col_3, 0, 2);
	l->addWidget(col_4, 0, 3);


	QList<int> cord_list; cord_list
			<< cordinalyty::OneZero
			<< cordinalyty::OneOne
			<< cordinalyty::OneMany
			<< cordinalyty::ZeroMany;

	foreach (int c, cord_list)
	{
		menuCordinalityA->addItem(Support::cardinalityToString(c), c);
		menuCordinalityB->addItem(Support::cardinalityToString(c), c);
	}

	QList<QString> essences_list = DataController::getInstance()->getEssences();

//			QList<QString> essences_list; essences_list << "A" << "B" << "D" << "E";

	if(this->mode == 3)
	{
//		qDebug() << "Создание новой связи";

		col_1->setText("Сущность А");
		col_4->setText("Сущность B");
		col_3->setText("Кординальность к B");
		col_2->setText("Кординальность к A");

		foreach (QString s, essences_list)
		{
			menuEssenceA->addItem(s);
			menuEssenceB->addItem(s);
		}

	}

	if(this->mode == 4)
	{
//		qDebug() << "Включение в ассоциацию";

		col_1->setText("Первичные сущности");
		col_4->setText("Ассоциации");
//		col_3->setText("Кординальность");
		col_2->setText("Кординальность");
		submit->setText("Insert");

		foreach (QString s, essences_list)
		{
			EREssenceData * essence = DataController::getInstance()->search(s);
			if(essence == nullptr)
			{
				qDebug() << "__ERROR__: in RelationOperationWindow::RelationOperationWindow(int mode, QWidget *parent) : QWidget(parent) null pointer expection";
				continue;
			}

			if(essence->getType() == essence_type::Base)
			{
				menuEssenceA->addItem(s);
				continue;
			}

			if(essence->getType() == essence_type::Association)
			{
				menuEssenceB->addItem(s);
				continue;
			}
		}

		foreach (int c, cord_list)
		{
			menuCordinalityA->addItem(Support::cardinalityToString(c), c);
		}

		this->menuCordinalityB->setDisabled(true);
	}

	if(this->mode == 5)
	{
//		qDebug() << "Удаление связи между";

		col_1->setText("Сущность А");
		col_4->setText("Сущность B");
//		col_3->setText("Кординальность");
//		col_2->setText("Кординальность");
		submit->setText("Remove");

		foreach (QString s, essences_list)
		{
			menuEssenceA->addItem(s);
			menuEssenceB->addItem(s);
		}

		this->menuCordinalityB->setDisabled(true);
		this->menuCordinalityA->setDisabled(true);
	}

	if(this->mode == 6)
	{
		qDebug() << "Редактировани кардинальностей";

		col_1->setText("Сущность А");
		col_4->setText("Сущность B");
		col_2->setText("Кординальность к B");
		col_3->setText("Кординальность к A");
//		menuCordinalityB->setDisabled(true);
		submit->setText("Edit");

		foreach (QString s, essences_list)
		{
			menuEssenceB->addItem(s);
			menuEssenceA->addItem(s);
		}
	}

	this->setLayout(l);

	QObject::connect(cancel, SIGNAL(clicked(bool)), this, SLOT(cancelWork(bool)));
	QObject::connect(submit, SIGNAL(clicked(bool)), this, SLOT(checkSubmossion(bool)));
}

void RelationOperationWindow::setAEssece(QString name)
{
	qDebug() << "A essence:" << name;
}

void RelationOperationWindow::checkSubmossion(bool test)
{
	qDebug() << "Проверка операций со связями";
	qDebug() << "A: " << menuEssenceA->currentText();
	qDebug() << "B: " << menuEssenceB->currentText();
	qDebug() << "cord A: " << menuCordinalityA->currentText();
	qDebug() << "cord B: " << menuCordinalityB->currentText();

	QString A = menuEssenceA->currentText();
	QString B = menuEssenceB->currentText();
	int cord_A = menuCordinalityA->currentData().toInt();
	int cord_B = menuCordinalityB->currentData().toInt();
	switch (mode)
	{
	case 3:
	{
		if(DataController::getInstance()->createRelation(A, B, cord_A, cord_B) == 0)
		{
			emit successRelationOperation(true);
			close();
		}
		break;
	}
	case 4:
	{
		if(DataController::getInstance()->joinBaseToExistAssociation(A,B,cord_A) == 0)
		{
			emit successRelationOperation(true);
			close();
		}
		break;
	}
	case 5:
	{
		int ans = DataController::getInstance()->removeRelation(A, B);
		if(ans == 0)
		{
			emit successRelationOperation(true);
			close();
		}
		break;
	}
	case 6:
	{
		if(DataController::getInstance()->setCordinality(A, B, cord_A, cord_B) == 0)
		{
			emit successRelationOperation(true);
			close();
		}
		break;
	}

	default:
		break;
	}
}

void RelationOperationWindow::cancelWork(bool check)
{
	qDebug() << "Отмена операций со связями";
	close();
}
