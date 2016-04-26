
#include <QApplication>
#include <EREssenceData.h>
#include <ERRelationsData.h>
#include "EREnums.h"
#include <DataController.h>

int main(int argc, char *argv[])
{
	QApplication appl(argc, argv);

	DataController data;

	QString a = "A"; int type_a = essence_type::Base;
	QList<QString> keys_a; keys_a << "ak";
	QList<QString> attrs_a; attrs_a << "aa";

	QString b = "B"; int type_b = essence_type::Base;
	QList<QString> keys_b; keys_b << "bk";
	QList<QString> attrs_b; attrs_b << "ba";

	QString c = "C"; int type_c = essence_type::Base;
	QList<QString> keys_c; keys_c << "ck";
	QList<QString> attrs_c; attrs_c << "ca";

	QString r = "R"; int type_r = essence_type::Association;
	QList<QString> keys_r; keys_r << "rk";
	QList<QString> attrs_r; attrs_r << "ra";

	QString d = "D"; int type_d = essence_type::Designation;
	QList<QString> keys_d; keys_d << "dk" <<"dk2";
	QList<QString> attrs_d; attrs_d << "da";

	QString d1 = "D1"; int type_d1 = essence_type::Designation;
	QList<QString> keys_d1; keys_d1 << "d1k";
	QList<QString> attrs_d1; attrs_d1 << "d1a";

	QString d2 = "D2"; int type_d2= essence_type::Designation;
	QList<QString> keys_d2; keys_d2 << "d2k";
	QList<QString> attrs_d2; attrs_d2 << "d2a";

	QString e1 = "E1"; int type_e1= essence_type::Characteristic;
	QList<QString> keys_e1; keys_e1 << "e1k";
	QList<QString> attrs_e1; attrs_e1 << "e1a";

	QString e2 = "E2"; int type_e2= essence_type::Characteristic;
	QList<QString> keys_e2; keys_e2 << "e2k";
	QList<QString> attrs_e2; attrs_e2 << "e2a";

	QString e3 = "E3"; int type_e3= essence_type::Characteristic;
	QList<QString> keys_e3; keys_e3 << "e3k";
	QList<QString> attrs_e3; attrs_e3 << "e3a";

	data.createEssence(a, type_a, keys_a, attrs_a);
	data.createEssence(b, type_b, keys_b, attrs_b);
	data.createEssence(c, type_c, keys_c, attrs_c);
	data.createEssence(d, type_d, keys_d, attrs_d);
	data.createEssence(r, type_r, keys_r, attrs_r);
	data.createEssence(d1, type_d1, keys_d1, attrs_d1);
	data.createEssence(d2, type_d2, keys_d2, attrs_d2);
	data.createEssence(e1, type_e1, keys_e1, attrs_e1);
	data.createEssence(e2, type_e2, keys_e2, attrs_e2);
	data.createEssence(e3, type_e3, keys_e3, attrs_e3);

//	data.createRelation("A", "B", cordinalyty::OneMany, cordinalyty::OneMany);

	data.createRelation("A", "C", cordinalyty::OneOne, cordinalyty::OneOne);
	data.createRelation("D1", "C", cordinalyty::OneOne, cordinalyty::OneOne);
	data.createRelation("A<->C", "E1", cordinalyty::OneOne, cordinalyty::OneOne);
	data.createRelation("A<->C", "D", cordinalyty::OneOne, cordinalyty::OneOne);
	data.createRelation("B","E3", cordinalyty::OneOne, cordinalyty::OneOne);
	data.joinBaseToExistAssociation("B", "A<->C", cordinalyty::OneMany);

	data.removeKey("D", "dk2");
	data.removeKey("D", "dk");

	//not work
	data.removeKey("D1", "d1k");

//	data.createRelation("R", "E1", cordinalyty::OneOne, cordinalyty::OneOne);
//	data.createRelation("C", "E2", cordinalyty::OneOne, cordinalyty::OneOne);
//	data.createRelation("A", "C", cordinalyty::OneOne, cordinalyty::OneOne);
//	data.createRelation("C", "E2", cordinalyty::OneOne, cordinalyty::OneOne);

//	data.createRelation("A", "D2", cordinalyty::OneOne, cordinalyty::OneOne);


//	data.addKey("B", "newBkey");
//	data.addKey("A", "newAkey");


	data.printAllEssence();
	data.printRelations();



	return appl.exec();
}
