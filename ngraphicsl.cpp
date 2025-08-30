// ngraphicsl.cpp
// si - sdl interface

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include "nglib.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <unistd.h>
using namespace std;

#define WINDOWNAME "ngraphicsl"
#define tpo points[index-1]
int WINDOWPOSX = SDL_WINDOWPOS_CENTERED;
int WINDOWPOSY = SDL_WINDOWPOS_CENTERED;
int WINDOWWIDTH = 1280;
int WINDOWHEIGHT = 720;
#define WINDOWFLAGS SDL_WINDOW_SHOWN

int COORD_SCALE = 1;
int CENTER_X = 0;
int CENTER_Y = 0;
bool INVERT_Y = 0;

void transformcoords(int& x, int& y) {
    x = x * COORD_SCALE + CENTER_X;
    if (INVERT_Y) {
        y = CENTER_Y - y * COORD_SCALE;
    } else {
        y = y * COORD_SCALE + CENTER_Y;
    }
}

void inversetransformcoords(int& x, int& y) {
    x = (x - CENTER_X) / COORD_SCALE;
    if (INVERT_Y) {
        y = (CENTER_Y - y) / COORD_SCALE;
    } else {
        y = (y - CENTER_Y) / COORD_SCALE;
    }
}

#define RENDERERINDEX -1
#define RENDERERFLAGS SDL_RENDERER_ACCELERATED

// laspo - last point

void startsici() {
    cout << "WINDOWPOSX (0 centred): ";
    cin >> WINDOWPOSX;
    cout << "WINDOWPOSY (0 centred): ";
    cin >> WINDOWPOSY;
    cout << "WINDOW WIDTH (0 - 1280): ";
    cin >> WINDOWWIDTH;
    cout << "WINDOW HEIGHT (0 - 720): ";
    cin >> WINDOWHEIGHT;
    if (WINDOWPOSX == 0) WINDOWPOSX = SDL_WINDOWPOS_CENTERED;
    if (WINDOWPOSY == 0) WINDOWPOSY = SDL_WINDOWPOS_CENTERED;
    if (WINDOWWIDTH == 0) WINDOWWIDTH = 1280;
    if (WINDOWHEIGHT == 0) WINDOWHEIGHT = 720;
    mainsi();
}

