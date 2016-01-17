#include <genesis.h>
#include "../res/rescomp.h"

#include "../inc/hud.h"
#include "../inc/screenUtils.h"
#include "../inc/sfxPSG.h"



/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


#define COIN_PAL PAL0
#define COIN_PLAN APLAN
#define COIN_ATTR TILE_ATTR_FULL(COIN_PAL, FALSE, FALSE, FALSE, TILE_USERINDEX+100)

#define TILE_COIN 1


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static const Image *coinScreens[ MAX_LEVELS ] =
{
    &coinMap01,	&coinMap02,	&coinMap03,	&coinMap04,	&coinMap05,
    &coinMap06,	&coinMap07,	&coinMap08,	&coinMap09,	&coinMap10
};

static Map *collisionMap = NULL;

static u8 frame = 0;


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static u8 isCoin( u16 tileX, u16 tileY )
{
	u8 isCoin = FALSE;

	if( collisionMap != NULL )
	{
		const u16 mapWithInTile		= collisionMap->w;
		const u16 mapHeightInTile	= collisionMap->h;

		if( tileX < mapWithInTile && tileY < mapHeightInTile )
		{
			isCoin = ( collisionMap->tilemap[ (tileY * mapWithInTile) + tileX ] == TILE_COIN );
		}
	}

	return isCoin;
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void coinDisplayAllCoins( void )
{
	const Image *coinsImage 	= coinScreens[ level ];
	VDP_drawImageEx( COIN_PLAN, coinsImage, COIN_ATTR, 0, 0, FALSE, FALSE );

	collisionMap = unpackMap(coinsImage->map, NULL);

	/* Check each 16px X 16px square for a coin */
	collectedCoins = 0;
	totalCoins = 0;

	u8 x, y;
	for ( x = 0; x < collisionMap->w; x++ )
	{
		for ( y = 0; y < collisionMap->h; y++ )
		{
			if ( isCoin( x, y ) )
			{
				++totalCoins;
			}
		}
	}
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void captureCoin( u16 tileX, u16 tileY )
{
	if( isCoin( tileX, tileY ) )
	{
		sfxpsg_play( SFX_COIN );

		/* Remove Coin from Map */
        VDP_clearTileMapRect( COIN_PLAN, tileX, tileY, 2, 2 );
        collisionMap->tilemap[ (tileY * collisionMap->w) + tileX ] = NULL;

        updateCollectedCoins( collectedCoins + 1 );
	}
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void coinMovement( void )
{
	const u8 vScroll = ( frame++ & 16 ) ? 1 : 0;

	VDP_setVerticalScroll( PLAN2VDPPLAN(COIN_PLAN) , vScroll );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void destroyCoinMap( void )
{
	MEM_free( collisionMap );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
