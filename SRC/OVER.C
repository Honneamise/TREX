/* HEADERS */
#include <stdlib.h>

#include "DIXIE/CORE.H"

#include "SRC/STATE.H"
#include "SRC/GAME.H"
#include "SRC/MANAGER.H"

/* VARS */
static int CHANGE = 0;
static int DRAW = 1;

static int SONG_INDEX = 0;
static int SONG_LEN = 14;
static int SONG[14] =
{
	P, E, A, 2280, B, A, 2280, A, B, A, F, G, E, E
};

static byte *phaze = 0;
static int phaze_w = 140;
static int phaze_h = 180;

/**********/
void OverReset()
{
	CHANGE = 0;

	DRAW = 1;

	SONG_INDEX = 0;
}

/**********/
void OverInit()
{
	phaze = ManagerGet(1);
}

/*********/
void OverClose()
{

}

/**********/
void OverInput()
{
    if(kbhit())
	{
        switch (getch())
		{
			default:
				CHANGE = 1;
				StopSound();
				GameReset();
				SM_Pop();
				break;
        }
    }
}

/*********/
void OverUpdate()
{
	/* update current note */
	if(!CHANGE && !SoundPlaying())
	{
		Sound(SONG[SONG_INDEX], 0.5f);
		SONG_INDEX++;
		if(SONG_INDEX>=SONG_LEN){ SONG_INDEX=0; }
	}
}

/**********/
void OverDraw()
{
	if(DRAW==1)
	{
		Clear(COLOR_0);

		Image(phaze, phaze_w, phaze_h, WIDTH-phaze_w, HEIGHT-phaze_h);

		Color(COLOR_1);

		String("\"CGA is the best.\"\n\n-Phaze101-", 16, HEIGHT/2);		

		DRAW=0;
	}

	Update();

}