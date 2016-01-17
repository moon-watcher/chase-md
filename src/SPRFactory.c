#include <genesis.h>
#include "../res/rescomp.h"

#include "../inc/SPRFactory.h"
#include "../inc/SPRDispatcher.h"



/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


#define SPR_PAL		PAL2
#define SPR_ATTR 	( TILE_ATTR( SPR_PAL, FALSE, FALSE, FALSE ) )


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void loadSpritePaletteDark( void )
{
	VDP_setPalette( SPR_PAL, spritePaletteDark.data );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void loadSpritePalette( void )
{
	VDP_setPalette( SPR_PAL, spritePaletteNormal.data );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static Sprite *createMonster( s16 positionX, s16 positionY, u8 monsterId, u8 loadpal )
{
	Sprite *monsterSpr = SPRD_new( 6, SPRD_DOWN );

	SPR_initSprite( monsterSpr, (SpriteDefinition*) &monstersSprDef, positionX, positionY, SPR_ATTR );
	SPR_setAnim( monsterSpr, monsterId );

	if( loadpal )
	{
		loadSpritePalette( );
	}

	return monsterSpr;
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static Sprite *createPause( s16 positionX, s16 positionY, u8 loadpal )
{
	Sprite *pauseSpr = SPRD_new( 0, SPRD_UP );

	SPR_initSprite( pauseSpr, (SpriteDefinition*) &pauseSprDef, positionX, positionY, SPR_ATTR );

	if( loadpal )
	{
		loadSpritePalette( );
	}

	return pauseSpr;
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


const sprFactoryStruct SPRFactory =
{
	.createMonster			= 	&createMonster,
	.createPause			=	&createPause,
	.loadSpritePalette		=	&loadSpritePalette,
	.loadSpritePaletteDark	=	&loadSpritePaletteDark
};


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
