
#ifndef _HUD_
#define _HUD_


	//Defines
	#define MAX_LEVELS 10
	#define IS_GAME_OVER ( lives == 0 )
	#define IS_GAME_COMPLETE ( level >= MAX_LEVELS )
	#define IS_STAGE_COMPLETED ( collectedCoins >= totalCoins )

	//Global Data
	u8 lives, level, totalCoins, collectedCoins;

	//Prototypes
	void hudInitialize( void );
	void hudDisplayAsFirstTime( void );
	void updateCollectedCoins( u8 amount );
	void updateLives( u8 amount );


#endif
