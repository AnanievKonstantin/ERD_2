#ifndef CONSOLEOUTPUT_H
#define CONSOLEOUTPUT_H

#include <QTextBrowser>

class ConsoleOutput
{
public:
	static ConsoleOutput * getInstance();
	static QTextBrowser * getBrowser();

	static ConsoleOutput * self;
	static void printSystemError(QString error);
	static void printSystemMassage(QString msg);
	static void printUserError(QString error);
	static void printInfo(QString msg);
	static void printInfoList(QString msg, QList<QString> list);

private:
	ConsoleOutput();
	ConsoleOutput(ConsoleOutput const&){}
	ConsoleOutput& operator=(ConsoleOutput const&){}
	static QTextBrowser * browser;
	static unsigned int lineCount;

};

#endif // CONSOLEOUTPUT_H
