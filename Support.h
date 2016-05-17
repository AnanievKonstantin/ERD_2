#ifndef SUPPORT_H
#define SUPPORT_H
#include <QDebug>
#include "EREnums.h"

class Support
{
	public:
		Support();
		static QString typeToString(int type);
		static QString cardinalityToString(int cordinals);
		static bool checkTypeEssence(int type);
		static bool checkTypeCordinality(int type);

		static QString fontFamilie;
		static int fontSizeEssence;
		static int fontSizeProperty;
};

#endif // SUPPORT_H
