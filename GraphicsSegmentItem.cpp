#include <QDebug>
#include "GraphicsSegmentItem.h"

GraphicsSegmentItem::GraphicsSegmentItem(SKFigure *aStart, SKFigure *aEnd) :
	QGraphicsLineItem(), p1(NULL), p2(NULL)
{
	p1 = aStart;
	p2 = aEnd;

	p1->addChild(this);
	p2->addChild(this);

	setFlags(ItemIsSelectable);
	setZValue(-1);

	setPen(QPen(Qt::darkRed, 2.0));
	updateItem();
}

int GraphicsSegmentItem::type() const
{
	return SKFigure::SegmentType;
}


void GraphicsSegmentItem::updateItem()
{
	qDebug() << "update segment item";
	setLine(QLineF(p1->pos(), p2->pos()));
}



