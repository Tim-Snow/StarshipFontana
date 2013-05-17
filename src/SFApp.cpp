#include "SFApp.h"
#include <fstream>

SFApp::SFApp() {
  is_running = true;
  surface    = SDL_GetVideoSurface();
  wall	     = make_shared<SFAsset>(SFASSET_WALL);
  player     = make_shared<SFAsset>(SFASSET_PLAYER);
  coin       = make_shared<SFAsset>(SFASSET_COIN);
  alien      = make_shared<SFAsset>(SFASSET_ALIEN);
  auto player_pos = Point2(surface->w/2, 88.0f);
  player->SetPosition(player_pos);


ifstream file("assets/map.txt", ios::in);
char map_array[16][16];



string line;
for(int i=0; i< 16; i++){
file >> line;
for(int j=0; j< 16; j++){
char c = line[j];
map_array[15-i][j] = c;
std::cout << c;
	}
std::cout << endl;
}
std::cout << "this is what the array looks like" << endl;
for(int i=0; i< 16; i++){
	for(int j=0; j<16; j++){
std::cout << map_array[i][j];
}
std::cout << endl;
}

for(int i=0; i< 16; i++){
	for(int j=0; j<16; j++){
		switch(map_array[i][j]) {
		case '0':{}
			break;
		case '1': {
			coin = make_shared<SFAsset>(SFASSET_COIN);
			auto coin_pos = Point2(((40)*j)+20, ((30)*i)+45);
			coin->SetPosition(coin_pos);
      			coins.push_back(coin);
			break;
			}
		case '2':{
			wall = make_shared<SFAsset>(SFASSET_WALL);
			auto wall_pos = Point2(((40)*j)+20, ((30)*i)+45);
			wall->SetPosition(wall_pos);
    			walls.push_back(wall);
			break;
			}
		default:
		cerr << "Error in file format" << endl;
		}
	}
}

const int number_of_aliens = 2;
  for(int i=0; i<number_of_aliens; i++) {
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN);
    auto pos   = Point2(120+(400*i), 430.0f);
    alien->SetPosition(pos);
    aliens.push_back(alien);
  }
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
  Point2 p = player->GetPosition();
  int playerx = p.getX();
  int playery = p.getY();

  for(auto a : aliens){
  Point2 al = a->GetPosition();
  int alienx = al.getX();
  int alieny = al.getY();
	 if(alienx > playerx){
     a->GoWest();
   } else { a->GoEast(); }
   if(alieny > playery){
    a->GoSouth();
   } else { a->GoNorth(); }
  }

  for(auto c : coins){
    if(player->CollidesWith(c)){
		  SFEventDispacher::GetInstance().RaiseAndDispach(c->GetId(), SFEVENT_COLLISION);
      
    }
  }
  for( auto a : aliens){
    if(player->CollidesWith(a)){
      std::cout << "You Lose!" << endl;
      is_running = false;
    }
  }
  for( auto w : walls){

    if(playerx-15<0){
      playerx=0;
    }
    if(playery-15<0){
      playery=0;
    }
      
    
  }


  list<shared_ptr<SFAsset>> tmp;
  for(auto c : coins) {
    if(c->IsAlive()){
      tmp.push_back(c);
    }
  }
  coins.clear();
  coins = list<shared_ptr<SFAsset>>(tmp);  
}

void SFApp::OnRender() {
  // clear the surface
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 8, 54, 129) );

  // draw the player
    for(auto w: walls){
	w->OnRender(surface);
	}
    for(auto c: coins) {
    	if(c->IsAlive()) {c->OnRender(surface);}
  	}
    for(auto a: aliens){
	if(a->IsAlive()) {a->OnRender(surface);}
	}
  player->OnRender(surface);
  // Switch the off-screen buffer to be on-screen
  SDL_Flip(surface);
}
