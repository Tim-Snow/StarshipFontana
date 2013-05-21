#ifndef SFEVENT_H
#define SFEVENT_H

#include <SDL/SDL.h>
#include <iostream> 
/**
 * Most of these SFEVENTs map onto game concepts apart from _NULL and _LAST.
 * SFEVENT_NULL means to do nothing.  It is created if we get an event that we do not recognise.
 * SFEVENT_LAST marks the maximal element in the SFEVENT enumeration.  It is useful for creating
 *              the slots array in SFEventDispacher
 */
enum SFEVENT {SFEVENT_NULL, SFEVENT_INTRO, SFEVENT_WIN, SFEVENT_LOSE, SFEVENT_QUIT, SFEVENT_UPDATE, SFEVENT_COLLISION, SFEVENT_LAST, SFEVENT_PLAYER_MOVE};

/**
 * Abstracts away from SDL_Event so that our game event management needs no SDL-specific code.
 */
class SFEvent {
public:
  SFEvent(const SDL_Event &);
  SFEVENT GetCode();
  int     getX();
  int     getY();
  int     timer;
  bool    right;
  bool    left;
  bool    up;
  bool    down;
  int     xVel;
  int     yVel;

private:
  SFEVENT code;
  Uint8*  keys[];
};
  
#endif
