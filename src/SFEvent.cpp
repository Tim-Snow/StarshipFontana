#include "SFEvent.h"

/**
 * Effectively wraps an SDL_Event in our custom event type.
 */
SFEvent::SFEvent(const SDL_Event & event) {
bool keys[323] = {false};
if(keys[SDLK_LEFT]){
code= SFEVENT_PLAYER_LEFT;
}
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
      keys[event.key.keysym.sym] = true;
      code = SFEVENT_PLAYER_LEFT;
      break;
    case SDLK_RIGHT:
      keys[event.key.keysym.sym] = true;
      code = SFEVENT_PLAYER_RIGHT;
      break;
    case SDLK_UP:
      keys[event.key.keysym.sym] = true;
      code = SFEVENT_PLAYER_UP;
      break;
    case SDLK_DOWN:
      keys[event.key.keysym.sym] = true;
      code = SFEVENT_PLAYER_DOWN;
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
      keys[event.key.keysym.sym] = false;
      break;
    case SDLK_RIGHT:
      keys[event.key.keysym.sym] = false;
      break;
    case SDLK_UP:
      keys[event.key.keysym.sym] = false;
      break;
    case SDLK_DOWN:
      keys[event.key.keysym.sym] = false;
      break;
    }
    break;
  default:
    code = SFEVENT_NULL;
    break;
  }
}

SFEVENT SFEvent::GetCode() {
  return code;
}
