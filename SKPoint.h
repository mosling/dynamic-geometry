#ifndef GRAPHICSPOINTITEM_H
#define GRAPHICSPOINTITEM_H

#include <QSet>
#include "SKFigure.h"


class SKPoint : public SKFigure
{
public:
	explicit SKPoint();
	~SKPoint();

	virtual NsFigure::objEnum getType();
	virtual NsFigure::objEnum getTypeClass();

	QRectF boundingRect() const;
	void paint(QPainter *painter,
				  const QStyleOptionGraphicsItem *option,
				  QWidget *widget);
   void setRadius(qreal aRadius);

private:
   qreal radius;

};

#endif // QGRAPHICSPOINTITEM_H
