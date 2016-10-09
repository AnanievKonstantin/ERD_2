#ifndef SUPPORT_H
#define SUPPORT_H
#include <QDebug>
#include "EREnums.h"

/**
 * @brief The Support class
 *	хранит настройки и выполняет часто повторяющиеся операции по преобразования строк
 */
class Support
{
	public:
		Support();

		/**
		 * @brief typeToString
		 *	преобразует тип в строку
		 * @param type
		 *	тип сущности
		 * @return
		 *	строка с именем типа
		 */
		static QString typeToString(int type);

		/**
		 * @brief cardinalityToString
		 *	преобразует тип кардинальности в строку
		 * @param cordinals
		 *	кардинальность
		 * @return
		 *	строка с кардинальностью
		 */
		static QString cardinalityToString(int cordinals);

		/**
		 * @brief checkTypeEssence
		 *	проверяет корректность типа сущности
		 * @param type
		 *	тип сущности
		 * @return
		 *	true да тип сущности корректен
		 *	false нет тип сущности не корректен
		 */
		static bool checkTypeEssence(int type);

		/**
		 * @brief checkTypeCordinality
		 *	проверяет корректность типа свойства
		 * @param type
		 *	тип свойства
		 * @return
		 *	true да тип свойства корректен
		 *	false нет тип свойства не корректен
		 */
		static bool checkTypeCordinality(int type);

		/**
		 * @brief fontFamilie
		 *	вернёт шрифт для сущностей
		 */
		static QString fontFamilie;

		/**
		 * @brief getStrippedProperty
         *	вёрнёт имя свойства без системного пути (без знака :)
         *  before
         *   property == hell_key:entytyA:A:Master:key
         *  after
         *   property == key
         * @param nonStrippedProperty
		 *	имя свойства с системным путём
		 * @return
		 * имя свойства без системного пути
		 */
        static QString getStrippedProperty(const QString &nonStrippedProperty);

		/**
		 * @brief getTableHeightRow
		 * @return ширину таблиц в Data модели
		 */
		static qreal getTableHeightRow();

		/**
		 * @brief getTableDeltaRow
		 * @return вернёт дельту между строками в Data модели
		 */
		static qreal getTableDeltaRow();

		static int fontSizeProperty;
		static int fontSizeEssence;
	private:
		static qreal tableHeightRow;
		static qreal tableDeltaRow;
};

#endif // SUPPORT_H
