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
		static QString getStrippedProperty(QString nonStrippedProperty);
		static qreal getTableHeightRow();
		static qreal getTableDeltaRow();
	private:
		static qreal tableHeightRow;
		static qreal tableDeltaRow;
};

#endif // SUPPORT_H
