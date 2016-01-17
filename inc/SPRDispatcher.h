
#ifndef _SPRITEDISPATCHER_H_
#define _SPRITEDISPATCHER_H_


    /** \brief
     *  Available directions for use with Sprite Dispatcher functions
     *
     *  Members:
     *  SPRD_DOWN
     *  SPRD_UP
     */
    typedef enum
    {
       SPRD_DOWN =    0,
       SPRD_UP =      1

    } SPRDdir;


    /** \brief
     *  List of available sprites used by this module (SpriteDispatcher).
     *
     *  The size of available sprites is defined by MAX_SPRITE.
     */
    Sprite sprlist[MAX_SPRITE];


    /** \brief
     *  Clear the whole sprite list.
     */
    void SPRD_reset  ( void );


    /** \brief
     *  Search for a free index into the sprite list, starting for the beginning of this list.
     *
     * \return
     *  A free index of sprite list, or (MAX_SPRITE -1) in case the sprite list will be completely filled.
     */
    u8 SPRD_getFirstIDX ( void );


    /** \brief
     *  Search for a free sprite into the sprite list, starting for the beginning of this list.
     *
     * \return
     *  The requested sprite, or last sprite of the list in case the sprite list will be completely filled.
     */
    Sprite* SPRD_getFirst( void );


    /** \brief
     *  Search for a free index into the sprite list, starting for the ending of this list.
     *
     * \return
     *  A free index of sprite list, or 0 in case the sprite list will be completely filled.
     */
    u8 SPRD_getLastIDX  ( void );

    /** \brief
     *  Search for a free sprite into the sprite list, starting for the ending of this list.
     *
     * \return
     *  The requested sprite, or first sprite of the list in case the sprite list will be completely filled.
     */
    Sprite* SPRD_getLast( void );



    /** \brief
     *  Search for a free index into the sprite list, from 'pos' to the ending or the begining of the list depending of the typed 'dir'.
     *
     *  \param pos
     *  The pos which represent the starting index of the search.
     *
     *  \param dir
     *  The direction of the search.
     *
     *  Use 'SPRD_DOWN' to search till the beginning of the sprite list.
     *  Use 'SPRD_UP' to search till the ending of the sprite list.
     *
     * \return
     *  A free index of sprite list, in case the sprite list will be completely filled,
     *  0 will be returned for SPRD_DOWN direction and (MAX_SPRITE -1) for SPRD_UP.
     */
    u8 SPRD_newIDX    ( u8 pos, SPRDdir dir );


    /** \brief
     *  Search for a free sprite into the sprite list, from 'pos' to the ending or the begining of the list depending of the typed 'dir'.
     *
     *  \param pos
     *  The pos which represent the starting index of the search.
     *
     *  \param dir
     *  The direction of the search.
     *
     *  Use 'SPRD_DOWN' to search till the beginning of the sprite list.
     *  Use 'SPRD_UP' to search till the ending of the sprite list.
     *
     * \return
     *  The requested sprite, in case the sprite list will be completely filled,
     *  the first one of the list will be returned for SPRD_DOWN direction and the last one for SPRD_UP.
     */
    Sprite* SPRD_new  ( u8 pos, SPRDdir dir );


     /** \brief
     *  Free the sprite defined by index.
     *
     *  \param idx
     *  Index of the sprite which will be cleared.
     *
     */
    void SPRD_delete ( u8 idx );


    /** \brief
     *  Return the length of the actual sprite list.
     *
     *  Will be use as second parameter of SPR_update() function.
     *
     * \return
     *  Return the length of the actual sprite list
     */
    u8 SPRD_getLength ( void );

    /** \brief
     *  Update the entire 'sprlist'.
     */
    void SPRD_update( void );

#endif
