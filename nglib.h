// nglib.h
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
using namespace std;

// nglf.cpp
int gcd(int a, int b);
int lcm(int a, int b);

struct fraction{
  // main: full part; numerator; denominator;
  int fp = 0, num = 0, denom = 0;

  // miscellaneous: last divider; 
  
  int ld = 0;

  void reduce(){
     ld = gcd(num, denom);
     num /= ld;
     denom /= ld;      
  }

  void toimproperfraction(){
    num = denom * fp + num;
    fp = 0;
  }

  void tomixedfraction(){
    fp = num / denom;
    num %= denom;
  }

  void decimaltofraction(double decimal){
    denom = 1e6;
    num = (int)(decimal * denom);
    reduce();
  }

  void printfpnumcdenom(bool wendl){
    cout << fp << " " << num << "/" << denom;
    if (wendl) cout << endl;
  }

  void printnumdenom(bool wendl){
    cout << num << "/" << denom;
    if (wendl) cout << endl;
  }
};

fraction addfraction(fraction first, fraction second);
fraction subfraction(fraction first, fraction second);
fraction mulfraction(fraction first, fraction second);
fraction divfraction(fraction first, fraction second);
int getranum(int min, int max);
int mainsi();
int nglci();
