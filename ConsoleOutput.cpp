#include "ConsoleOutput.h"

ConsoleOutput	*	ConsoleOutput::self			= nullptr;
QTextBrowser	*	ConsoleOutput::browser		= nullptr;
unsigned int				ConsoleOutput::lineCount	= 0;

ConsoleOutput *ConsoleOutput::getInstance()
{
	if(self == nullptr)
	{
		self = new ConsoleOutput();
		return self;
	}

	return self;
}

QTextBrowser *ConsoleOutput::getBrowser()
{
	if(self == nullptr)
	{
		getInstance();
	}

	return browser;
}

void ConsoleOutput::printSystemError(QString error)
{
	QString num = QString::number(lineCount);
	browser->append("<p style=font-weight:bold;><font color= purple  face= Arial>" + num +": "+ error + "</font></p>");
	lineCount++;
}

ConsoleOutput::ConsoleOutput()
{
	browser = new QTextBrowser;
}

void ConsoleOutput::printSystemMassage(QString msg)
{
	QString num = QString::number(lineCount);
	browser->append("<p style=font-weight:bold;><font color = orange  face= Arial >" + num +": "+msg + "</font></p>");
	lineCount++;
}

void ConsoleOutput::printUserError(QString error)
{
	QString num = QString::number(lineCount);
	browser->append("<p><font color= red  face= Arial>" + num +": "+ error + "</font></p>");
	lineCount++;
}

void ConsoleOutput::printStartActionInfo(QString info)
{
	QString num = QString::number(lineCount);
	browser->append("<p><font color= green  face= Arial>" + num +": "+ info + "</font></p>");
	lineCount++;
}

void ConsoleOutput::printInfo(QString msg)
{
	QString num = QString::number(lineCount);
	browser->append("<p><font color= black  face= Arial>" + num +": "+ msg + "</font></p>");
	lineCount++;
}

void ConsoleOutput::printInfoList(QString msg, QList<QString> list)
{
	QString num = QString::number(lineCount);
	QString string_list;
	foreach (QString s, list)
	{
		string_list = string_list + ", " + s;
	}

	browser->append("<p><font color= black  face= Arial>" + num +": "+ msg + " " + string_list + "</font></p>");
	lineCount++;
}

























