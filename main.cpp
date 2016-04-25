
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



	QString a1 = "A1";
	int type_a1 = essence_type::Designation;
	QList<QString> keys_a1; keys_a1 << "a1k";
	QList<QString> attrs_a1; attrs_a1 << "a1a";

	QString b = "B";
	int type_b = essence_type::Base;
	QList<QString> keys_b; keys_b << "bk";
	QList<QString> attrs_b; attrs_b << "ba" << "B::ak";

	QString d = "D";
	int type_d = essence_type::Characteristic;
	QList<QString> keys_d; keys_d << "dk" <<"D::ak";
	QList<QString> attrs_d; attrs_d << "da";

	QString c = "C";
	int type_c = essence_type::Association;
	QList<QString> keys_c; keys_c << "ck" <<"C::ak";
	QList<QString> attrs_c; attrs_c << "ca";

//	QString x2 = "X2";
//	int type_x2 = essence_type::Characteristic;
//	QList<QString> keys_x2; keys_x2 << "x2k" << "X2::ASS::bk" <<"X2::ASS::ak";
//	QList<QString> attrs_x2; attrs_x2 << "x2a";

	data.createEssence(a, type_a,keys_a,attrs_a);
	data.createEssence(c, type_c,keys_c,attrs_c);
	data.createEssence(b, type_b,keys_b,attrs_b);
	data.createEssence(d, type_d,keys_d,attrs_d);

//	data.addKey("D", "XXX");
	data.createRelation("C", "A", cordinalyty::OneOne, cordinalyty::OneOne);
	data.createRelation("D", "A", cordinalyty::OneOne, cordinalyty::OneOne);
	data.createRelation("A", "B", cordinalyty::OneOne, cordinalyty::OneOne);
	data.createRelation("A1", "A", cordinalyty::OneOne, cordinalyty::OneOne);


	data.addKey("A", "ak2");

//	data.createEssence(x2, type_x2,keys_x2,attrs_x2);


	data.printAllEssence();
	data.printRelations();

//	d.createRelation(id_0, id_1, cordinalyty::ZeroMany, cordinalyty::OneOne);

//	d.printRelations();
//	d.printAllEssence();


	return appl.exec();
}
