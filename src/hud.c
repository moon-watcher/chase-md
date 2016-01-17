#include <genesis.h>

#include "../inc/hud.h"



/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


#define HUD_PLAN	BPLAN
#define HUD_PAL		PAL0
#define HUD_ATTR 	TILE_ATTR(HUD_PAL, FALSE, FALSE, FALSE)


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void hudInitialize( void )
{
	lives 			= 5;
	level 			= 0;
	totalCoins 		= 0;
	collectedCoins 	= 0;
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static void VDP_drawNumberBG(u16 plan, s32 num, u16 flags, u16 x, u16 y, s16 minsize) // Borrowed from @pocket_lucho, hehehe.
{
    char str[42];
    intToStr(num, str, minsize);
    VDP_drawTextBG(plan, str, flags, x, y);
}

void hudDisplayAsFirstTime( void )
{
	//TODO: To be replaced by SGDK sprintf
    VDP_drawTextBG(HUD_PLAN, "LEVEL:   GEMS:   /     LIVES: ", HUD_ATTR, 5, 1);
    VDP_drawNumberBG(HUD_PLAN, level+1, HUD_ATTR, 11, 1, 1);
    updateCollectedCoins( collectedCoins );
    VDP_drawNumberBG(HUD_PLAN, totalCoins, HUD_ATTR, 23, 1, 3);
    updateLives( lives );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void updateCollectedCoins( u8 amount )
{
	collectedCoins = amount;

	VDP_drawNumberBG(HUD_PLAN, collectedCoins, HUD_ATTR, 19, 1, 3);
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void updateLives( u8 amount )
{
	lives = amount;

    VDP_drawNumberBG(HUD_PLAN, lives, HUD_ATTR, 34, 1, 1);
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
