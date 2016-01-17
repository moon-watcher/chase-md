#include <genesis.h>
#include "../res/rescomp.h"

#include "../inc/joyReader.h"
#include "../inc/musicVGM.h"
#include "../inc/screenUtils.h"
#include "../inc/sfxPSG.h"


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0x0EEE
#define IMG_ATTR TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX)
#define FIXBITS 4


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void gameTitle( void )
{
	u8 frame 	= 0, delay = 160;
	s8 speed 	= -8 << FIXBITS;
	s16 vscroll	= VDP_getScreenHeight( ) << FIXBITS;

	JoyReaderReset ( );

	VDP_setEnable( FALSE );
		VDP_cleanScreen( );
		VDP_setVerticalScroll( PLAN_A, VDP_getScreenHeight( ) );
		VDP_drawImageEx (APLAN, &titleScreen, IMG_ATTR, 0, 0, TRUE, FALSE );
	VDP_setEnable( TRUE );

	musicvgm_play( MUSIC_TITLE );

	while( TRUE ) // Shiru's Original Algorithm -- AWESOME!!
	{
		VDP_waitVSync( );
		VDP_setVerticalScroll( PLAN_A, vscroll>>FIXBITS );
		JoyReaderUpdate( );

		vscroll += speed;

		if( vscroll < 0 )
		{
			vscroll = 0;
			speed	= -speed>>1; /* speed = -speed/2 */
		}

		if( speed > ( -8<<FIXBITS ) ) { speed -= 2; }

		if ( delay ) { --delay; }
		else
		{
			 VDP_setPaletteColor(1, ( frame & 32 ) ? COLOR_BLACK : COLOR_WHITE );

			 if( PAD_1_PRESSED_START ) { break; }
		}

		frame++;
	}

	musicvgm_stop( );
	sfxpsg_play( SFX_PRESS_START );

	VDP_setVerticalScroll( PLAN_A, 0 );
	for ( frame=0; frame < 120; frame++ )
	{
		VDP_waitVSync( );
		VDP_setPaletteColor( 1, ( frame & 4 ) ? COLOR_BLACK : COLOR_WHITE );
	}

	VDP_fadePalOut(PAL0, 30, FALSE);
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
