
#ifndef _SCREEN_
#define _SCREEN_


	//Macros
	#define PIXEL2TILE(n) ((n)>>3)
	#define TILE2PIXEL(n) ((n)<<3)
	#define PLAN2VDPPLAN(n) ((n==APLAN)?PLAN_A:PLAN_B)

	//Prototypes
	void VDP_cleanScreen( void );
	void showImageFadeInOut( const Image *Image, const u32 delay );


#endif
