#include "SFEvent.h"
/**
 * Effectively wraps an SDL_Event in our custom event type.
 */

SFEvent::SFEvent(const SDL_Event & event) {
Uint8* keys = SDL_GetKeyState(NULL);
if(keys[SDLK_RIGHT]){
  right = true;
} else right = false;
if(keys[SDLK_LEFT]){
  left = true;
} else left = false;
if(keys[SDLK_UP]){
  up = true;
} else up = false;
if(keys[SDLK_DOWN]){
  down = true;
} else down = false;

switch (event.type) {
  case SDL_QUIT:
    code = SFEVENT_QUIT;
    break;
  case SDL_USEREVENT:
    code = SFEVENT_UPDATE;
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_SPACE:
      code = SFEVENT_FIRE;
      break;
    case SDLK_q:
      code = SFEVENT_QUIT;
      break;
   }
   break;
  default:
    code = SFEVENT_NULL;
    break;
    
  }
}
int SFEvent::getX(){
if(right==true){
xVel=2;}
if(left==true){
xVel=-2;}
else if(left==false&&right==false){
xVel=0;}
return xVel;
}
int SFEvent::getY(){
if(up==true){
yVel=2;}
if(down==true){
yVel=-2;}
else if(up==false&&down==false){
yVel=0;}
return yVel;
}

SFEVENT SFEvent::GetCode() {
if(timer==1){
 code=SFEVENT_UPDATE;
timer=0;
} else if(right==true){
 code=SFEVENT_PLAYER_RIGHT;
timer=1;
} else if(left==true){
  code=SFEVENT_PLAYER_LEFT;
timer=1;
} else if(up==true){
  code=SFEVENT_PLAYER_UP;
  timer=1;
} else if(down==true){
  code=SFEVENT_PLAYER_DOWN;
  timer=1;
}

return code;
}
