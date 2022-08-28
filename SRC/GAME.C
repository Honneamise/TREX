/* HEADERS */ 
#include <stdlib.h>

#include "DIXIE/CORE.H"
#include "DIXIE/UTILS.H"

#include "SRC/UNIT.H"
#include "SRC/STATE.H"
#include "SRC/MANAGER.H"
#include "SRC/INTRO.H"
#include "SRC/OVER.H"

/* VARS */
static int CHANGE = 0;

static int difficulty = 5;

static Unit player = {0};
static Unit enemy = {0};

static int player_collision = 0;
static int player_life = 3;
static int player_score = 0;
static char player_score_str[16] = {0};

/**********/
void GameReset()
{
	CHANGE = 0;

	difficulty = 5;

	player_life = 3;
	player_score = 0;
	player_collision = 0;

	player.pos = Vec2fInit(50, HEIGHT/2);
	player.speed = Vec2fInit(0,0);

	enemy.pos = Vec2fInit(WIDTH, HEIGHT/2);
	enemy.speed = Vec2fInit(-difficulty,0);
	enemy.img = ManagerGet( Rand(2, ManagerSize()-1) );
}

/**********/
void GameInit()
{
	player.pos = Vec2fInit(50, HEIGHT/2);
	player.speed = Vec2fInit(0,0);
	player.img = ManagerGet(0);
	player.img_w = 32;
	player.img_h = 32;
	
	enemy.pos = Vec2fInit(WIDTH, HEIGHT/2);
	enemy.speed = Vec2fInit(-difficulty,0);
	enemy.img_w = 32;
	enemy.img_h = 32;
}

/*********/
void GameClose()
{

}

/**********/
void GameInput()
{
    if(kbhit())
	{
        switch (getch())
		{
			case 27:
				CHANGE = 1;
				StopSound();
				IntroReset();
				SM_Pop();
				break;

			case ' ':
				if(player.speed.y == 0)
				{
					player.speed.y = -difficulty;

					Sound(C,0.25f);
				}
				break;

			default: break;
        }
    }
}

/*********/
void GameUpdate()
{
	/* there was a collision ? */
	if(player_collision)
	{
		player_life--;

		StopSound();

		Sound(8126, 0.5f);
		while(SoundPlaying()){ Update(); }
		
		Sound(8609, 0.5f);
		while(SoundPlaying()){ Update(); }

		Sound(9121, 1.0f);
		while(SoundPlaying()){ Update(); }

		StopSound();

		enemy.pos.x = WIDTH + enemy.img_w/2;
		enemy.img = ManagerGet( Rand(2, ManagerSize()-1) );

		player.pos = Vec2fInit(50, HEIGHT/2);
		player.speed = Vec2fInit(0,0);

		/* still alive ? */
		if(player_life<=0)
		{
			CHANGE = 1;
			StopSound();
			OverReset();
			SM_Push(STATE_OVER);
			return;
		}
	}

	UnitUpdate(&player);

	if(player.speed.y<0)
	{
		if(player.pos.y < HEIGHT/2 - player.img_h*2)
		{
			player.speed.y = +difficulty;
		}
	}

	if(player.speed.y>0)
	{
		if(player.pos.y > HEIGHT/2)
		{
			player.pos.y = HEIGHT/2;
			player.speed.y = 0;
		}
	}

	UnitUpdate(&enemy);
	if(enemy.pos.x < -enemy.img_w/2)
	{
		player_score++;

		if(player_score%3==0){ difficulty++; }

		enemy.pos.x = WIDTH + enemy.img_w/2;
		enemy.img = ManagerGet( Rand(2, ManagerSize()-1) );
		enemy.speed = Vec2fInit(-difficulty,0);		
	}

	/* check collision */
	player_collision = ImageOverlap(player.img,
								player.pos.x - player.img_w/2,
								player.pos.y - player.img_h/2,
								player.img_w,
								player.img_h,

								enemy.img,
                    			enemy.pos.x - enemy.img_w/2,
								enemy.pos.y - enemy.img_h/2,
								enemy.img_w,
								enemy.img_h,

								COLOR_0);

}

/**********/
void GameDraw()
{
	int i = 0;

	if(player_life<=0)
	{ 
		Clear(COLOR_0);
		Update();
		return; 
	}

	/*draw*/
	Clear(COLOR_0);

	UnitDraw(&player);

	UnitDraw(&enemy);

	Color(COLOR_3);
	Line(0, HEIGHT/2+16, WIDTH, HEIGHT/2+16);

	/*score*/
	sprintf(player_score_str,"Score : %d", player_score);
	String(player_score_str, WIDTH/2, HEIGHT/2 + player.img_h/2*3);

	/*life*/
	for(i=0;i<player_life;i++)
	{
		ImageMask(player.img, player.img_w, player.img_h, (i+1) * player.img_w, HEIGHT/2 + player.img_h, COLOR_0);
	}

	Update();

}