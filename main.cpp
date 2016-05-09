
#include <QApplication>
#include <widget.h>

int main(int argc, char *argv[])
{
	QApplication appl(argc, argv);
	Widget w;
	w.show();



	return appl.exec();
}