struct point{
    int index;
    int x, y;
    int size = 0;
    // formpo:
    // 0 - square
    // 1 - circle
    int formpo = 0;
    Uint8 r = 255;
    Uint8 g = 255;
    Uint8 b = 255;
    Uint8 a = 255;
    void render(SDL_Renderer* renderer) const {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        if (formpo == 1){
            for (int w = -size; w <= size; w++){
                for (int h = -size; h <= size; h++){
                    if (w*w + h*h <= size*size){
                        SDL_RenderDrawPoint(renderer, x + w, y + h);
                    }
                }
            }
        }
        if (formpo == 0){
            SDL_Rect rect = {x - size, y - size, 2*size + 1, 2*size + 1};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
};

struct line{
    int index;
    int index1, index2;
    Uint8 r = 255;
    Uint8 g = 255;
    Uint8 b = 255;
    Uint8 a = 255;
    void render(SDL_Renderer* renderer, const vector<point>& points) const{
        if (index1 >= 1 && index1 <= points.size() && index2 >= 1 && index2 <= points.size()){
            const point& p1 = points[index1 - 1];
            const point& p2 = points[index2 - 1];
            SDL_SetRenderDrawColor(renderer, r, g, b, a);
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

double calculateAngle(int x1, int y1, int x2, int y2, int x3, int y3) {
    int vec1_x = x1 - x2;
    int vec1_y = y1 - y2;
    
    int vec2_x = x3 - x2;
    int vec2_y = y3 - y2;
    
    double dotProduct = vec1_x * vec2_x + vec1_y * vec2_y;
    
    double mag1 = sqrt(vec1_x * vec1_x + vec1_y * vec1_y);
    double mag2 = sqrt(vec2_x * vec2_x + vec2_y * vec2_y);
    
    if (mag1 > 0 && mag2 > 0) {
        double cosAngle = dotProduct / (mag1 * mag2);
        cosAngle = max(-1.0, min(1.0, cosAngle));
        
        return acos(cosAngle) * 180.0 / M_PI;
    }
    
    return -1;
}

bool isClicked(int mx, int my, int rx, int ry, int rw, int rh){ return (mx >= rx && mx <= (rx + rw) && my >= ry && my <= (ry + rh)); }

bool waitingforclick = false;
int newpointsize = 1;
int newpointform = 0;

void cifsi(SDL_Renderer* renderer, int mouseX, int mouseY, SDL_Event event){
    string action;
    cin >> action;
    // new point
    if (action == "newpo"){
        points.push_back({});
        point& laspo = points.back();
        cin >> laspo.x >> laspo.y;
        transformcoords(laspo.x, laspo.y);
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
        transformcoords(laspo.x, laspo.y);
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
        transformcoords(points[index - 1].x, points[index - 1].y);
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


    if (action == "setcolorline" || action == "scl"){
        int index, r, g, b, a = 255;
        cin >> index >> r >> g >> b;
        if (cin.peek() != '\n'){
          cin >> a; 
        } 

        if (index >= 1 && index <= lines.size()){
          lines[index-1].r = static_cast<Uint8>(r);
          lines[index-1].g = static_cast<Uint8>(g);
          lines[index-1].b = static_cast<Uint8>(b);
          lines[index-1].a = static_cast<Uint8>(a);
          cout << "line " << index << " color set to: (" << r << ", " << g << ", " << b << ", " << a << ")" << endl;
        }
    }

    // info index
    if (action == "infopo"){
        int index;
        cin >> index;
        cout << "x: " << points[index - 1].x << endl << "y: " << points[index - 1].y << endl << "size: " << points[index - 1].size << endl << "form: " << points[index - 1].formpo << endl << "r: " << points[index-1].r << endl
        << "g: " << tpo.g << endl << "b: " << tpo.b << endl << "a: " << tpo.a << endl;
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
        int count, delay_ms;
        cin >> count >> delay_ms;
        for (int i = 0; i < count; i++){
            points.push_back({});
            point& laspo = points.back();
            laspo.x = getranum(0, WINDOWWIDTH);
            laspo.y = getranum(0, WINDOWHEIGHT);
            laspo.index = points.size();
            cout << "index, x, y: " << laspo.index << " " << laspo.x << " " << laspo.y << endl;

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            renderall(renderer, points, lines);
            SDL_RenderPresent(renderer);
            SDL_Delay(delay_ms);
        }
    }

    if (action == "lrpfscap"){
        int count, delay_ms;
        cin >> count >> delay_ms;
        for (int i = 0; i < count; i++){
            points.push_back({});
            point& laspo = points.back();
            laspo.x = getranum(0, WINDOWWIDTH);
            laspo.y = getranum(0, WINDOWHEIGHT);
            laspo.index = points.size();
            cout << "index, x, y: " << laspo.index << " " << laspo.x << " " << laspo.y << endl;
            lines.clear();
            int lineindex = 1;
            for (size_t i = 0; i < points.size(); ++i){
                for (size_t j = i + 1; j < points.size(); ++j) {
                    lines.push_back({lineindex++, static_cast<int>(i + 1), static_cast<int>(j + 1)}) ;
                }
            }
            cout << "created: " << lines.size() << " lines" << endl;

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            renderall(renderer, points, lines);
            SDL_RenderPresent(renderer);
            SDL_Delay(delay_ms);
        }
    }

    // loop newrapo
    if (action == "lnewrapo"){
        int count, delay_ms, minx, maxx, miny, maxy;
        cin >> count >> delay_ms >> minx >> maxx >> miny >> maxy;
        for (int i = 0; i < count; i++){
            points.push_back({});
            point& laspo = points.back();
            laspo.x = getranum(minx, maxx);
            laspo.y = getranum(miny, maxy);
            laspo.index = points.size();
            cout << "index, x, y: " << laspo.index << " " << laspo.x << " " << laspo.y << endl;

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            renderall(renderer, points, lines);
            SDL_RenderPresent(renderer);
            SDL_Delay(delay_ms);
        }
    }

    // loop newrapo connect all points
    if (action == "lnewrapocap"){
        int count, delay_ms, minx, maxx, miny, maxy;
        cin >> count >> delay_ms >> minx >> maxx >> miny >> maxy;
        for (int i = 0; i < count; i++){
            points.push_back({});
            point& laspo = points.back();
            laspo.x = getranum(minx, maxx);
            laspo.y = getranum(miny, maxy);
            laspo.index = points.size();
            cout << "index, x, y: " << laspo.index << " " << laspo.x << " " << laspo.y << endl;

            lines.clear();
            int lineindex = 1;
            for (size_t i = 0; i < points.size(); ++i){
                for (size_t j = i + 1; j < points.size(); ++j) {
                    lines.push_back({lineindex++, static_cast<int>(i + 1), static_cast<int>(j + 1)}) ;
                }
            }

            cout << "created: " << lines.size() << " lines" << endl;

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            renderall(renderer, points, lines);
            SDL_RenderPresent(renderer);
            SDL_Delay(delay_ms);
        }
    }

    if (action == "setpointstyle" || action == "sps"){
        int index, newSize, form;
        cin >> index >> newSize >> form;
        points[index-1].size = newSize;
        points[index-1].formpo = form;
        cout << "index: newsize: newform" << index << " " << newSize << " " << form << endl;
    }

    if (action == "setcolorpoint" || action == "scp"){
        int index, r, g, b, a = 255;
        cin >> index >> r >> g >> b;
        if (cin.peek() != '\n'){
          cin >> a; 
        } 

        if (index >= 1 && index <= points.size()){
          points[index-1].r = static_cast<Uint8>(r);
          points[index-1].g = static_cast<Uint8>(g);
          points[index-1].b = static_cast<Uint8>(b);
          points[index-1].a = static_cast<Uint8>(a); 

        }
        cout << "index: r: g: b: a: " << index << " " << r << " " << g << " " << b << " " << a << endl;
        
    }

    // enable console interface
    if (action == "eci"){
        nglci();
    }

    if (action == "setscreencenter" || action == "scc"){
        cin >> CENTER_X >> CENTER_Y >> INVERT_Y;

        for (auto& p : points){
            int absX = p.x;
            int absY = p.y;
            inversetransformcoords(absX, absY);
            p.x = absX;
            p.y = absY;
            transformcoords(p.x, p.y);
        }
        cout << "center set to: x; y; invert_y: " << CENTER_X << " " << CENTER_Y << " " << INVERT_Y << endl;
    }

    if (action == "setscale"){
        cin >> COORD_SCALE;
        for (auto& p : points){
            int logicalX = p.x;
            int logicalY = p.y;
            inversetransformcoords(logicalX, logicalY);
            p.x = logicalX;
            p.y = logicalY;
            transformcoords(p.x, p.y);
        }
        cout << "scale set to 1:" << COORD_SCALE << endl;
    }

    if (action == "measureangle" || action == "ma") {
    int vertexIndex, point1Index, point2Index;
    cin >> vertexIndex >> point1Index >> point2Index;
    
    if (vertexIndex < 1 || vertexIndex > points.size() || 
        point1Index < 1 || point1Index > points.size() || 
        point2Index < 1 || point2Index > points.size()) {
        cout << "invalid point index" << endl;
        } else {
        const point& vertex = points[vertexIndex - 1];
        const point& p1 = points[point1Index - 1];
        const point& p2 = points[point2Index - 1];
        
        double angle = calculateAngle(p1.x, p1.y, vertex.x, vertex.y, p2.x, p2.y);
        
        if (angle >= 0) {
            cout << "angle at point " << vertexIndex << " between points " 
                 << point1Index << " and " << point2Index << ": " 
                 << angle << " degrees" << endl;
        } else {
            cout << "cannot calculate angle - zero vectors" << endl;
        }
    }

    if (action == "measureanglelines" || action == "mal") {
      int lineIndex1, lineIndex2;
      cin >> lineIndex1 >> lineIndex2;

      if (lineIndex1 < 1 || lineIndex1 > lines.size() || 
          lineIndex2 < 1 || lineIndex2 > lines.size()) {
        cout << "invalid line index" << endl;
      } else {
        const line& l1 = lines[lineIndex1 - 1];
        const line& l2 = lines[lineIndex2 - 1];

        if (l1.index1 >= 1 && l1.index1 <= points.size() && 
            l1.index2 >= 1 && l1.index2 <= points.size() &&
            l2.index1 >= 1 && l2.index1 <= points.size() && 
            l2.index2 >= 1 && l2.index2 <= points.size()) {

          const point& p11 = points[l1.index1 - 1];
          const point& p12 = points[l1.index2 - 1];
          const point& p21 = points[l2.index1 - 1];
          const point& p22 = points[l2.index2 - 1];

          // Находим направляющие векторы линий
          int vec1_x = p12.x - p11.x;
          int vec1_y = p12.y - p11.y;
          int vec2_x = p22.x - p21.x;
          int vec2_y = p22.y - p21.y;

          double angle = calculateAngle(p11.x + vec1_x, p11.y + vec1_y, 
              p11.x, p11.y, 
              p21.x + vec2_x, p21.y + vec2_y);

          if (angle >= 0) {
            cout << "angle between line " << lineIndex1 << " and line " 
              << lineIndex2 << ": " << angle << " degrees" << endl;
          } else {
            cout << "cannot calculate angle - zero vectors" << endl;
          }
        } else {
          cout << "invalid point indices in lines" << endl;
        }
      }
    } 
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
    int mouseX, mouseY;
    while (running){
        SDL_GetMouseState(&mouseX, &mouseY);
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) running = false;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        cifsi(renderer, mouseX, mouseY, event);
        renderall(renderer, points, lines);

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
