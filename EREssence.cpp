#include "EREssence.h"

EREssence::EREssence(EREssenceData *data, QGraphicsWidget * parent):QGraphicsWidget(parent)
{
	if(data == nullptr)
	{
		qDebug("ERROR SETTING ESSENCE DATA");
		exit(10);
	}
	this->data = data;
}


QString EREssence::getId() const
{
	return data->getId();
}

QString EREssence::getIdWithoutPath() const
{

	QString name = data->getId();
	QString id = name.right(name.length() - name.lastIndexOf(":") - 1);
	return id;
//	return data->getId();
}


QString &EREssence::getNonConstId()
{
	return data->getNonConstId();
}

void EREssence::addArrow(Arrow * arrow)
{
	arrows.append(arrow);
}

QVariant EREssence::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant & value)
{
	if (change == QGraphicsItem::ItemPositionChange) {
		foreach (Arrow *a, arrows) {
			a->updatePosition();
		}
	}
//	static int i = 0;
//	qDebug() <<id<<" "<<i <<"\n";
//	i++;
	return value;
}

void EREssence::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
{
	QString id = getId();
	emit edit(id);
}

void EREssence::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QString id = getId();
	emit focued(id);

}

int EREssence::getType() const
{
	return data->getType();
}

QList<QString> EREssence::getAttrs()
{
	return data->getAttrsConst();
}

QList<QString> EREssence::getKeys()
{
	return data->getKeysConst();
}

//void EREssence::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
//{
//	qDebug("void EREssence::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)");
//}

//void EREssence::mousePressEvent(QGraphicsSceneMouseEvent * event)
//{
//	qDebug("void EREssence::mousePressEvent(QGraphicsSceneMouseEvent * event)");
//}

//void EREssence::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)
//{
//	qDebug("void EREssence::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)");
//}


