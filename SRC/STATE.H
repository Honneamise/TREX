#ifndef STATE_H
#define STATE_H

/* HEADERS */
#include "DIXIE/BASE.H"

/*********/
/* STATE */
/*********/
typedef struct State
{
	int code;

	void(*init)();
    void(*close)();

    void(*update)();
	void(*input)();
	void(*draw)();

}State;

State StateInit(int code, void(*init)(), void(*close)(), void(*update)(), void(*input)(), void(*draw)() );

void StateClose(State *state);


/*****************/
/* STATE MANAGER */
/*****************/
typedef struct StateManager
{
    int run;
    State *push;
    State *pop;
    Array states;
    Stack stack;

}StateManager;

void SM_Init();

void SM_Close();

void SM_Add(State *st);

void SM_Push(int code);

void SM_Pop();

void SM_Start();

void SM_Stop();

#endif