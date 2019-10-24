#include <QDebug>
#include "SKFigure.h"

SKFigure::SKFigure() :  QGraphicsItem(), removingChild(NULL)
{
	setFlag(ItemIsMovable);
	setFlag(ItemIsSelectable);
	setFlag(ItemSendsGeometryChanges);

    baseFigureSet = new QSet<SKFigure*>;
    dependentFigureSet = new QSet<SKFigure*>;

	setToolTip("BaseFigure");
}

SKFigure::~SKFigure()
{
    foreach (SKFigure *p, *dependentFigureSet)
	{
        p->removeDependent(this);
	}

	//! Jetzt koennen die Kinder geloescht werden, da diese
	//! sich auch aus den Mengen childs entfernen wollen, muessen
	//! wir dies an dieser Stelle verhindern.
    foreach (SKFigure *c, *baseFigureSet)
	{
		removingChild = c;
		delete c;
	}
    removingChild = nullptr;

    delete baseFigureSet;
    delete dependentFigureSet;
}

void SKFigure::addBaseFigure(SKFigure *child)
{
    baseFigureSet->insert(child);
    child->addDependentFigure(this);
}

void SKFigure::removeDependent(SKFigure *child)
{
	if (child != removingChild)
	{
        baseFigureSet->remove(child);
	}
}

void SKFigure::addDependentFigure(SKFigure *parent)
{
    dependentFigureSet->insert(parent);
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
        foreach(SKFigure *child, *baseFigureSet)
		{
			child->updateItem();
			child->itemChange(change, value);
		}
	}

	return QGraphicsItem::itemChange(change, value);
}
