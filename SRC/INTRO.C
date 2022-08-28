/* HEADERS */
#include <string.h>

#include "DIXIE/CORE.H"
#include "DIXIE/EXT.H"

#include "SRC/UNIT.H"
#include "SRC/STATE.H"
#include "SRC/MANAGER.H"
#include "SRC/GAME.H"

/* VARS */
static int CHANGE = 0;
static int DRAW = 1;

static int IMAGE_INDEX = 2;
static Timer IMAGE_TIMER = {0};

static int SONG_INDEX = 2;
static int SONG_LEN = 16;
static int SONG[16] =
{
	P, E, E, F, F_, F_, A, F_, A, F_, F_, F, E, B, E, E
};

/**********/
void IntroReset()
{
	CHANGE = 0;

	DRAW = 1;

	IMAGE_INDEX = 2;

	SONG_INDEX = 0;	
	
	TimerStart(&IMAGE_TIMER);
}

/**********/
void IntroInit()
{
	IMAGE_TIMER = TimerInit();
	TimerStart(&IMAGE_TIMER);
}

/*********/
void IntroClose()
{

}

/**********/
void IntroInput()
{
    if(kbhit())
	{
        switch (getch())
		{
			case 27:
				CHANGE = 1;
				StopSound();
				SM_Stop();
				break;

			default:
				CHANGE = 1;
				StopSound();
				GameReset();
				SM_Push(STATE_GAME);
				break;
        }
    }
}

/*********/
void IntroUpdate()
{
	if(!CHANGE && !SoundPlaying())
	{
		Sound(SONG[SONG_INDEX], 0.25f);
		SONG_INDEX++;
		if(SONG_INDEX>=SONG_LEN){ SONG_INDEX=0; }
	}

	if(TimerGet(&IMAGE_TIMER)>1.5f)
	{
		IMAGE_INDEX++;
		if(IMAGE_INDEX>=ManagerSize()){ IMAGE_INDEX = 2; }
		TimerStart(&IMAGE_TIMER);

		DRAW = 1;
	}
}

/**********/
void IntroDraw()
{
	if(DRAW)
	{
		Clear(COLOR_0);

		Color(COLOR_3);
		
		String("The best programming language", WIDTH/2-(30*8)/2, HEIGHT/4);

		String("Made for the TREX RPI Game Jam by Honny.", 0, HEIGHT-16);

		ImageMask( ManagerGet(IMAGE_INDEX), 32, 32, WIDTH/2-16, HEIGHT/2-16, COLOR_0);

		DRAW = 0;
	}

	Update();
}
