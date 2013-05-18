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
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
      break;
    case SDLK_RIGHT:
      break;
    case SDLK_UP:
      break;
    case SDLK_DOWN:
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
      break;
    case SDLK_RIGHT:
      break;
    case SDLK_UP:
      break;
    case SDLK_DOWN:
      break;
    }
   break;
  default:
    code = SFEVENT_NULL;
    break;
  }
}

SFEVENT SFEvent::GetCode() {
Uint8 *keys = SDL_GetKeyState(NULL);

  if(keys[SDLK_LEFT]){
    code = SFEVENT_PLAYER_LEFT;
    std::cout << "left pressed" << code << std::endl; 
  }
  if(keys[SDLK_RIGHT]){
    code = SFEVENT_PLAYER_RIGHT;
    std::cout << "right pressed" << code <<  std::endl;
  }
  if(keys[SDLK_UP]){
    code = SFEVENT_PLAYER_UP;
    std::cout << "up pressed" << code <<  std::endl;  
  }
  if(keys[SDLK_DOWN]){
    code = SFEVENT_PLAYER_DOWN;
    std::cout << "down pressed" << std::endl;  
  }
return code;
}
