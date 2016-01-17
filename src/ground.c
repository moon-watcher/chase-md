#include <genesis.h>

#include "../inc/hud.h"
#include "../inc/musicVGM.h"
#include "../res/rescomp.h"




/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


#define STAGE_PLAN BPLAN
#define STAGE_PAL PAL0
#define STAGE_ATTR TILE_ATTR_FULL(STAGE_PAL, FALSE, FALSE, FALSE, TILE_USERINDEX)

#define TILE_FLOOR 9


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static const Image *playgroundScreens[ MAX_LEVELS ] =
{
    &playGround01,	&playGround02,	&playGround03,	&playGround04,	&playGround05,
    &playGround06,	&playGround07,	&playGround08,	&playGround09,	&playGround10
};

static Map *stageMap = NULL;


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void displayPlayground( void )
{
	const Image *stageImage 	= playgroundScreens[ level ];
	VDP_drawImageEx( STAGE_PLAN, stageImage, STAGE_ATTR, 0, 0, TRUE, FALSE );

	stageMap = unpackMap(stageImage->map, NULL);
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


u8 isFloor( u16 tileX, u16 tileY )
{
	u8 isFloor = FALSE;

	if( stageMap != NULL )
	{
		const u16 mapWithInTile		= stageMap->w;
		const u16 mapHeightInTile	= stageMap->h;

		if( tileX < mapWithInTile && tileY < mapHeightInTile )
		{
			isFloor = ( stageMap->tilemap[ (tileY * mapWithInTile) + tileX ] == TILE_FLOOR );
		}
	}

	return isFloor;
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */



void destroyPlaygroundMap( void )
{
	MEM_free( stageMap );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


vgmtrack getPlayGroundMusic( void )
{
	const vgmtrack tracks[ MAX_LEVELS ] =
	{
		MUSIC_INGAME01, MUSIC_INGAME02, MUSIC_INGAME03, MUSIC_INGAME01, MUSIC_INGAME02,
		MUSIC_INGAME03, MUSIC_INGAME01, MUSIC_INGAME02, MUSIC_INGAME03, MUSIC_INGAME04
	};

	return tracks[ level ];
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void loadPlayGroundPaletteDark( void )
{
	const Palette *allDarkPalettes[ MAX_LEVELS ] =
	{
		&spriteStage01Dark, &spriteStage01Dark, &spriteStage02Dark, &spriteStage02Dark, &spriteStage03Dark,
		&spriteStage03Dark, &spriteStage04Dark, &spriteStage04Dark, &spriteStage05Dark, &spriteStage05Dark
	};

	VDP_setPalette( STAGE_PAL, allDarkPalettes[ level ]->data );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */

void loadPlayGroundPaletteNormal( void )
{
	const Palette *allNormalPalettes[ MAX_LEVELS ] =
	{
		&spriteStage01Normal, &spriteStage01Normal, &spriteStage02Normal, &spriteStage02Normal, &spriteStage03Normal,
		&spriteStage03Normal, &spriteStage04Normal, &spriteStage04Normal, &spriteStage05Normal, &spriteStage05Normal
	};

	VDP_setPalette( STAGE_PAL, allNormalPalettes[ level ]->data );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
