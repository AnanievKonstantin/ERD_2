
#include <QApplication>
#include <EREssenceData.h>
#include <ERRelationsData.h>
#include "EREnums.h"
#include <DataController.h>

int main(int argc, char *argv[])
{
	QApplication appl(argc, argv);

	DataController data;

	QString a = "A";
	int type_a = essence_type::Designation;
	QList<QString> keys_a; keys_a << "ak";
	QList<QString> attrs_a; attrs_a << "aa";


	QString b = "B";
	int type_b = essence_type::Base;
	QList<QString> keys_b; keys_b << "bk";
	QList<QString> attrs_b; attrs_b << "ba";

	QString d = "D";
	int type_d = essence_type::Characteristic;
	QList<QString> keys_d; keys_d << "dk";
	QList<QString> attrs_d; attrs_d << "da";

//	QString x = "X";
//	int type_x = essence_type::Characteristic;
//	QList<QString> keys_x; keys_x << "xk" << "X::bk";
//	QList<QString> attrs_x; attrs_x << "xa";

	QString c = "C";
	int type_c = essence_type::Association;
	QList<QString> keys_c; keys_c << "ck";
	QList<QString> attrs_c; attrs_c << "ca";

//	QString x2 = "X2";
//	int type_x2 = essence_type::Characteristic;
//	QList<QString> keys_x2; keys_x2 << "x2k" << "X2::ASS::bk" <<"X2::ASS::ak";
//	QList<QString> attrs_x2; attrs_x2 << "x2a";

	data.createEssence(a, type_a,keys_a,attrs_a);
	data.createEssence(c, type_c,keys_c,attrs_c);
	data.createEssence(b, type_b,keys_b,attrs_b);
	data.createEssence(d, type_d,keys_d,attrs_d);

//	data.createEssence(x2, type_x2,keys_x2,attrs_x2);


	data.printAllEssence();

//	d.createRelation(id_0, id_1, cordinalyty::ZeroMany, cordinalyty::OneOne);

//	d.printRelations();
//	d.printAllEssence();


	return appl.exec();
}
