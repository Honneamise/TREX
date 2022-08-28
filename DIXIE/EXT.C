/* HEADERS */
#include <math.h>
#include <time.h>

#include "DIXIE/BASE.H"
#include "DIXIE/EXT.H"

/*********/
/* VEC2F */
/*********/
Vec2f Vec2fInit(float x, float y)
{
    Vec2f t = {0};

    t.x = x;
    t.y = y;

    return t;
}

/**********/
Vec2f Vec2fAdd(Vec2f v, Vec2f s)
{
	Vec2f t = {0};

	t.x = v.x + s.x;
	t.y = v.y + s.y;

	return t;
}

/**********/
Vec2f Vec2fSub(Vec2f v, Vec2f s)
{
    Vec2f t = {0};

    t.x = v.x - s.x;
    t.y = v.y - s.y;
	
    return t; 
}

/**********/
Vec2f Vec2fMul(Vec2f v, float n)
{
    Vec2f t = {0};

    t.x = v.x * n;
    t.y = v.y * n;

	return t;
}

/**********/
Vec2f Vec2fDiv(Vec2f v, float n)
{
    Vec2f t = {0};

    t.x = v.x / n;
    t.y = v.y / n;

	return t;
}

/**********/
float Vec2fLen(Vec2f v)
{
	float val = (v.x * v.x) + (v.y * v.y);

	return (float)sqrt(val);
}

/**********/
Vec2f Vec2fNormalize(Vec2f v)
{
    Vec2f t = {0};

	float m = Vec2fLen(v);

	if (m != 0.0f) { return Vec2fDiv(v, m); };

    return t;
}

/**********/
Vec2f Vec2fRotate(Vec2f v, Vec2f s, float angle)
{
    Vec2f t = {0};

	float x = v.x - s.x;
	float y = v.y - s.y;
	float radians = Radiansf(-angle);

	float _x = s.x + x * cos(radians) - y * sin(radians);
	float _y = s.y + x * sin(radians) + y * cos(radians);

    t.x = _x;
    t.y = _y;
	
    return t;
}

/**********/
float Vec2fDot(Vec2f v, Vec2f s)
{
	return (v.x * s.x) + (v.y * s.y);
}

/**********/
float Vec2fCross(Vec2f v, Vec2f s)
{
	return (v.x * s.y) - (v.y * s.x);
}

/*********/
/* TIMER */
/*********/
Timer TimerInit()
{
	Timer t = {0};

	return t;
}

/**********/
void TimerStart(Timer *t)
{
	t->clock_start = clock();
    t->clock_pause = 0;

    t->started = 1;
    t->paused = 0;
}

/**********/
void TimerStop(Timer *t)
{
	t->clock_start = 0;
    t->clock_pause = 0;
    
	t->started = 0;
    t->paused = 0;
}

/**********/
void TimerPause(Timer *t)
{
    if(t->started && !t->paused)
    {    
        t->clock_pause = clock() - t->clock_start;
        t->clock_start = 0;

		t->paused = 1;
    }
}

/**********/
void TimerResume(Timer *t)
{
    if(t->started && t->paused)
    {
		t->clock_start = clock() - t->clock_pause;
		t->clock_pause = 0;
        
		t->paused = 0;
	}
}

/**********/
float TimerGet(Timer *t)
{
    float _t = 0;

    if(t->started)
    {
        if(t->paused) { _t = t->clock_pause/CLK_TCK; }
        else { _t = (clock() - t->clock_start)/CLK_TCK; }
    }

    return _t;
}
