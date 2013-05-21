#include "SFApp.h"
#include <fstream>

SFApp::SFApp() {
  is_running = true;
  surface    = SDL_GetVideoSurface();
  wall	     = make_shared<SFAsset>(SFASSET_WALL);
  lose       = make_shared<SFAsset>(SFASSET_LOSE);
  win        = make_shared<SFAsset>(SFASSET_WIN);
  intro      = make_shared<SFAsset>(SFASSET_INTRO);
  player     = make_shared<SFAsset>(SFASSET_PLAYER);
  coin       = make_shared<SFAsset>(SFASSET_COIN);
  alien      = make_shared<SFAsset>(SFASSET_ALIEN);

  auto player_pos = Point2(surface->w/2, 100.0f);
  auto lose_pos   = Point2(surface->w/2, 450.0f);
  lose->SetPosition(lose_pos);
  win->SetPosition(lose_pos);
  intro->SetPosition(lose_pos);
  player->SetPosition(player_pos);

  ifstream file("assets/map.txt", ios::in);
  char map_array[15][20];
  string line;
  for(int i=0; i< 15; i++){
    file >> line;
    for(int j=0; j< 20; j++){
      char c = line[j];
      map_array[14-i][j] = c;
      std::cout << c;
	  }
    std::cout << endl;
  }//this reads in a text file which stores the level format, it scans through and assigns each value to an array

  for(int i=0; i< 15; i++){ //the array is then scanned through and relevent tiles are placed, 0 is blank, 1 is a coin, 2 is a wall
	  for(int j=0; j<20; j++){
		  switch(map_array[i][j]) {
		  case '0':
			  break;
		  case '1': {
			  coin = make_shared<SFAsset>(SFASSET_COIN);
			  auto coin_pos = Point2(((32)*j)+15, ((32)*i)+48);
			  coin->SetPosition(coin_pos);
        coins.push_back(coin);
			  break;
			  }
		  case '2':{
			  wall = make_shared<SFAsset>(SFASSET_WALL);
			  auto wall_pos = Point2(((32)*j)+15, ((32)*i)+48);
			  wall->SetPosition(wall_pos);
        walls.push_back(wall);
			  break;
			  }
		  default:
		  cerr << "Error in file format" << endl;
		  }
	  }
  }
  const int number_of_aliens = 3;
  for(int i=0; i<number_of_aliens; i++) {
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN);
    auto pos   = Point2(120+(200*i), 400.0f);
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
  int xVel = event.getX();
  int yVel = event.getY();
  SFEVENT the_event = event.GetCode();
  switch(state){
    case 0://intro state
      switch (the_event) {
        case SFEVENT_QUIT:
          std::cout << "You quit, game not started";
          is_running = false;
          break;
        case SFEVENT_UPDATE:
          OnRender(0);
          break;
        case SFEVENT_PLAYER_MOVE:
          state=1;       
          break;
        }
      break;

    case 1://game in progress
      switch (the_event) {
      case SFEVENT_QUIT:
        std::cout << "You quit, score: " << score;
        is_running = false;
        break;
      case SFEVENT_UPDATE:
        OnUpdateWorld();
        OnRender(1);
        break;
      case SFEVENT_PLAYER_MOVE:
        player->GoDir(xVel, yVel);       
        break;
      }
    break;

    case 2://lose state
      switch (the_event) {
      case SFEVENT_QUIT:
        std::cout << "You died, score: " << score;
        is_running = false;
        break;
      case SFEVENT_UPDATE:
        OnUpdateWorld();
        OnRender(2);
        break;
      }
      break;

    case 3://win state
      switch (the_event) {
      case SFEVENT_QUIT:
        std::cout << "You won, score: " << score;
        is_running = false;
        break;
      case SFEVENT_UPDATE:
        OnUpdateWorld();
        OnRender(3);
        break;
      }
    break;
    default:0;
  }

  for(auto w : walls){ //if the player collides with a wall, reverse position
    if(player->CollidesWith(w)){
      collision=true;
      player->GoDir(-xVel, -yVel);
    }
  }
}

int SFApp::OnExecute() {
  // Execute the app
  SDL_Event event;
  score = 0;
  while (SDL_WaitEvent(&event) && is_running) {
    // if this is an update event, then handle it in SFApp,
    // otherwise punt it to the SFEventDispacher.
    SFEvent sfevent((const SDL_Event) event);
    OnEvent(sfevent);
  }
}

void SFApp::OnUpdateWorld() {
  
  for(auto c : coins){//coin collision
    if(player->CollidesWith(c)){
      score+=50;
      std::cout << score << std::endl;
  	  SFEventDispacher::GetInstance().RaiseAndDispach(c->GetId(), SFEVENT_COLLISION);  
    }
  }
  list<shared_ptr<SFAsset>> tmp;
  for(auto c : coins) {//remove coin from list
    if(c->IsAlive()){
      tmp.push_back(c);
    }
  }
  coins.clear();
  coins = list<shared_ptr<SFAsset>>(tmp); 
  if(coins.size() == 0){ //when there are no more coins, set game state to win
    state=3;
  }

 for(auto a : aliens){
   int alienVX = 1;
   int alienVY = 1;
    for(auto w : walls){
      Point2 pl    = player->GetPosition();
      Point2 al   = a->GetPosition();
      int alienx  = al.getX();
      int alieny  = al.getY();
      int playerx = pl.getX();
      int playery = pl.getY();

      if(alienx > playerx){//extremely basic ai, goes to player position
        alienVX = -1;
      } else { alienVX=1; }
      if(alieny > playery){
        alienVY=-1;
      } else { alienVY=1; }
    }
    if(player->CollidesWith(a)){  
      state=2;   
    }
  a->GoDir(alienVX,alienVY);    
  }
}

void SFApp::OnRender(int x) {
  if(x==0){//intro screen
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 8, 54, 129) );
    player->OnRender(surface);
    intro->OnRender(surface);
    for(auto w: walls){
	    w->OnRender(surface);
	  }
    for(auto a: aliens){
      a->OnRender(surface);
	  } 
  SDL_Flip(surface); 
  }
  if(x==1){
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 8, 54, 129) );
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
    SDL_Flip(surface);
  }
  if(x==2){//lose screen
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0) );
    lose->OnRender(surface); 
    SDL_Flip(surface);
  }
  if(x==3){//win screen
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 133, 133) );
    win->OnRender(surface);
    SDL_Flip(surface);
  }
}
