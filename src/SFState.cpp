#include "SFState.h"

SFState::SFState(int x) {


  switch (x) {
    case 0:
      code = STATE_INTRO;
    case 1:
      code = STATE_PLAY;
    case 2:
      code = STATE_LOSE;
    case 3:
      code = STATE_WIN;
  }
}
  int Update(int x){
    int coinListSize = x;
    if(coinListSize==0){
      SFState(3);
    } else SFState(1);
  }

int SFState::GetCode(){
  return code;
}
