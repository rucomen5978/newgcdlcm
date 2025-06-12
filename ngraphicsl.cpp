// ngraphicsl.cpp
// si - sdl interface

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "nglib.h"
#include <algorithm>
#include <vector>
#include <iostream>
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

struct line{
  int index;
  int index1, index2;
  void render(SDL_Renderer* renderer, const vector<point>& points) const{
    if (index1 >= 1 && index1 <= points.size() && index2 >= 1 && index2 <= points.size()){
      const point& p1 = points[index1 - 1];
      const point& p2 = points[index2 - 1];
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
    } 
  } 
};

vector<point> points;
vector<line> lines;

void renderall(SDL_Renderer* renderer, const vector<point>& points, const vector<line>& lines){
  for (const auto& p : points) {
    p.render(renderer); 
  }

  for (const auto& l : lines){
    l.render(renderer, points); 
  }
}

void delpo(int index){
  if (index >= 1 && index <= points.size()){
    points.erase(points.begin() + index - 1); 
    for (size_t i = 0; i < points.size(); ++i) {
      points[i].index = i + 1; 
    }

    lines.erase(remove_if(lines.begin(), lines.end(), [index](const line& l) { return l.index1 == index || l.index2 == index;}), lines.end());

    for (size_t i = 0; i < lines.size(); ++i) lines[i].index = i + 1;
  } else cout << "invalid index" << endl;
}

void cifsi(){
  string action;
  cin >> action;
  // new point
  if (action == "newpo"){
    points.push_back({});
    point& laspo = points.back();
    cin >> laspo.x >> laspo.y;
    laspo.index = points.size();
    cout << "index, x, y: " << laspo.index << " " << laspo.x << " " << laspo.y << endl;
  }

  // new random point
  if (action == "newrapo"){
    points.push_back({});
    point& laspo = points.back();
    int minx, maxx, miny, maxy;
    cin >> minx >> maxx >> miny >> maxy;
    laspo.x = getranum(minx, maxx);
    laspo.y = getranum(miny, maxy);
    laspo.index = points.size();
    cout << "index, x, y: " << laspo.index << " " << laspo.x << " " << laspo.y << endl;
  }

  // new random point full screen
  if (action == "rpfs"){
    points.push_back({});
    point& laspo = points.back();
    laspo.x = getranum(0, WINDOWWIDTH);
    laspo.y = getranum(0, WINDOWHEIGHT);
    laspo.index = points.size();
    cout << "index, x, y: " << laspo.index << " " << laspo.x << " " << laspo.y << endl;
  }

  // edit point
  if (action == "edipo"){
    int index, newx, newy;
    cin >> index >> newx >> newy;
    points[index - 1].x = newx;
    points[index - 1].y = newy; 
    cout << "index, newx, newy: " << index << " " << points[index - 1].x << " " << points[index - 1].y << endl;
  }
  
  // new line
  if (action == "newli" || action == "nl"){
    int index1, index2;
    cin >> index1 >> index2;
    lines.push_back({static_cast<int>(lines.size() + 1), index1, index2});
    cout << "indexli, indexpo1, indexpo2: " << lines.back().index << " " << index1 << " " << index2 << endl;
  }

  // info line
  if (action == "infoli"){
    int indexli;
    cin >> indexli;
    cout << "index1, index2: " << lines[indexli - 1].index1 << " " << lines[indexli - 1].index2 << endl; 
  }

  // print all lines
  if (action == "pali"){
    for (const auto& l : lines){
      cout << "indexli, index1, index2: " << l.index << " " << l.index1 << " " << l.index2 << endl; 
    } 
  }

  // edit line
  if (action == "edili"){
    int indexli, newi1, newi2;
    cin >> indexli >> newi1 >> newi2;
    lines[indexli - 1].index1 = newi1;
    lines[indexli - 1].index2 = newi2; 
    cout << "indexli, newi1, newi2: " << indexli << " " << lines[indexli - 1].index1 << " " << lines[indexli - 1].index2 << endl; 
  }
  
  // info index
  if (action == "infopo"){
    int index;
    cin >> index;
    cout << "x: " << points[index - 1].x << endl << "y: " << points[index - 1].y << endl;
  }

  // print all points
  if (action == "papo"){
    for (const auto& p : points){
      cout << "index, x, y: " << p.index << " " << p.x << " " << p.y << endl;
    } 
  }

  // delete po
  if (action == "delpo"){
    int index;
    cin >> index;
    delpo(index);
  }

  // connect all points
  if (action == "cap"){
    lines.clear();
    int lineindex = 1;
    for (size_t i = 0; i < points.size(); ++i){
      for (size_t j = i + 1; j < points.size(); ++j) {
        lines.push_back({lineindex++, static_cast<int>(i + 1), static_cast<int>(j + 1)}) ;
      } 
    }

    cout << "created: " << lines.size() << " lines" << endl;
  }

  // delete points and lines
  if (action == "dpal"){
    points.clear();
    lines.clear();
  }

  // loop rpfs
  if (action == "lrpfs"){
    int count;
    cin >> count;
    for (int i = 0; i < count; i++){
      points.push_back({});
      point& laspo = points.back();
      laspo.x = getranum(0, WINDOWWIDTH);
      laspo.y = getranum(0, WINDOWHEIGHT);
      laspo.index = points.size();
      cout << "index, x, y: " << laspo.index << " " << laspo.x << " " << laspo.y << endl;
    } 
  }

  // loop newrapo
  if (action == "lnewrapo"){
    int count, minx, maxx, miny, maxy;
    cin >> count >> minx >> maxx >> miny >> maxy;
    for (int i = 0; i < count; i++){
      points.push_back({});
      point& laspo = points.back();
      laspo.x = getranum(minx, maxx);
      laspo.y = getranum(miny, maxy);
      laspo.index = points.size();
      cout << "index, x, y: " << laspo.index << " " << laspo.x << " " << laspo.y << endl; 
    }
  }

  // enable console interface
  if (action == "eci"){
    nglci();     
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
    renderall(renderer, points, lines);

    SDL_RenderPresent(renderer); 
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
