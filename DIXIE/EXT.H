#ifndef _EXT
#define _EXT

/* HEADERS */
#include <time.h>
#include "DIXIE/BASE.H"

/**********/
/* Vec2f */
/**********/
typedef struct Vec2f
{
	float x;
	float y;

} Vec2f;

Vec2f	Vec2fInit(float x, float y);
Vec2f 	Vec2fAdd(Vec2f v, Vec2f s);
Vec2f 	Vec2fSub(Vec2f v, Vec2f s);
Vec2f 	Vec2fMul(Vec2f v, float n);
Vec2f 	Vec2fDiv(Vec2f v, float n);
float 	Vec2fLen(Vec2f v);
Vec2f 	Vec2fNormalize(Vec2f v);
Vec2f 	Vec2fRotate(Vec2f v, Vec2f s, float angle);
float 	Vec2fDot(Vec2f v, Vec2f s);
float 	Vec2fCross(Vec2f v, Vec2f s);

/*********/
/* TIMER */
/*********/
typedef struct Timer
{
	clock_t clock_start;
    clock_t clock_pause;

	byte started;
    byte paused; 

} Timer;

Timer TimerInit();
void TimerStart(Timer *t);
void TimerStop(Timer *t);
void TimerPause(Timer *t);
void TimerResume(Timer *t);
float TimerGet(Timer *t);


#endif