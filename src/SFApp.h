#ifndef SFAPP_H
#define SFAPP_H

#include <memory>   // Pull in std::shared_ptr
#include <iostream> // Pull in std::cerr, std::endl

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFAsset.h"

/**
 * Represents the StarshipFontana application.  It has responsibilities for
 * * Creating and destroying the app window
 * * Processing game events
 */
class SFApp {
public:
  SFApp();
  virtual ~SFApp();
  void    OnEvent(SFEvent &);
  int     OnExecute();
  void    OnUpdateWorld();
  void    OnRender();

private:
  SDL_Surface           * surface;
  bool                    is_running;
  char		 	  map_array[16][12];
  shared_ptr<SFAsset>     wall;
  shared_ptr<SFAsset>     player;
  shared_ptr<SFAsset>     coin;
  shared_ptr<SFAsset>     alien;
  list<shared_ptr<SFAsset> > walls;
  list<shared_ptr<SFAsset> > coins;
  list<shared_ptr<SFAsset> > aliens;
  uint		  	  tickoftype;
  SFError OnInit();
};
#endif
