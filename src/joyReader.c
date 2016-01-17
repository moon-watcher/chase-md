#include <genesis.h>

#include "../inc/joyReader.h"



/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void JoyReaderInit ( )
{
	memset( joysticks, NULL, sizeof( joysticks ) );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void JoyReaderUpdate ( void )
{
	u16 active;

	#if PAD_MAX > 0

		active = JOY_readJoypad ( JOY_1 );
		joysticks[JOY_1] = ( Joyreader ) { active, (active ^ joysticks[JOY_1].active) };

	#endif

	#if PAD_MAX > 1

		active = JOY_readJoypad ( JOY_2 );
		joysticks[JOY_2] = ( Joyreader ) { active, (active ^ joysticks[JOY_2].active) };

	#endif

	#if PAD_MAX	> 2

		active = JOY_readJoypad ( JOY_3 );
		joysticks[JOY_3] = ( Joyreader ) { active, (active ^ joysticks[JOY_3].active) };

	#endif

	#if PAD_MAX	> 3

		active = JOY_readJoypad ( JOY_4 );
		joysticks[JOY_4] = ( Joyreader ) { active, (active ^ joysticks[JOY_4].active) };

	#endif

	#if PAD_MAX	> 4

		active = JOY_readJoypad ( JOY_5 );
		joysticks[JOY_5] = ( Joyreader ) { active, (active ^ joysticks[JOY_5].active) };

	#endif

	#if PAD_MAX	> 5

		active = JOY_readJoypad ( JOY_6 );
		joysticks[JOY_6] = ( Joyreader ) { active, (active ^ joysticks[JOY_6].active) };

	#endif

	#if PAD_MAX	> 6

		active = JOY_readJoypad ( JOY_7 );
		joysticks[JOY_7] = ( Joyreader ) { active, (active ^ joysticks[JOY_7].active) };

	#endif

	#if PAD_MAX	> 7

		active = JOY_readJoypad ( JOY_8 );
		joysticks[JOY_8] = ( Joyreader ) { active, (active ^ joysticks[JOY_8].active) };

	#endif
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void JoyReaderReset ( )
{
    JoyReaderInit ( );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
