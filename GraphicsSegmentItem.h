#ifndef GRAPHICSSEGMENTITEM_H
#define GRAPHICSSEGMENTITEM_H

#include <QGraphicsLineItem>
#include <QLineF>
#include "SKFigure.h"

class GraphicsSegmentItem : public QGraphicsLineItem, SKFigure
{
public:
	explicit GraphicsSegmentItem(SKFigure *aStart,
										  SKFigure *aEnd);

	void updateItem();
	int type() const;

private:
	SKFigure *p1, *p2;

};

#endif // GRAPHICSSEGMENTITEM_H
