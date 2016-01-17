#include <genesis.h>
#include "../res/rescomp.h"

#include "../inc/joyReader.h"
#include "../inc/musicVGM.h"
#include "../inc/screenUtils.h"



/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


#define COLOR_WHITE 0x0000
#define COLOR_BLUE 0x0C84


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void gameDone( void )
{
	VDP_waitVSync( );

	VDP_setEnable( FALSE );
		VDP_cleanScreen( );
		VDP_setPalette( PAL0, palette_black );
		VDP_drawImageEx( APLAN, &gameDoneImg, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX), 0, 0, FALSE, FALSE );
	VDP_setEnable( TRUE );

	musicvgm_play( MUSIC_GAME_DONE );

	VDP_fadePalIn( PAL0, gameDoneImg.palette->data, 15, FALSE );

	JoyReaderReset( );

	u8 frame = 0;
	while( !PAD_1_PRESSED_START )
	{
		VDP_waitVSync();
		VDP_setPaletteColor(1, (frame++&2) ? COLOR_WHITE : COLOR_BLUE );

		JoyReaderUpdate( );
	}

	VDP_fadePalOut(PAL0, 20, FALSE);
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
