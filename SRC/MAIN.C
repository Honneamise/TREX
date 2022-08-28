/* HEADERS */
#include "DIXIE/CORE.H"

#include "SRC/MANAGER.H"
#include "SRC/STATE.H"
#include "SRC/INTRO.H"
#include "SRC/GAME.H"
#include "SRC/OVER.H"

#include <stdio.h>

/* MAIN */
int main()
{
	State intro = {0};
	State game = {0};
	State over = {0};

	Init();

	SM_Init();

	ManagerInit("RES/RES.TXT");

	intro = StateInit( STATE_INTRO, IntroInit, IntroClose, IntroInput, IntroUpdate, IntroDraw);
	game = StateInit( STATE_GAME, GameInit, GameClose, GameInput, GameUpdate, GameDraw);
	over = StateInit( STATE_OVER, OverInit, OverClose, OverInput, OverUpdate, OverDraw);


    SM_Add(&intro);
    SM_Add(&game);
	SM_Add(&over);

	SM_Push(STATE_INTRO);

	SM_Start();

	ManagerClose();

	SM_Close();

	Close();

	return 0;
}
