/* HEADERS */
#include "DIXIE/CORE.H"

#include "SRC/UNIT.H"

/**********/
void UnitDraw(Unit *u)
{
	if(u->img)
	{
		ImageMask(u->img, u->img_w, u->img_h, u->pos.x - u->img_w/2, u->pos.y - u->img_h/2, COLOR_0);
	}
	else
	{
		RectangleFill(u->pos.x - u->img_w/2, u->pos.y - u->img_h/2, u->img_w, u->img_h);
	}
}

/**********/
void UnitUpdate(Unit *u)
{
	u->pos = Vec2fAdd(u->pos, u->speed);
}