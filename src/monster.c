#include <genesis.h>
#include "../res/rescomp.h"

#include "../inc/screenUtils.h"
#include "../inc/coin.h"
#include "../inc/monster.h"
#include "../inc/ground.h"
#include "../inc/hud.h"
#include "../inc/joyReader.h"
#include "../inc/sfxPSG.h"
#include "../inc/SPRDispatcher.h"
#include "../inc/SPRFactory.h"



/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


#define MONSTER_MAX_MOVES 16

#define MAX_MONSTER 4
#define PLAYER_IDX 0
#define FRANKY_IDX 1
#define VAMPY_IDX 2
#define BANDY_IDX 3

#define MAX_DIR     4
#define DIR_NONE    0
#define DIR_UP      1
#define DIR_RIGHT   2
#define DIR_DOWN    3
#define DIR_LEFT    4


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static u8 monstersTotalByLevel[ MAX_LEVELS ] = { 2, 2, 3, 3, 3, 3, 4, 4, 4, 4 };

static Vect2D_u16 *monstersPositionByLevel[ MAX_LEVELS ] =
{
	//					CHASE			FRANKY			VAMPY			BANDY
	(Vect2D_u16[])	{	{112, 80},  	{192,144} 									},
	(Vect2D_u16[])	{ 	{112, 80},  	{192,144} 									},
	(Vect2D_u16[])	{ 	{ 96, 64},  	{208, 64}, 		{ 96,160} 					},
	(Vect2D_u16[])	{ 	{ 96, 64},  	{208, 64}, 		{ 96,160} 					},
	(Vect2D_u16[])	{ 	{ 96, 64},  	{208, 64}, 		{208,160} 					},
	(Vect2D_u16[])	{ 	{ 96, 64},  	{208, 64}, 		{208,160} 					},
	(Vect2D_u16[])	{ 	{ 96, 48},  	{240, 64}, 		{ 64,160}, 		{208,176}	},
	(Vect2D_u16[])	{ 	{ 96, 48},  	{240, 64}, 		{ 64,160}, 		{208,176}	},
	(Vect2D_u16[])	{ 	{ 80, 40},  	{224, 40}, 		{ 80,184}, 		{224,184}	},
	(Vect2D_u16[])	{ 	{ 72, 40},  	{216, 40}, 		{ 72,184}, 		{216,184}	}
};

typedef struct
{
	u8		monsterId;
    u8      direction;
    u8      lastDirection;
    fix16	speed;
    fix16   moveCounter;
    u16     basePosX;
    u16     basePosY;
    Sprite  *sprite;

} tMonster;

