#include "SFEvent.h"

/**
 * Effectively wraps an SDL_Event in our custom event type.
 */
SFEvent::SFEvent(const SDL_Event & event) {
bool keys[4] = {0,0,0,0};
  switch (event.type) {
  case SDL_QUIT:
    code = SFEVENT_QUIT;
    break;
  case SDL_USEREVENT:
    code = SFEVENT_UPDATE;
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
      keys[0]=1;
      std::cout << keys[0];
      break;
    case SDLK_RIGHT:
      keys[1]=1;
      break;
    case SDLK_UP:
      keys[2]=1;
      break;
    case SDLK_DOWN:
      keys[3]=1;
      break;
    case SDLK_SPACE:
      code = SFEVENT_FIRE;
      break;
    case SDLK_q:
      code = SFEVENT_QUIT;
      break;
    }
  case SDL_KEYUP:
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
      keys[0]=0;
      break;
    case SDLK_RIGHT:
      keys[1]=0;
      break;
    case SDLK_UP:
      keys[2]=0;
      break;
    case SDLK_DOWN:
      keys[3]=0;
      break;
    }
   break;
  default:
    code = SFEVENT_NULL;
    break;
  }
}
SFEVENT SFEvent::Movement() {
  if(keys[0]==1){
  return SFEVENT_PLAYER_LEFT;}
  if(keys[1]==1){
  return SFEVENT_PLAYER_RIGHT;}
  if(keys[2]==1){
  return SFEVENT_PLAYER_UP;}
  if(keys[3]==1){
  return SFEVENT_PLAYER_DOWN;} else 
  return code;
}

SFEVENT SFEvent::GetCode() {
  return code;
}
