/*
    Borrowed from @MoonWatcherMD - Game: JunkbotsMD (BitBitJam 2014)

    Some changes and improvements by JackNolddor (@nolddor)
    Last Update: xx/Jan/2016
*/


#include <genesis.h>

#include "../inc/SPRDispatcher.h"



/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static u8 _used [ MAX_SPRITE ] = { [0 ... MAX_SPRITE-1] = FALSE };
static u8 _cnt = 0;


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


static u8 _find ( u8 start, SPRDdir direction )
{
   s8 i;

   switch ( direction )
   {
      case SPRD_UP:

         for ( i = start; i < MAX_SPRITE; i++ )
         {
            if ( ! _used[(u8) i] )
            {
               return i;
            }
         }

         return MAX_SPRITE-1;


      case SPRD_DOWN:

         for ( i = start; i >= 0; i-- )
         {
            if ( ! _used[(u8) i] )
            {
               return i;
            }
         }

         return 0;
   }

   return 0;
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


u8 SPRD_getLength ( void )
{
    return _cnt;
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


u8 SPRD_newIDX ( u8 idx, SPRDdir dir )
{
   u8 i = _find( idx, dir );

   _used[ i ] = TRUE;
   if( i >= _cnt ) { _cnt = i + 1; }

   return i;
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


Sprite* SPRD_new ( u8 pos, SPRDdir dir )
{
    return &sprlist[ SPRD_newIDX(pos, dir) ];
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


u8 SPRD_getFirstIDX ( void )
{
    return SPRD_newIDX( 0, SPRD_UP );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


Sprite* SPRD_getFirst ( void )
{
    return &sprlist[ SPRD_getFirstIDX() ];
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


u8 SPRD_getLastIDX ( void )
{
    return SPRD_newIDX( (MAX_SPRITE-1), SPRD_DOWN );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


Sprite* SPRD_getLast ( void )
{
    return SPRD_new( (MAX_SPRITE-1), SPRD_DOWN );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void SPRD_delete ( u8 i )
{
   if ( i < _cnt )
   {
       if ( i+1 == _cnt ) { _cnt--; }

       memset( &sprlist[i], NULL, sizeof(Sprite) );
       _used[i] = FALSE;
   }
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void SPRD_update( void )
{
	SPR_update( sprlist, SPRD_getLength( ) );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */


void SPRD_reset( void )
{
    _cnt = 0;
    memset( _used, FALSE, sizeof (u8) * MAX_SPRITE );
    memset( sprlist, NULL, sizeof(Sprite) * MAX_SPRITE );
}


/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
