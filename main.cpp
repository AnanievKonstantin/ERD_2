
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
	QList<QString> keys_a;
	QList<QString> attrs_a; attrs_a << "aa";

	QString b = "B"; int type_b = essence_type::Base;
	QList<QString> keys_b;
	QList<QString> attrs_b; attrs_b << "ba";

	QString c = "C"; int type_c = essence_type::Base;
	QList<QString> keys_c;
	QList<QString> attrs_c; attrs_c << "ca";

	QString d = "D"; int type_d = essence_type::Base;
	QList<QString> keys_d;
	QList<QString> attrs_d; attrs_d << "da";

	QString e = "E"; int type_e = essence_type::Base;
	QList<QString> keys_e;
	QList<QString> attrs_e; attrs_e << "ea";




	QString des1 = "DES1"; int type_des1 = essence_type::Designation;
	QList<QString> keys_des1;
	QList<QString> attrs_des1; attrs_des1 << "des1a";

	QString char1 = "CHAR1"; int type_char1 = essence_type::Characteristic;
	QList<QString> keys_char1;
	QList<QString> attrs_char1; attrs_char1 << "char1a";

//	QString d1 = "D1"; int type_d1 = essence_type::Designation;
//	QList<QString> keys_d1; keys_d1 << "d1k";
//	QList<QString> attrs_d1; attrs_d1 << "d1a";

//	QString d2 = "D2"; int type_d2= essence_type::Designation;
//	QList<QString> keys_d2; keys_d2 << "d2k";
//	QList<QString> attrs_d2; attrs_d2 << "d2a";

//	QString e1 = "E1"; int type_e1= essence_type::Characteristic;
//	QList<QString> keys_e1; keys_e1 << "e1k";
//	QList<QString> attrs_e1; attrs_e1 << "e1a";

//	QString e2 = "E2"; int type_e2= essence_type::Characteristic;
//	QList<QString> keys_e2; keys_e2 << "e2k";
//	QList<QString> attrs_e2; attrs_e2 << "e2a";

//	QString e3 = "E3"; int type_e3= essence_type::Characteristic;
//	QList<QString> keys_e3; keys_e3 << "e3k";
//	QList<QString> attrs_e3; attrs_e3 << "e3a";

	data.createEssence(a, type_a, keys_a, attrs_a);
	data.createEssence(b, type_b, keys_b, attrs_b);
	data.createEssence(c, type_c, keys_c, attrs_c);
	data.createEssence(d, type_d, keys_d, attrs_d);
	data.createEssence(e, type_e, keys_e, attrs_e);
	data.createEssence(des1, type_des1, keys_des1, attrs_des1);
	data.createEssence(char1, type_char1, keys_char1, attrs_char1);
//	data.createEssence(d1, type_d1, keys_d1, attrs_d1);
//	data.createEssence(d2, type_d2, keys_d2, attrs_d2);
//	data.createEssence(e1, type_e1, keys_e1, attrs_e1);
//	data.createEssence(e2, type_e2, keys_e2, attrs_e2);
//	data.createEssence(e3, type_e3, keys_e3, attrs_e3);

//	data.createRelation("A", "B", cordinalyty::OneMany, cordinalyty::OneMany);

	data.createRelation("A", "C", cordinalyty::OneOne, cordinalyty::OneOne);
//	data.createRelation("B", "D", cordinalyty::OneOne, cordinalyty::OneOne);
//	data.createRelation("B", "A", cordinalyty::OneOne, cordinalyty::OneOne);
//	data.createRelation("A", "C", cordinalyty::OneOne, cordinalyty::OneOne);
//	data.joinBaseToExistAssociation("E", "A<->C",cordinalyty::OneOne);
	data.createRelation("A<->C", "DES1", cordinalyty::OneOne, cordinalyty::OneOne);
	data.createRelation("A<->C", "CHAR1", cordinalyty::OneOne, cordinalyty::OneOne);
	//	data.createRelation("DES1", "A", cordinalyty::OneOne, cordinalyty::OneOne);

	data.addKey("DES1", "key");
	data.removeKey("DES1", "key");

	data.printAllEssence();

//	data.addKey("DES1", "key");
//	data.printAllEssence();
//	data.removeKey("DES1","key");
//	data.printAllEssence();
//	data.createRelation("A<->C", "D", cordinalyty::OneOne, cordinalyty::OneOne);
//	data.createRelation("B","E3", cordinalyty::OneOne, cordinalyty::OneOne);
//	data.joinBaseToExistAssociation("B", "A<->C", cordinalyty::OneMany);

//	data.addKey("D", "D_id");
//	data.removeKey("D", "dk");

	//not work
//	data.removeKey("D1", "d1k");

//	data.createRelation("R", "E1", cordinalyty::OneOne, cordinalyty::OneOne);
//	data.createRelation("C", "E2", cordinalyty::OneOne, cordinalyty::OneOne);
//	data.createRelation("A", "C", cordinalyty::OneOne, cordinalyty::OneOne);
//	data.createRelation("C", "E2", cordinalyty::OneOne, cordinalyty::OneOne);

//	data.createRelation("A", "D2", cordinalyty::OneOne, cordinalyty::OneOne);


//	data.addKey("B", "newBkey");
//	data.addKey("A", "newAkey");


//	data.printRelations();
	data.remove("A<->C", "A");
	data.printAllEssence();
	data.printRelations();


	return appl.exec();
}
