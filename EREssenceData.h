#ifndef ERESSENCEDATA_H
#define ERESSENCEDATA_H

#include <QString>
#include <QDebug>
#include <QList>
#include "Support.h"
#include <QJsonArray>
#include <QJsonObject>

class EREssenceData
{
	public:
		EREssenceData(QString id, int type);
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

		void read(const QJsonObject &json);
		void write(QJsonObject &json) const;

	private:
		QString id;
		int type;
		QList<QString> attributes;
		QList<QString> keys;
};

#endif // ERESSENCEDATA_H
