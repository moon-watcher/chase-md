#include <genesis.h>
#include "../res/rescomp.h"

#include "../inc/joyReader.h"
#include "../inc/musicVGM.h"
#include "../inc/screenUtils.h"



/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


#define COLOR_WHITE 0x0000
#define COLOR_PINK 0x084C


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void gameOver( void )
{
	VDP_waitVSync( );

	VDP_setEnable( FALSE );
		VDP_cleanScreen( );
		VDP_setPalette( PAL0, palette_black );
		VDP_drawImageEx( APLAN, &gameOverImg, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX), 0, 0, FALSE, FALSE );
	VDP_setEnable( TRUE );

	musicvgm_play( MUSIC_GAME_OVER );

	VDP_fadePalIn( PAL0, gameOverImg.palette->data, 15, FALSE );

	JoyReaderReset( );

	u8 frame = 0;
	u8 delay = 0;
	u8 maxDelay = (IS_PALSYSTEM) ? 175 : 210;

	while( !PAD_1_PRESSED_START )
	{
		VDP_waitVSync();
		VDP_setPaletteColor(1, (frame++&2) ? COLOR_WHITE : COLOR_PINK );

		if( delay < maxDelay )
		{
			delay++;
		}
		else if( delay == maxDelay )
		{
			SND_playSfx_VGM( sfxGameOverVoice, sizeof(sfxGameOverVoice) );
			delay = -1;
		}

		JoyReaderUpdate( );
	}

	VDP_fadePalOut(PAL0, 20, FALSE);
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
