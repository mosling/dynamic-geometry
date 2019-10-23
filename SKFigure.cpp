#include <QDebug>
#include "SKFigure.h"

SKFigure::SKFigure() :  QGraphicsItem(), removingChild(NULL)
{
	setFlag(ItemIsMovable);
	setFlag(ItemIsSelectable);
	setFlag(ItemSendsGeometryChanges);

	childs = new QSet<SKFigure*>;
	parents = new QSet<SKFigure*>;

	setToolTip("BaseFigure");
}

SKFigure::~SKFigure()
{
	// zuerst wird das Objekt aus Vaterobjekten entfernt

	qDebug() << "deleting object " << this->toolTip();
	foreach (SKFigure *p, *parents)
	{
		qDebug() << "remove from child " << p->toolTip();
		p->removeChild(this);
	}

	//! Jetzt können die Kinder gelöscht werden, da diese
	//! sich auch aus den Mengen childs entfernen wollen, müssen
	//! wir dies an dieser Stelle verhindern.
	foreach (SKFigure *c, *childs)
	{
		qDebug()<<"start child removing " << c->toolTip() << "{";
		removingChild = c;
		delete c;
		qDebug()<< "}";

	}
	removingChild = NULL;

	delete childs;
	delete parents;
}

void SKFigure::addChild(SKFigure *child)
{
	childs->insert(child);
	child->addParent(this);
}

void SKFigure::removeChild(SKFigure *child)
{
	if (child != removingChild)
	{
		childs->remove(child);
	}
}

void SKFigure::addParent(SKFigure *parent)
{
	parents->insert(parent);
}

void SKFigure::updateItem()
{
	qDebug() << "change useless base element";
}

QVariant SKFigure::itemChange(QGraphicsItem::GraphicsItemChange change,
													const QVariant &value)
{
   if (change == ItemPositionHasChanged && scene() )
	{
		foreach(SKFigure *child, *childs)
		{
			child->updateItem();
			child->itemChange(change, value);
		}
	}

	return QGraphicsItem::itemChange(change, value);
}

NsFigure::objEnum SKFigure::getType()
{
	return NsFigure::OBJECT;
}

NsFigure::objEnum SKFigure::getTypeClass()
{
	return NsFigure::OBJECT;
}

