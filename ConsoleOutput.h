#ifndef CONSOLEOUTPUT_H
#define CONSOLEOUTPUT_H

#include <QTextBrowser>

/**
 * @brief The ConsoleOutput class
 * Консоль, описываеь функции вывода на консоль сообщений. От функции зависит цвет сообщения
 *
 *
 */
class ConsoleOutput
{
public:
	static ConsoleOutput * getInstance();
	static QTextBrowser * getBrowser();
	static ConsoleOutput * self;

	static void printSystemError(QString error);
	static void printSystemMassage(QString msg);
	static void printUserError(QString error);
	static void printStartActionInfo(QString info);
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
