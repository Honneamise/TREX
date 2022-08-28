/* HEADERS */
#include <stdlib.h>
#include <string.h>

#include "SRC/STATE.H"

/* VARS */
static StateManager SM = {0};

/*********/
/* STATE */
/*********/
State StateInit(int code, void(*init)(), void(*close)(), void(*input)(), void(*update)(), void(*draw)() )
{
	State st = {0};

	st.code = code;
	st.init = init;
	st.close = close;
	st.input = input;
	st.update = update;
	st.draw = draw;
    
	return st;
}

/*********/
void StateClose(State *state)
{
    state->close();

	state->code = -1;
	state->init = NULL;
	state->close = NULL;
	state->input = NULL;
	state->update = NULL;
	state->draw = NULL;
}

/*****************/
/* STATE MANAGER */
/*****************/
void SM_Init()
{
	SM.run = 0;
    SM.push = NULL;
    SM.pop = NULL; 
    ArrayInit(&SM.states);
	StackInit(&SM.stack);
}

/**********/
void SM_Close()
{
	SM.run = 0;
	SM.push = NULL;
    SM.pop = NULL; 

	ArrayClose(&SM.states, (void (*)(void *))StateClose );
	StackClose(&SM.stack,NULL);
}

/**********/
void SM_Add(State *st)
{	
	int i = 0;

	for(i=0;i<SM.states.elems_count;i++)
	{
		if( ((State*)(SM.states.elems[i]))->code == st->code)
		{
			return;
		}
	}

	st->init();

	ArrayAdd(&SM.states,st);
}

/**********/
void SM_Push(int code)
{
	int i = 0;

	for(i=0;i<SM.states.elems_count;i++)
	{
		if( ((State*)(SM.states.elems[i]))->code == code)
		{
			SM.push = (State*)(SM.states.elems[i]);
			return;
		}
	}
}

/**********/
void SM_Pop()
{
	SM.pop = StackPeek(&SM.stack);
}


/**********/
void SM_Start()
{
	State *state = NULL;

	SM.run = 1;

    while(SM.run)
	{
		if(SM.push)
		{
			StackPush(&SM.stack,SM.push);
			SM.push = NULL;
		}

		if(SM.pop)
		{
			StackPop(&SM.stack);
			SM.pop = NULL;
		}

    	state = StackPeek(&SM.stack);

		if(state)
		{
			if(state->input) { state->input(); };

			if(state->update) { state->update(); };

			if(state->draw) { state->draw(); };

		}
		else
		{ 
			SM.run=0; 
		}
	
	}
}

/**********/
void SM_Stop()
{
	SM.run = 0;
}