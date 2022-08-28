#ifndef UNIT_H
#define UNIT_H

/* HEADERS */
#include "DIXIE/BASE.H"
#include "DIXIE/EXT.H"

typedef struct Unit
{
	Vec2f pos;
	Vec2f speed;

	int img_w;
	int img_h;
	byte *img;

} Unit;

void UnitDraw(Unit *u);

void UnitUpdate(Unit *u);

#endif