#include <genesis.h>

#include "../res/rescomp.h"
#include "../inc/musicVGM.h"



/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static const tVGM _list [ ] =
{
		{ "Title Music", 		(u8*) musicTitle },
		{ "Get Ready Music", 	(u8*) musicGetReady },
		{ "Ingame 01 Music", 	(u8*) musicIngame01 },
		{ "Ingame 02 Music", 	(u8*) musicIngame02 },
		{ "Ingame 03 Music", 	(u8*) musicIngame03 },
		{ "Ingame 04 Music", 	(u8*) musicIngame04 },
		{ "Well Done Music", 	(u8*) musicGameDone },
		{ "Game Over Music", 	(u8*) musicGameOver },
		{ "Silence Music", 	 	(u8*) musicSilence },

	    { "EOF",            	NULL } /* DON'T REMOVE */
};


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void musicvgm_play ( vgmtrack nb )
{
	SND_isPlaying_MVS( );
	SND_startPlay_VGM ( _list[ nb ].data );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


tVGM *musicvgm_get_track ( vgmtrack nb )
{
   return ( tVGM* ) & _list [ nb ];
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


vgmtrack musicvgm_nb_tracks()
{
   return MUSICVGM_MAX;
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void musicvgm_stop( )
{
	 musicvgm_play( MUSIC_SILENCE );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
