#include <genesis.h>

#include "../inc/hud.h"
#include "../inc/musicVGM.h"
#include "../res/rescomp.h"

#include "../inc/screenUtils.h"



/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static const Image *splashScreens[ MAX_LEVELS ] =
{
    &splashScreen01,	&splashScreen02,	&splashScreen03,	&splashScreen04,	&splashScreen05,
    &splashScreen06,	&splashScreen07,	&splashScreen08,	&splashScreen09,	&splashScreen10
};


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void gameLoading( void )
{
    musicvgm_play( MUSIC_GET_READY );

	const Image *splashScreen = splashScreens[ level ];
	showImageFadeInOut( splashScreen, 3500 );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
