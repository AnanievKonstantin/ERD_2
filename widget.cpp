#include "widget.h"

Widget::Widget(QWidget *parent)
	: QWidget(parent)
{
	this->layout = new QHBoxLayout(this);
	this->erView = new ERGraphicsView();
	this->treeModel = new TreeModel();
	this->treeViev = new QTreeView();

	this->treeModelForOneEssence = new TreeModelForOneEssence("__EMPTY__");
	this->treeVievOneEssence = new QTreeView();

//	treeVievOneEssence->setGeometry(QRect(0,0, 100, 100));
	treeVievOneEssence->setMinimumWidth(250);
	treeVievOneEssence->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);

	treeViev->setGeometry(QRect(0,0, 100, 100));
	treeViev->setMinimumWidth(200);
	treeViev->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);

	treeViev->setModel(treeModel);
	treeVievOneEssence->setModel(treeModelForOneEssence);



	treeVievOneEssence->setRootIsDecorated(false);
	treeVievOneEssence->setAlternatingRowColors(true);
	treeVievOneEssence->setAllColumnsShowFocus(true);
	treeVievOneEssence->setExpandsOnDoubleClick(false);
	treeVievOneEssence->setEditTriggers(QAbstractItemView::NoEditTriggers);
	treeVievOneEssence->setSortingEnabled(true);
	treeVievOneEssence->sortByColumn(0, Qt::AscendingOrder);
	treeVievOneEssence->header()->resizeSections(QHeaderView::ResizeToContents);

//	treeViev->setRootIsDecorated(false);
	treeViev->setAlternatingRowColors(true);
//	treeViev->setAllColumnsShowFocus(true);
//	treeViev->setExpandsOnDoubleClick(false);
//	treeViev->setEditTriggers(QAbstractItemView::NoEditTriggers);
//	treeViev->setSortingEnabled(true);
//	treeViev->sortByColumn(0, Qt::AscendingOrder);
//	treeViev->header()->resizeSections(QHeaderView::ResizeToContents);

	treeVievOneEssence->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//	treeViev->setAutoScroll(true);
	layout->addWidget(treeViev);
	layout->addWidget(erView);
	layout->addWidget(treeVievOneEssence);

	EssenceGraphicsController::instance();
	EssenceGraphicsController::setScene(erView->getScene());

	setUpSignalsAndSlots();
}

bool Widget::setUpSignalsAndSlots()
{
	QObject::connect(this->erView, SIGNAL(doCreation(int)), this, SLOT(createEssence(int)));
	QObject::connect(this->erView, SIGNAL(doRelationOperation(int)), this, SLOT(performRelationOperation(int)));
	QObject::connect(EssenceGraphicsController::instance(), SIGNAL(startEditEssence(QString)), this, SLOT(editEssence(QString)));
	QObject::connect(EssenceGraphicsController::instance(), SIGNAL(startFocucedEssence(QString)), this, SLOT(treeViewEssenceUpdate(QString)));
	QShortcut * key = new QShortcut(QKeySequence("Ctrl+S"), this);
	key->setContext(Qt::ShortcutContext::ApplicationShortcut);
	QObject::connect(key, SIGNAL(activated()), this, SLOT(save()));


}

Widget::~Widget()
{

}

void Widget::syncTreeViev()
{
	delete treeModel;
	treeModel = new TreeModel;
	treeViev->setModel(treeModel);
//	treeViev->expandAll();
}

void Widget::editEssence(QString id)
{
	qDebug() <<"in edit";
	int type = DataController::getInstance()->search(id)->getType();
	EssenceCreateWindow * win = new EssenceCreateWindow(id, type);
//	QObject::connect(win, SIGNAL(toDeleteEssence(QString)), this, SLOT(removeEssence(QString)));
	QObject::connect(win, SIGNAL(endSuccessCreation(QString)), this, SLOT(addEssenceOnScreen(QString)));
	QObject::connect(win, SIGNAL(endSuccessEditation(QString)), this, SLOT(addEssenceOnScreen(QString)));
	QObject::connect(win, SIGNAL(endDeletetion(QString)), this, SLOT(removeEssence(QString)));
	win->show();
}

void Widget::createEssence(int type)
{

	EssenceCreateWindow * win = new EssenceCreateWindow("", type);
	QObject::connect(win, SIGNAL(endSuccessCreation(QString)), this, SLOT(addEssenceOnScreen(QString)));
//	QObject::connect(win, SIGNAL(toDeleteEssence(QString)), this, SLOT(removeEssence(QString)));
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
	syncTreeViev();

}

void Widget::removeEssence(QString id)
{
	EssenceGraphicsController::instance()->syncWithDataContriller();
	syncTreeViev();
}

void Widget::performRelationOperation(int action_code)
{
	switch (action_code) {
		case 3:
		{
			RelationOperationWindow * w = new RelationOperationWindow(action_code);
			QObject::connect(w, SIGNAL(successRelationOperation(bool)), this, SLOT(afterPerformRelationOperation(bool)));
			w->show();
			//qDebug("Создаю: связь");
			break;
		}
		case 4:
		{
			RelationOperationWindow * w = new RelationOperationWindow(action_code);
			QObject::connect(w, SIGNAL(successRelationOperation(bool)), this, SLOT(afterPerformRelationOperation(bool)));
			w->show();
			break;

		}
		case 5:
		{
			RelationOperationWindow * w = new RelationOperationWindow(action_code);
			QObject::connect(w, SIGNAL(successRelationOperation(bool)), this, SLOT(afterPerformRelationOperation(bool)));
			w->show();
			//qDebug("Удаляю связь");
			break;
		}
		case 6:
		{
			RelationOperationWindow * w = new RelationOperationWindow(action_code);
			QObject::connect(w, SIGNAL(successRelationOperation(bool)), this, SLOT(afterPerformRelationOperation(bool)));
			w->show();
			//qDebug("изменяю кардинальность");
			break;

		}
		default:
			qDebug("__ERROR_: in void Widget::performRelationOperation(int action_code) error action code");
			break;
	}

}

void Widget::afterPerformRelationOperation(bool test)
{
	EssenceGraphicsController::instance()->syncWithDataContriller();
	syncTreeViev();
}

void Widget::save()
{
	qDebug() << "START SAVE:";
}

void Widget::treeViewEssenceUpdate(QString id)
{
	qDebug() << "Updating";
	delete treeModelForOneEssence;
	treeModelForOneEssence = new TreeModelForOneEssence(id);
	treeVievOneEssence->setModel(treeModelForOneEssence);
	treeVievOneEssence->expandAll();

}

