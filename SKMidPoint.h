#ifndef MIDPOINT_H
#define MIDPOINT_H

#include "SKPoint.h"

class SKMidPoint : public SKPoint
{
public:
   SKMidPoint(SKFigure *obj1, SKFigure *obj2);

	QRectF boundingRect() const;
	void paint(QPainter *painter,
				  const QStyleOptionGraphicsItem *option,
				  QWidget *widget);
	QPainterPath shape() const;

	virtual NsFigure::objEnum getType();
	virtual NsFigure::objEnum getTypeClass();
	virtual void updateItem();

private:
	SKFigure *p1, *p2;
	qreal w, h;
	QPointF l1, l2;
};

#endif // MIDPOINT_H
