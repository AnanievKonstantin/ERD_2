#ifndef ERESSENCEDATA_H
#define ERESSENCEDATA_H

#include <QString>
#include <QDebug>
#include <QList>
#include "Support.h"

class EREssenceData
{
	public:
		EREssenceData(QString id, int type);
		void print();
		QString getId() const;
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

	private:
		QString id;
		int type;
		QList<QString> attributes;
		QList<QString> keys;
};

#endif // ERESSENCEDATA_H
