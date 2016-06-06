#ifndef ERESSENCEDATA_H
#define ERESSENCEDATA_H

#include <QString>
#include <QDebug>
#include <QList>
#include "Support.h"
#include <QJsonArray>
#include <QJsonObject>

/**
 * @brief The EREssenceData class
 *	Описывает класс инкапсулиреющий описание данных сущности диаграммы
 */
class EREssenceData
{
	public:
		EREssenceData(QString id, int type);

		//debug print in to termimal
		void print();

		QString getId() const;
		QString & getNonConstId();
		void setId(const QString & value);

		int getType() const;
		void setType(const int value);

		QList<QString> & getAttributes();
		void setAttributes(const QList<QString> & value);

		QList<QString> & getKeys();
		void setKeys(const QList<QString> & value);

		bool addAtribute(QString attr);
		bool addKey(QString key);

		void removeKey(QString key);

		bool removeAttributeWithSubStr(QString attr);

		QList<QString> getKeysConst();
		QList<QString> getAttrsConst();

		/**
		 * @brief read
		 *	считывает из json
		 * @param json
		 *	данные об объекте в формате json
		 */
		void read(const QJsonObject &json);

		/**
		 * @brief write
		 *	записывает  в json
		 * @param json
		 *	данные об объекте в формате json
		 */
		void write(QJsonObject &json) const;

	private:

		/**
		 * @brief id имя сущности
		 */
		QString id;

		/**
		 * @brief type
		 *	тип сущности из essence_type
		 */
		int type;

		/**
		 * @brief attributes
		 *	список атрбутов сущности
		 */
		QList<QString> attributes;

		/**
		 * @brief keys
		 *	список ключей сущности
		 */
		QList<QString> keys;
};

#endif // ERESSENCEDATA_H