static tMonster allMonsters[ MAX_MONSTER ];


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static void checkCollisionWithCoins( tMonster *monster )
{
	s16 tileX = PIXEL2TILE(monster->sprite->x - 0x80);
	s16 tileY = PIXEL2TILE(monster->sprite->y - 0x80);

	captureCoin( tileX, tileY );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static void checkCollisionWithPlayer( const tMonster *player, tMonster *monster )
{
	// Borrowed from @KanedaFr [http://gendev.spritesmind.net/page-collide.html]

	const s16 playerWith	= player->sprite->frame->w;
	const s16 playerHeight	= player->sprite->frame->h;

	const s16 playerX		= player->sprite->x + 4;
	const s16 playerY		= player->sprite->y + 4;
	const s16 playerXX		= playerX + playerWith - 5;
	const s16 playerYY		= playerY + playerHeight - 5;

	const s16 monsterWith	= monster->sprite->frame->w;
	const s16 monsterHeight	= monster->sprite->frame->h;

	const s16 monsterX		= monster->sprite->x + 4;
	const s16 monsterY		= monster->sprite->y + 4;
	const s16 monsterXX		= monsterX + monsterWith - 5;
	const s16 monsterYY		= monsterY + monsterHeight - 5;


	if( !( ( monsterX > playerXX ) || ( monsterY > playerYY ) || ( monsterXX < playerX ) || ( monsterYY < playerY ) ) )
	{
		updateLives( lives -1 );

		isPlayerCatched = TRUE;
	}
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static void setDirectionFromJoy( tMonster *monster )
{
	s16 x = PIXEL2TILE(monster->sprite->x - 0x80);
	s16 y = PIXEL2TILE(monster->sprite->y - 0x80);

	monster->direction = DIR_NONE;

		 if( PAD_1_ACTIVE_UP     && isFloor( x, y-1) )    { monster->direction = DIR_UP; }
	else if( PAD_1_ACTIVE_RIGHT  && isFloor( x+2, y) )    { monster->direction = DIR_RIGHT; }
	else if( PAD_1_ACTIVE_DOWN   && isFloor( x, y+2) )    { monster->direction = DIR_DOWN; }
	else if( PAD_1_ACTIVE_LEFT   && isFloor( x-1, y) )    { monster->direction = DIR_LEFT; }
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static void setDirectionRelativeToPlayer( const tMonster *player, tMonster *monster )
{
	s16 playerX		= PIXEL2TILE(player->sprite->x - 0x80);
	s16 playerY		= PIXEL2TILE(player->sprite->y - 0x80);
	s16 monsterX	= PIXEL2TILE(monster->sprite->x - 0x80);
	s16 monsterY	= PIXEL2TILE(monster->sprite->y - 0x80);


	/* First we'll check all available directions */

	u8 availableDirections[ MAX_DIR ];
	u8 totalAvailableDirections = 0;

	if( monster->lastDirection != DIR_DOWN   && isFloor( monsterX, monsterY-1 ) )
	{
		availableDirections[ totalAvailableDirections++ ] = DIR_UP;
	}
	if( monster->lastDirection != DIR_LEFT   && isFloor( monsterX+2, monsterY ) )
	{
		availableDirections[ totalAvailableDirections++ ] = DIR_RIGHT;
	}
	if( monster->lastDirection != DIR_UP     && isFloor( monsterX, monsterY+2 ) )
	{
		availableDirections[ totalAvailableDirections++ ] = DIR_DOWN;
	}
	if( monster->lastDirection != DIR_RIGHT  && isFloor( monsterX-1, monsterY ) )
	{
		availableDirections[ totalAvailableDirections++ ] = DIR_LEFT;
	}

	if( totalAvailableDirections == 0 )
	{
		monster->direction = DIR_NONE;
	}
	else
	{
		monster->direction = availableDirections[ random() % totalAvailableDirections ] ;
	}

	/* Finding a clever path NOT FOR VAMPY */

	if( monster->monsterId != VAMPY_IDX || (random( ) & 3) == 0 )
	{
		u8 availableCleverDirections[ 2 ];
		u8 totalAvailableCleverDirections = 0;
		u8 directionId;

		for( directionId = 0; directionId < totalAvailableDirections; directionId++ )
		{
			if( availableDirections[ directionId ] == DIR_UP && monsterY > playerY )
			{
				availableCleverDirections[ totalAvailableCleverDirections++ ] = DIR_UP;
			}
			else if( availableDirections[ directionId ] == DIR_RIGHT && monsterX < playerX )
			{
				availableCleverDirections[ totalAvailableCleverDirections++ ] = DIR_RIGHT;
			}
			else if( availableDirections[ directionId ] == DIR_DOWN && monsterY < playerY )
			{
				availableCleverDirections[ totalAvailableCleverDirections++ ] = DIR_DOWN;
			}
			else if( availableDirections[ directionId ] == DIR_LEFT && monsterX > playerX )
			{
				availableCleverDirections[ totalAvailableCleverDirections++ ] = DIR_LEFT;
			}
		}

		if( totalAvailableCleverDirections != 0 )
		{
			monster->direction = availableCleverDirections[ random () % totalAvailableCleverDirections ];
		}
	}
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static void respawnMonster( const tMonster* monster )
{
	sfxpsg_play( SFX_RESPAWN_01 + monster->monsterId );

	const s16 originalPositionX = monster->sprite->x - 0x80;
	const s16 originalPositionY = monster->sprite->y - 0x80;

	u8 delay;
	for ( delay = 0; delay < 32; delay++ )
	{
		VDP_waitVSync( );

		const s16 positionX = originalPositionX;
		const s16 positionY = ( delay & 2 ) ? originalPositionY : VDP_getScreenHeight( );

		SPR_setPosition( monster->sprite, positionX, positionY );

		SPRD_update( );
	}
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static fix16 getSpeedByMonster( u8 monsterId )
{
	const fix16 speedTable[ MAX_MONSTER ] =
	{
		FIX16(1.8), // CHASE
		FIX16(0.8), // FRANKY
		FIX16(0.9), // VAMPY
		FIX16(1.0)  // BANDY
	};

	fix16 speed = FIX16( 0 );

	if( monsterId < MAX_MONSTER )
	{
		speed = speedTable[ monsterId ];
	}

	return speed;
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void monsterMovement( void )
{
	u8 totalMonsters =  monstersTotalByLevel[ level ];

	u8 monsterId;
	for ( monsterId = 0; monsterId < totalMonsters; monsterId++ )
	{
		const u8 isPlayer = ( monsterId == PLAYER_IDX );

		tMonster *thisMonster = &allMonsters[ monsterId ];
		const tMonster *player = &allMonsters[ PLAYER_IDX ];

		if( thisMonster->direction == DIR_NONE )
		{
			if ( isPlayer )
			{
				setDirectionFromJoy( thisMonster );
			}
			else
			{
				setDirectionRelativeToPlayer( player, thisMonster );
			}
		}

		s16 moveCounterInt = fix16ToInt( thisMonster->moveCounter );

		if( thisMonster->direction != DIR_NONE )
		{
			thisMonster->moveCounter = fix16Add( thisMonster->moveCounter, thisMonster->speed );
			moveCounterInt = fix16ToInt( thisMonster->moveCounter );

			if( moveCounterInt > MONSTER_MAX_MOVES ) { moveCounterInt = MONSTER_MAX_MOVES; }

			switch( thisMonster->direction )
			{
				case DIR_UP:        thisMonster->sprite->y = thisMonster->basePosY - moveCounterInt; break;
				case DIR_RIGHT:     thisMonster->sprite->x = thisMonster->basePosX + moveCounterInt; break;
				case DIR_DOWN:      thisMonster->sprite->y = thisMonster->basePosY + moveCounterInt; break;
				case DIR_LEFT:      thisMonster->sprite->x = thisMonster->basePosX - moveCounterInt; break;
			}
		}


		if( moveCounterInt == MONSTER_MAX_MOVES || thisMonster->direction == DIR_NONE )
		{
			thisMonster->moveCounter 	= FIX16(0.0);
			thisMonster->basePosY 		= thisMonster->sprite->y;
			thisMonster->basePosX 		= thisMonster->sprite->x;
			thisMonster->lastDirection 	= thisMonster->direction;
			thisMonster->direction 		= DIR_NONE;
		}

		if( isPlayer )
		{
			checkCollisionWithCoins( thisMonster );
		}
		else
		{
			checkCollisionWithPlayer( player, thisMonster );
		}
	}
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void monstersInitialize( void )
{
	isPlayerCatched = FALSE;

	u8 totalMonsters =  monstersTotalByLevel[ level ];

	u8 monsterId;
	for ( monsterId = 0; monsterId < totalMonsters; monsterId++ )
	{
		const u16 positionX = monstersPositionByLevel[ level ][ monsterId ].x;
		const u16 positionY = monstersPositionByLevel[ level ][ monsterId ].y;

		const u8 loadpal = ( monsterId == PLAYER_IDX );

		const Sprite *monsterSpr = SPRFactory.createMonster( positionX, positionY, monsterId, loadpal );

		allMonsters[ monsterId ] = (const tMonster)
		{
			.monsterId		= monsterId,
			.direction		= DIR_NONE,
			.lastDirection	= DIR_NONE,
			.speed			= getSpeedByMonster( monsterId ),
			.moveCounter	= FIX16(0.0),
			.basePosX 		= monsterSpr->x,
			.basePosY 		= monsterSpr->y,
			.sprite 		= (Sprite*) monsterSpr
		};

		respawnMonster( &allMonsters[ monsterId ] );
	}

}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
