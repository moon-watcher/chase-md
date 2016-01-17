
#ifndef _SFXPSG_H_
#define _SFXPSG_H_


	typedef enum
	{
	   SFX_ALL_COLLECTED = 0,
	   SFX_COIN,
	   SFX_KILL,
	   SFX_GAME_PAUSE,
	   SFX_RESPAWN_01,
	   SFX_RESPAWN_02,
	   SFX_RESPAWN_03,
	   SFX_RESPAWN_04,
	   SFX_PRESS_START,

	   SFXPSG_MAX

	} sfxtrack;


	typedef struct
	{
		u8  title[16];
		u8 *data;
		u8  num;
	}
	tPSG;


	void   sfxpsg_play      ( sfxtrack psg );
	void   sfxpsg_frame     ( void );
	u16    sfxpsg_nb_tracks ( );
	tPSG   *sfxpsg_get_track ( sfxtrack num );


#endif
