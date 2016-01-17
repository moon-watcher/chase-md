#include <genesis.h>


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void VDP_cleanScreen( void )
{
	VDP_clearPlan( APLAN, TRUE );
	VDP_waitDMACompletion( );
	VDP_clearPlan( BPLAN, TRUE );
	VDP_waitDMACompletion( );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void showImageFadeInOut( const Image *Image, const u32 delayBetweenFades )
{
	VDP_waitVSync( );

	VDP_setEnable( FALSE );
		VDP_cleanScreen( );
		VDP_setPalette( PAL0, palette_black );
		VDP_drawImageEx( APLAN, Image, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX), 0, 0, FALSE, FALSE );
	VDP_setEnable( TRUE );

	VDP_fadePalIn( PAL0, Image->palette->data, 15, FALSE );

	waitMs( delayBetweenFades );

	VDP_fadePalOut( PAL0, 30, FALSE );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
