#include "widget.h"

Widget::Widget(QWidget *parent)
	: QWidget(parent)
{
	this->layout = new QHBoxLayout(this);
	this->erView = new ERGraphicsView();
	layout->addWidget(erView);
	EssenceGraphicsController::instance();
	EssenceGraphicsController::setScene(erView->getScene());
	setUpSignalsAndSlots();
}

bool Widget::setUpSignalsAndSlots()
{
	QObject::connect(this->erView, SIGNAL(doCreation(int)), this, SLOT(createEssence(int)));

}

Widget::~Widget()
{

}

void Widget::editEssence(QString id)
{
	int type = DataController::getInstance()->search(id)->getType();
	EssenceCreateWindow * win = new EssenceCreateWindow(id, type);
	QObject::connect(win, SIGNAL(toDeleteEssence(QString)), this, SLOT(removeEssence(QString)));
	win->show();
}

void Widget::createEssence(int type)
{

	QList<QString> keys;
	static int i = 0;
	QList<QString> attributes; attributes << "def_attr" + i;
		EssenceCreateWindow * win = new EssenceCreateWindow("", type);
		QObject::connect(win, SIGNAL(endSuccessCreation(QString)), this, SLOT(addEssenceOnScreen(QString)));
//		QObject::connect(win, SIGNAL(toDeleteEssence(QString)), this, SLOT(removeEssence(QString)));
		win->show();


}

void Widget::addEssenceOnScreen(QString id)
{
	EREssenceData * data = DataController::getInstance()->search(id);

	if(data == nullptr)
	{
		qDebug() << "__ERROR__: in void Widget::addEssenceOnScreen(QString id) nullptr expection";
		return;
	}

	EssenceGraphicsController::instance()->syncWithDataContriller();
//	EREssenceBase *b = new EREssenceBase(data);
//	EssenceGraphicsController::instance()->addEssence(b);

//	QObject::connect(b, SIGNAL(edit(QString)), this, SLOT(editEssence(QString)));
//	this->erView->getScene()->addItem(b);
//	foreach (QString attr, data->getAttributes())
//	{
//		EREssenceProperty * p = new EREssenceProperty(new EREssenceData(attr, essence_type::Property_default));
//		Arrow * a = new Arrow(b,p);

//		EssenceGraphicsController::instance()->addProperty(p);
//		EssenceGraphicsController::instance()->addArrow(a);
//		erView->getScene()->addItem(a);
//		erView->getScene()->addItem(p);

//	}

//	foreach (QString key, data->getKeys())
//	{
//		int type =Property_key;
//		if(key.lastIndexOf("::") != -1)
//		{
//			type = essence_type::Property_foreign_key;
//		}

//		EREssenceProperty * p = new EREssenceProperty(new EREssenceData(key, type));
//		Arrow * a = new Arrow(b,p);

//		EssenceGraphicsController::instance()->addProperty(p);
//		EssenceGraphicsController::instance()->addArrow(a);
//		erView->getScene()->addItem(a);
//		erView->getScene()->addItem(p);

//	}

//	EssenceGraphicsController::instance()->print();
}

void Widget::removeEssence(QString id)
{
//	erView->getScene()->removeItem(EssenceGraphicsController::instance()->getEssence(id));
//	qDebug() << "Deleted: " << id <<"\n";
}

