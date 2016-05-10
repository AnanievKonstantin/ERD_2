
#include <QApplication>
#include <widget.h>

int main(int argc, char *argv[])
{
	QApplication appl(argc, argv);
	Widget w;
	w.show();

//	RelationOperationWindow w(1);
//	w.show();


	return appl.exec();
}
