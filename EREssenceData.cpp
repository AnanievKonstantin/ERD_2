#include "EREssenceData.h"

EREssenceData::EREssenceData(QString id, int type)
{
	this->id = id;
	this->type = type;
}

void EREssenceData::print()
{
	qDebug() << "Essence: " << id;
	qDebug() << "\tType: " << Support::typeToString(getType());
	qDebug() << "\tkeys: " << keys;
	qDebug() << "\tattributes: " << attributes;
}

QString EREssenceData::getId() const
{
	return id;
}

QString &EREssenceData::getNonConstId()
{
	return id;
}

void EREssenceData::setId(const QString & value)
{
	id = value;
}

int EREssenceData::getType() const
{
	return type;
}

void EREssenceData::setType(const int value)
{
	type = value;
}

QList<QString> & EREssenceData::getAttributes()
{
	return attributes;
}

void EREssenceData::setAttributes(const QList<QString> & value)
{
	this->attributes = value;
}

QList<QString> & EREssenceData::getKeys()
{
	return this->keys;
}

void EREssenceData::setKeys(const QList<QString> & value)
{
	this->keys = value;
}

bool EREssenceData::addAtribute(QString attr)
{
	this->attributes.append(attr);
}

bool EREssenceData::addKey(QString key)
{
	if(keys.contains(key) == true)
	{
		return false;
	}

	if(attributes.contains(key) == true)
	{
		return false;
	}

	keys.append(key);
	return true;
}

void EREssenceData::removeKey(QString key)
{
	keys.removeOne(key);
}

bool EREssenceData::removeAttributeWithSubStr(QString attr)
{
	foreach (QString a, attributes)
	{
		if(a.lastIndexOf(attr) != -1)
		{
			attributes.removeOne(a);
			return true;
		}
	}

	return false;
}

QList<QString> EREssenceData::getKeysConst()
{
	return this->keys;
}

QList<QString> EREssenceData::getAttrsConst()
{
	return this->attributes;
}

void EREssenceData::read(const QJsonObject &json)
{
	type = json["type"].toInt();
	id = json["id"].toString();
	QJsonArray jattrs = json["attrs"].toArray();
	QJsonArray jkeys = json["keys"].toArray();

	for(int i = 0; i < jattrs.size(); i++)
	{
		attributes.append(jattrs[i].toString());
	}

	for(int i = 0; i < jkeys.size(); i++)
	{
		keys.append(jkeys[i].toString());
	}
}

void EREssenceData::write(QJsonObject &json) const
{
	QJsonArray jattrs;
	QJsonArray jkeys;

	json["id"] = id;
	json["type"] = type;
	foreach (QString key, keys)
	{
		jkeys.append(key);
	}

	foreach (QString attr, attributes)
	{
		jattrs.append(attr);
	}
	json["keys"] = jkeys;
	json["attrs"] = jattrs;
}
































