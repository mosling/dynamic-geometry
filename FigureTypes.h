#ifndef FIGURETYPES_H
#define FIGURETYPES_H

#include <QString>

namespace NsFigure
{
	enum objEnum {TCLASS, LCLASS, PCLASS, CCLASS, OBJECT, MULTIFIG,
		POINT, SEGMENT, LINE, RAY, CIRCLE, TEXT, CIRCINT, INTPOINT, MIDPOINT,
		PONLINE, MIRPOINT, DISTPOINT, MIDLINE, PLUMBLINE, PARLINE, HORLINE,
		ALGORITHM, DYNCIRCLE};

	static QString objName[]={"class-of-texts", "class-of-lines",
		"class-of-points", "class-of-circles", "object",
		"multifig", "point", "segment", "line", "ray", "circle", "text",
		"circle-intersection", "intersection-point", "middle-point",
		"point-on-line", "mirror-point", "distance-point", "middle-line",
		"plumb-line", "parallel-line", "horizontal-line", "algorithm",
		"dyn-circle"};

//	static QChar objShort[]={'T', 'L', 'P', 'C', 'O', 'M', 'p', 's',
//		'l', 'r', 'c', 't', '_', 'i', '_', '_', '_', 'd', '_', '_', '_', 'h',
//		'a', '_' };

}

#endif // FIGURETYPES_H
