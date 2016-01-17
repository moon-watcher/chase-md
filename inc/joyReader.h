
#ifndef _JOYREADER_H_
#define _JOYREADER_H_


    typedef struct
    {
    	unsigned short active;
    	unsigned short changed;
    }
    Joyreader;


    // NOTE: JOY_MAX should be a value between [1 - 8] both allowed
    #define PAD_MAX 1

	#if PAD_MAX > 0

		#define PAD_1 joysticks [ JOY_1 ]

		#define PAD_1_ACTIVE (PAD_1.active)
		#define PAD_1_CHANGED (PAD_1.changed)
		#define PAD_1_PRESSED (PAD_1_ACTIVE & PAD_1_CHANGED)
		#define PAD_1_INACTIVE (~PAD_1_ACTIVE)
    	#define PAD_1_RELEASED (PAD_1_INACTIVE & PAD_1_CHANGED)

		#define PAD_1_ACTIVE_LEFT (PAD_1_ACTIVE & BUTTON_LEFT)
		#define PAD_1_ACTIVE_RIGHT (PAD_1_ACTIVE & BUTTON_RIGHT)
		#define PAD_1_ACTIVE_UP (PAD_1_ACTIVE & BUTTON_UP)
		#define PAD_1_ACTIVE_DOWN (PAD_1_ACTIVE & BUTTON_DOWN)

		#define PAD_1_PRESSED_A (PAD_1_PRESSED & BUTTON_A)
		#define PAD_1_PRESSED_B (PAD_1_PRESSED & BUTTON_B)
		#define PAD_1_PRESSED_C (PAD_1_PRESSED & BUTTON_C)
		#define PAD_1_PRESSED_START (PAD_1_PRESSED & BUTTON_START)
		#define PAD_1_PRESSED_BTN (PAD_1_PRESSED & BUTTON_BTN)
		#define PAD_1_PRESSED_LEFT (PAD_1_PRESSED & BUTTON_LEFT)
		#define PAD_1_PRESSED_RIGHT (PAD_1_PRESSED & BUTTON_RIGHT)
		#define PAD_1_PRESSED_UP (PAD_1_PRESSED & BUTTON_UP)
		#define PAD_1_PRESSED_DOWN (PAD_1_PRESSED & BUTTON_DOWN)

		#define PAD_1_INACTIVE_START (PAD_1_INACTIVE & BUTTON_START)

	#endif

	#if PAD_MAX > 1

		#define PAD_2 joysticks [ JOY_2 ]

	#endif



    //Public data
    Joyreader joysticks[ PAD_MAX ];


    //Public Functions
    void      JoyReaderInit     ( );
    void      JoyReaderUpdate   ( void );
    void      JoyReaderReset    ( );


#endif // _JOYREADER_H_


