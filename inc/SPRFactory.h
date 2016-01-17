
#ifndef _SPRFACTORY_H_
#define _SPRFACTORY_H_


	typedef struct
	{
		Sprite * 	(*createMonster)			( s16, s16, u8, u8 );
		Sprite * 	(*createPause)				( s16, s16, u8 );
		void	 	(*loadSpritePalette)		( void );
		void	 	(*loadSpritePaletteDark)	( void );

	} sprFactoryStruct;


	//Public data
	extern const sprFactoryStruct SPRFactory;


#endif /* _SPRFACTORY_H_ */
