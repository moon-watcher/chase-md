#include <genesis.h>
#include "../res/rescomp.h"

#include "../inc/screenUtils.h"
#include "../inc/coin.h"
#include "../inc/ground.h"
#include "../inc/hud.h"
#include "../inc/joyReader.h"
#include "../inc/monster.h"
#include "../inc/musicVGM.h"
#include "../inc/sfxPSG.h"
#include "../inc/SPRDispatcher.h"
#include "../inc/SPRFactory.h"



/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void gamePlay( void )
{

	JoyReaderReset( );

	VDP_setEnable( FALSE );
		VDP_cleanScreen( );
		SPRD_reset( );

		displayPlayground( );
		coinDisplayAllCoins( );
		hudDisplayAsFirstTime( );

		Sprite *pauseSpr = SPRFactory.createPause( VDP_getScreenWidth(), VDP_getScreenHeight(), FALSE );
	VDP_setEnable( TRUE );

	monstersInitialize( );

	musicvgm_play( getPlayGroundMusic( ) );

	u8 isGamePaused	= FALSE;

	while( !IS_STAGE_COMPLETED && !isPlayerCatched )
	{
		VDP_waitVSync( );
		JoyReaderUpdate( );

		if( PAD_1_PRESSED_START )
		{
			isGamePaused = !isGamePaused;

			sfxpsg_play( SFX_GAME_PAUSE );

			if( isGamePaused )
			{
				SPRFactory.loadSpritePaletteDark( );
				loadPlayGroundPaletteDark( );
				SPR_setPosition( pauseSpr, 140, 108 );
			}
			else
			{
				SPRFactory.loadSpritePalette( );
				loadPlayGroundPaletteNormal( );
				SPR_setPosition( pauseSpr, VDP_getScreenWidth(), VDP_getScreenHeight() );
			}
		}

		if( !isGamePaused )
		{
			monsterMovement( );
		}

		coinMovement( );
		SPRD_update( );
	}

	musicvgm_stop( );

	if( IS_STAGE_COMPLETED )
	{
		level++;
		sfxpsg_play( SFX_ALL_COLLECTED );
	}
	else
	{
		sfxpsg_play( SFX_KILL );
	}

	destroyPlaygroundMap( );
	destroyCoinMap( );

    waitMs(1000);
	SPR_clear( );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
