#ifndef ESSENCECREATEWINDOW_H
#define ESSENCECREATEWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <DataController.h>
#include <EssenceGraphicsController.h>
#include <QRegExp>
#include <QDebug>
#include <QRegExpValidator>

class EssenceCreateWindow : public QWidget
{
		Q_OBJECT
	public:
		explicit EssenceCreateWindow(QString id, int type, QWidget *parent = 0);
		bool loadData(QString id);
	private:
		QLineEdit name;
		QTableWidget keys;
		QTableWidget attributes;
		QGridLayout lay;
		QPushButton submit;
		QPushButton cancel;
		QPushButton remove;

		QString old_id;
		int current_type;
		QList<QString> old_keys;
		QList<QString> old_attrs;
		bool editMode = false;
		std::tuple<QString, int, QList<QString>, QList<QString>> old_data;

		void createWindow();

		QRegExp regExp;
		QRegExpValidator validator;
signals:
		void endSuccessCreation(QString id);
		void endSuccessEditation(QString id);
		void toDeleteEssence(QString id);
	public slots:
		void submitCreation(bool);
		void cancelCreation(bool);
		void removeEssence();






};

#endif // ESSENCECREATEWINDOW_H
