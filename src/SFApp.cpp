#include "SFApp.h"

SFApp::SFApp() {
  is_running = true;
  surface    = SDL_GetVideoSurface();
  tickoftype = 0;
  player     = make_shared<SFAsset>(SFASSET_PLAYER);
  auto player_pos = Point2(surface->w/2, 88.0f);
  player->SetPosition(player_pos);

  alien     = make_shared<SFAsset>(SFASSET_ALIEN);
  auto alien_pos = Point2(200, 200);
  alien->SetPosition(alien_pos);

  coin     = make_shared<SFAsset>(SFASSET_COIN);
  auto coin_pos = Point2(surface->w/4, 100);
  coin->SetPosition(coin_pos);
}

SFApp::~SFApp() {
}

/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
void SFApp::OnEvent(SFEvent& event) {
  SFEVENT the_event = event.GetCode();
  switch (the_event) {
  case SFEVENT_QUIT:
    is_running = false;
    break;
  case SFEVENT_UPDATE: 
    OnUpdateWorld();
    OnRender();
    tickoftype=+1;
    cout << tickoftype << endl;
    break;
  case SFEVENT_PLAYER_UP:
	player->GoNorth();
    break;

  case SFEVENT_PLAYER_LEFT:
	player->GoWest();
    break;
  case SFEVENT_PLAYER_RIGHT:
	player->GoEast();
    break;
  case SFEVENT_PLAYER_DOWN:
	player->GoSouth();
    break;
  }
}

int SFApp::OnExecute() {
  // Execute the app
  SDL_Event event;
  while (SDL_WaitEvent(&event) && is_running) {
    // if this is an update event, then handle it in SFApp,
    // otherwise punt it to the SFEventDispacher.
    SFEvent sfevent((const SDL_Event) event);
    OnEvent(sfevent);
  }
}

void SFApp::OnUpdateWorld() {
}

void SFApp::OnRender() {
  // clear the surface
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 8, 54, 129) );

  // draw the player
  player->OnRender(surface);
  coin->OnRender(surface);
  alien->OnRender(surface);

  // Switch the off-screen buffer to be on-screen
  SDL_Flip(surface);
}
