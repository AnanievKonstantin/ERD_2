#ifndef RELATIONOPERATIONWINDOW_H
#define RELATIONOPERATIONWINDOW_H

#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <DataController.h>
#include <EssenceGraphicsController.h>
#include <QWidget>
#include <QComboBox>

class RelationOperationWindow : public QWidget
{
	Q_OBJECT
public:
	explicit RelationOperationWindow(int mode, QWidget *parent = 0);
private:
	QPushButton * submit;
	QPushButton * cancel;
	QGridLayout * l;
	QComboBox * menuEssenceA;
	QComboBox * menuEssenceB;
	QComboBox * menuCordinalityA;
	QComboBox * menuCordinalityB;
	QLabel * col_1;
	QLabel * col_2;
	QLabel * col_3;
	QLabel * col_4;

	int mode = 0;


signals:
	void successRelationOperation(bool);

public slots:
	void setAEssece(QString name);
	void checkSubmossion(bool test);
	void cancelWork(bool );
};

#endif // RELATIONOPERATIONWINDOW_H
