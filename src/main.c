#include <genesis.h>

#include "../inc/game.h"
#include "../inc/hud.h"
#include "../inc/joyReader.h"
#include "../res/rescomp.h"
#include "../inc/screenUtils.h"
#include "../inc/SPRDispatcher.h"
#include "../inc/sfxPSG.h"



/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


_voidCallback *VIntCallback ( )
{
	if ( IS_PALSYSTEM || ( !IS_PALSYSTEM && ( vtimer % 6 ) ) )
	{
		sfxpsg_frame( );
	}

	return NULL;
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static void initEnviroment( void )
{
	VDP_setScreenWidth320( );
	VDP_setScreenHeight224( );

	VDP_setPlanSize( 64, 64 );
	VDP_setScrollingMode( HSCROLL_PLANE, VSCROLL_PLANE );

	SPR_init( NULL );
	SPRD_reset( );

	VDP_loadFont( &chaseFont, FALSE );

	JoyReaderInit( );

	SYS_setInterruptMaskLevel( 4 );
	SYS_setVIntCallback( (_voidCallback*) VIntCallback );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


int main( void )
{
	initEnviroment( );

	showImageFadeInOut( &disclaimer, 3500 );
	showImageFadeInOut( &nolddorLogo, 3500 );

	while( TRUE )
	{
		hudInitialize( );

		gameTitle( );

		while( ! (IS_GAME_COMPLETE || IS_GAME_OVER) )
		{
			gameLoading( );
			gamePlay( );
		}

		( IS_GAME_OVER ) ? gameOver( ) : gameDone( );

	}

	return NULL; /* Never Reached */
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
