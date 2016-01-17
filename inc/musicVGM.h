
#ifndef _MUSIC_VGM_
#define _MUSIC_VGM_


	//Global Data
	typedef enum
	{
		MUSIC_TITLE = 0,
		MUSIC_GET_READY,
		MUSIC_INGAME01,
		MUSIC_INGAME02,
		MUSIC_INGAME03,
		MUSIC_INGAME04,
		MUSIC_GAME_DONE,
		MUSIC_GAME_OVER,
		MUSIC_SILENCE,

	   MUSICVGM_MAX
	} vgmtrack;

	typedef struct
	{
	   u8  title[28];
	   u8 *data;
	}
	tVGM;


	//Prototypes
	void     	musicvgm_play		( vgmtrack nb );
	tVGM 		*musicvgm_get_track ( vgmtrack track );
	vgmtrack  	musicvgm_nb_tracks  ( );
	void      	musicvgm_stop 		( );
	void		musicvgm_play_sfx ( vgmtrack nb );


#endif

