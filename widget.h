#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include "ERGraphicsView.h"
#include "EREssenceBase.h"
#include "ERGraphicsView.h"
#include <QGraphicsRectItem>
#include "EREssenceDesignation.h"
#include "EREssenceCharacteristic.h"
#include "EREssenceRelation.h"
#include "EREssenceProperty.h"
#include <Arrow.h>
#include <DataController.h>
#include <EssenceGraphicsController.h>
#include <EssenseCreateWindow.h>
#include <RelationOperationWindow.h>
#include <QShortcut>
#include <QKeySequence>
#include <TreeModel.h>
#include <QTreeView>
#include <TreeModelForOneEssence.h>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QTabWidget>
#include <DataModelGraphicsView.h>
#include <ConsoleOutput.h>
#include <QSplitter>

/**
 * @brief The Widget class
 *	Основной контроллер программы, описывает главное, окно, сигнылы и слоты для предачи данных между
 *	элементами окна и DataController
 */
class Widget : public QWidget
{
		Q_OBJECT

	public:
		Widget(QWidget *parent = 0);
		~Widget();

	private:
		/**
		 * @brief initViev
		 *	устанавливает начальные параметры
		 */
		void initViev();

		/**
		 * @brief syncTreeViev
		 *	синхронизирует графические представления с данными диаграмм
		 */
		void syncTreeViev();

		QHBoxLayout * layoutH;
		QVBoxLayout * layoutV;

		ERGraphicsView * erView;
		DataModelGraphicsView * dataView;
		TreeModel * treeModel;
		QTreeView * treeViev;
		QTabWidget * tabs;

		QSplitter * vSplit;
		QSplitter * hSplit;



		TreeModelForOneEssence* treeModelForOneEssence;
		QTreeView * treeVievOneEssence;
		QMenuBar * bar;

		/**
		 * @brief setUpSignalsAndSlots
		 *	устанавливает сигналы и слоты
		 * @return
		 */
		bool setUpSignalsAndSlots();

		/**
		 * @brief initBar
		 *	инициализирует главное меню прграммы
		 */
		bool initBar();

		/**
		 * @brief createWindow
		 *	создаёт окно
		 */
		void createWindow();

		/**
		 * @brief setUpConsoleProperty
		 *	настриивает началтные настройки консоли
		 */
		void setUpConsoleProperty();

	public slots:
		void setUpTreeViews();
		void editEssence(QString id);
		void createEssence(int type);
		void addEssenceOnScreen(QString id);
		void removeEssence(QString id);
		void performRelationOperation(int action_code);
		void afterPerformRelationOperation(bool);
		void quick_save();
		void save_as();
		void new_file();
		void load_file();
		void endWork();
		void help();
		void treeViewEssenceUpdate(QString id);
		void closeEditWindow();

};

#endif // WIDGET_H
