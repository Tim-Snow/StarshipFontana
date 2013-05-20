#ifndef SFSTATE_H
#define SFSTATE_H

#include <SDL/SDL.h>
#include <iostream>

enum GameStates{
STATE_INTRO,
STATE_WIN,
STATE_LOSE,
STATE_PLAY
};

class SFState {
public:
  SFState(int);
  int SFUpdate(int);
  int GetCode();

private:
  int code;
};
#endif
