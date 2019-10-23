#include <QDebug>
#include "SKMidPoint.h"

SKMidPoint::SKMidPoint(SKFigure *obj1, SKFigure *obj2) : SKPoint()
{
   p1 = obj1;
   p2 = obj2;

	p1->addChild(this);
	p2->addChild(this);

	setFlags(ItemIsSelectable);

	setToolTip("MidPoint");
	updateItem();
}

NsFigure::objEnum SKMidPoint::getType()
{
	return NsFigure::MIDPOINT;
}

NsFigure::objEnum SKMidPoint::getTypeClass()
{
	return NsFigure::PCLASS;
}

void SKMidPoint::updateItem()
{
	qDebug() << "update midpoint item";
	QPointF a = p1->scenePos();
	QPointF b = p2->scenePos();
	bool nw = false;
	bool nh = false;

	w = qAbs(a.x()-b.x());
	h = qAbs(a.y()-b.y());
	nw = w < 10; 
	nh = h < 10;

	l1.setX(-w/2);
	l2.setX(w/2);
	if (a.x() < b.x())
	{
		l1.setY(a.y()>b.y()?h/2:-h/2);
		l2.setY(a.y()>b.y()?-h/2:h/2);
	}
	else
	{
		l1.setY(b.y()>a.y()?h/2:-h/2);
		l2.setY(b.y()>a.y()?-h/2:h/2);
	}

	setPos(a.x()+(b.x()-a.x())/2.0, a.y()+(b.y()-a.y())/2.0);

	// todo: what is the sense of the following lines
	if (nw) w = 10.0;
	if (nh) h = 10.0;
}

QRectF SKMidPoint::boundingRect() const
{
   return QRectF(-w/2,-h/2,w,h);
}

void SKMidPoint::paint(QPainter *painter,
							const QStyleOptionGraphicsItem *option,
							QWidget *widget)
{
   qDebug() << "paint midpoint item";
	QBrush brush(Qt::lightGray);
	QPen pen(brush,2,Qt::DashLine);
	QPen penP(Qt::blue);

	painter->setPen(pen);
	painter->drawRect(boundingRect());

	painter->setBrush(QBrush(Qt::yellow));
	painter->setPen(penP);
	painter->drawLine(l1, l2);
	painter->drawEllipse(-5,-5,10,10);
	//SKPoint::paint(painter, option, widget);
}

QPainterPath SKMidPoint::shape() const
{
	QPainterPath path;
	path.addEllipse(-5,-5,10,10);
	return path;
}

