#include "SFEvent.h"

/**
 * Effectively wraps an SDL_Event in our custom event type.
 */

SFEvent::SFEvent(const SDL_Event & event) {
  switch (event.type) {
  case SDL_QUIT:
    code = SFEVENT_QUIT;
    break;
  case SDL_USEREVENT:
    code = SFEVENT_UPDATE;
    break;
  /*case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
      keys[0]=true;
std::cout << keys[0];
      break;
    case SDLK_RIGHT:
      keys[1]=true;
      break;
    case SDLK_UP:
      keys[2]=true;
      break;
    case SDLK_DOWN:
      keys[3]=true;
      break;
    case SDLK_SPACE:
      code = SFEVENT_FIRE;
      break;*/
    case SDLK_q:
      code = SFEVENT_QUIT;
      break;
    //}

/*
  case SDL_KEYUP:
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
      keys[0]=false;
std::cout << keys[0];
      break;
    case SDLK_RIGHT:
      keys[1]=false;
std::cout << keys[1];
      break;
    case SDLK_UP:
      keys[2]=false;
std::cout << keys[2];
      break;
    case SDLK_DOWN:
      keys[3]=false;
std::cout << keys[3];
      break;
    }*/
   //break;
  default:
    code = SFEVENT_NULL;
    break;
  }
}
SFEVENT SFEvent::Movement(){
Uint8 *keys = SDL_GetKeyState(NULL);

  if(keys[SDLK_LEFT]){
    code = SFEVENT_PLAYER_LEFT;
    std::cout << "left pressed" << code << std::endl;
    return code;  
  }
  if(keys[SDLK_RIGHT]){
    code = SFEVENT_PLAYER_RIGHT;
    std::cout << "right pressed" << code <<  std::endl;
    return code;
  }
  if(keys[SDLK_UP]){
    code = SFEVENT_PLAYER_UP;
    std::cout << "up pressed" << code <<  std::endl;  
    return code;
  }
  if(keys[SDLK_DOWN]){
    code = SFEVENT_PLAYER_DOWN;
    std::cout << "down pressed" << std::endl;  
    return code;
  }
}
SFEVENT SFEvent::GetCode() {
  return code;
}
