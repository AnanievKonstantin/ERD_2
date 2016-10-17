#include "EREssenceBase.h"


EREssenceBase::EREssenceBase(EREssenceData *data, QGraphicsWidget * parent):EREssence(data, parent)
{

//	QAction* zorderAct= new QAction(tr("bring to front"), this);
//	connect(zorderAct, SIGNAL(triggered()), this, SLOT(itemZorder()));
//	addAction(zorderAct);
//	setContexMenuPolicy(Qt::ActionsContextMenu);
	initEssence();
}


void EREssenceBase::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QLinearGradient linearGradient(QPointF(size().width()/4, -size().height()), QPointF(40, 40));
	linearGradient.setColorAt(0, Qt::blue);
	linearGradient.setColorAt(1, Qt::white);

	QPen penOutLine(Qt::black, 1);
	painter->setBrush(*(new QBrush(linearGradient)));
	painter->setPen(penOutLine);

	if (isSelected())
	{
		painter->setPen(QPen(QColor(0,255,100), 2, Qt::DashLine));
	}
	painter->drawRect(0,0,size().width(),size().height());

	QPen pen(QColor(0,0,0));
	painter->setPen(pen);
	painter->setFont(QFont(Support::fontFamilie, Support::fontSizeEssence));
	painter->drawText(0,0,size().width(),50,Qt::AlignCenter,getIdWithoutPath());

//	painter->save() ;
//	painter->setPen(Qt::red) ;
//	painter->setBrush(Qt::NoBrush) ;
//	painter->drawRect(boundingRect()) ;
//	painter->restore() ;
}

QRectF EREssenceBase::boundingRect() const
{
    qreal x = 0;
    qreal y = 0;
    qreal w = this->size().width();
    qreal h = this->size().height();
	return QRectF(x,y, w,h);
}

QPolygonF EREssenceBase::getPolygon()
{
	return QPolygonF() << QPointF(pos().x(),pos().y() + size().height()/2) << QPointF(pos().x() + size().width()/2,pos().y())
					   << QPointF(pos().x() + size().width(),pos().y() + size().height()/2)
					   << QPointF(pos().x() + size().width()/2, pos().y() + size().height())
					   << QPointF(pos().x(),pos().y() + size().height()/2);
}

QPainterPath EREssenceBase::shape() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

void EREssenceBase::initEssence()
{
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
	setGeometry(0,0,180,50);
//	qDebug() << this->pos() <<"\n";
//	qDebug() << this->size() <<"\n";


}

//void EREssenceBase::contextMenuEvent(QContextMenuEvent * event)
//{
//	scene()->clearSelection();
//	scene()->clearSelection();
//	topMenu->exec(event->globalPos());
//}




EREssenceBase::~EREssenceBase()
{
}
