// ngraphicsl.cpp
// si - sdl interface

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "nglib.h"
#include <vector>
using namespace std;

#define WINDOWNAME "ngraphicsl"
#define WINDOWPOSX SDL_WINDOWPOS_CENTERED
#define WINDOWPOSY SDL_WINDOWPOS_CENTERED
#define WINDOWWIDTH 1280
#define WINDOWHEIGHT 720
#define WINDOWFLAGS SDL_WINDOW_SHOWN

#define RENDERERINDEX -1
#define RENDERERFLAGS SDL_RENDERER_ACCELERATED

// laspo - last point

struct point{
  int index;
  int x, y;
  void render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoint(renderer, x, y);
  }
};

vector<point> points;

void renpo(SDL_Renderer* renderer, const vector<point>& points){
  for (const auto&p:points) p.render(renderer);
}

void cifsi(){
  string action;
  cin >> action;
  if (action == "new"){
    points.push_back({});
    point& laspo = points.back();
    cin >> laspo.x >> laspo.y;
    laspo.index = points.size();
    cout << "index, x, y: " << laspo.index << " " << laspo.x << " " << laspo.y << endl;
  }
}

int mainsi(){
  // load sdl libs
  if (SDL_Init(SDL_INIT_VIDEO) < 0) { cout << "error sdl init video" << endl; return 1;}

  // creating 
  SDL_Window* window = nullptr;
  cout << "window created" << endl;
  SDL_Renderer* renderer = nullptr;
  cout << "renderer created" << endl;

  // init
  window = SDL_CreateWindow(WINDOWNAME, WINDOWPOSX, WINDOWPOSY, WINDOWWIDTH, WINDOWHEIGHT, WINDOWFLAGS);
  if (window == nullptr) { cout << "error init window"; return 1; }
  else cout << "window inited" << endl;
  renderer = SDL_CreateRenderer(window, RENDERERINDEX, RENDERERFLAGS);
  if (renderer == nullptr) { cout << "error init renderer"; return 1; }
  else cout << "renderer inited" << endl;

  // create here objects


  // cycle
  bool running = true;
  SDL_Event event;
  while (running){
    while (SDL_PollEvent(&event)){
      if (event.type == SDL_QUIT) running = false; 
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    cifsi();
    renpo(renderer, points);

    SDL_RenderPresent(renderer); 
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
