// ngl console interface
// nglci.cpp

#include "nglib.h"
#include <iostream>
#include <cmath>
using namespace std;

void addci(){
  long double fn, sn;
  cin >> fn >> sn;
  cout << fn + sn << endl;
}

void subci(){
  long double fn, sn;
  cin >> fn >> sn;
  cout << fn - sn << endl; 
}

void mulci(){
  long double fn, sn;
  cin >> fn >> sn;
  cout << fn * sn << endl;
}

void divci(){
  long double fn, sn;
  cin >> fn >> sn;
  cout << fn / sn << endl;
}

void powci(){
  long double num, degree;
  cin >> num >> degree;
  cout << powl(num, degree) << endl;
}

void rodci(){
  int fn, sn;
  cin >> fn >> sn;
  cout << fn % sn << endl;
}

void gcdci(){
  int fn, sn;
  cin >> fn >> sn;
  cout << gcd(fn, sn) << endl;
}

void lcmci(){
  int fn, sn;
  cin >> fn >> sn;
  cout << lcm(fn, sn) << endl;
}

void sinci(){
  long double fn;
  cin >> fn;
  cout << sinl(fn) << endl;
}

void cosci(){
  long double fn;
  cin >> fn;
  cout << cosl(fn) << endl;
}

void tanci(){
  long double fn;
  cin >> fn;
  cout << tanl(fn) << endl;
}

void rtci(){
  long double num, root;
  cin >> num >> root;
  cout << powl(num, 1/root) << endl;
}

void rdci(){
  fraction frac;
  cin >> frac.num >> frac.denom;
  frac.reduce();
  cout << frac.num << "/" << frac.denom << endl;
}

void itmci(){
  fraction frac;
  cin >> frac.num >> frac.denom;
  frac.tomixedfraction();
  cout << frac.fp << " " << frac.num << "/" << frac.denom << endl;
}

void tifci(){
  fraction frac;
  cin >> frac.fp >> frac.num >> frac.denom;
  frac.toimproperfraction();
  cout << frac.num << "/" << frac.denom << endl;
}

void dtfci(){
  fraction frac;
  double decimal;
  cin >> decimal;
  frac.decimaltofraction(decimal);
  cout << frac.num << "/" << frac.denom << endl;
}

void afci00(){
  fraction ffrac, sfrac;
  cin >> ffrac.num >> ffrac.denom >> sfrac.num >> sfrac.denom;
  ffrac = addfraction(ffrac, sfrac);
  cout << ffrac.num << "/" << ffrac.denom << " " << gcd(ffrac.num, ffrac.denom) << endl; 
}

void sfci00(){
  fraction ffrac, sfrac;
  cin >> ffrac.num >> ffrac.denom >> sfrac.num >> sfrac.denom;
  ffrac = subfraction(ffrac, sfrac);
  cout << ffrac.num << "/" << ffrac.denom << " " << gcd(ffrac.num, ffrac.denom) << endl; 
}

void mfci00(){
  fraction ffrac, sfrac;
  cin >> ffrac.num >> ffrac.denom >> sfrac.num >> sfrac.denom;
  ffrac = divfraction(ffrac, sfrac);
  cout << ffrac.num << "/" << ffrac.denom << " "<< gcd(ffrac.num, ffrac.denom) << endl; 
}

void dfci00(){
  fraction ffrac, sfrac;
  cin >> ffrac.num >> ffrac.denom >> sfrac.num >> sfrac.denom;
  ffrac = mulfraction(ffrac, sfrac);
  cout << ffrac.num << "/" << ffrac.denom << " "<< gcd(ffrac.num, ffrac.denom) << endl; 
}

int nglci(){
  string action;
  bool running = true;
  while (running){
    cin >> action;
    if (action == "add") addci();
    else if (action == "sub") subci();
    else if (action == "mul") mulci();
    else if (action == "div") divci();
    else if (action == "pow") powci();
    else if (action == "rod") rodci();
    else if (action == "gcd") gcdci();
    else if (action == "lcm") lcmci();
    else if (action == "sin") sinci();
    else if (action == "cos") cosci();
    else if (action == "tan") tanci();
    else if (action == "rt") rtci();
    else if (action == "rd") rdci();
    else if (action == "itm") itmci();
    else if (action == "tif") tifci();
    else if (action == "dtf") dtfci();
    else if (action == "af00") afci00();
    else if (action == "sf00") sfci00();
    else if (action == "mf00") mfci00();
    else if (action == "df00") dfci00();
    else if (action == "ex") return 0;
    else if (action == "cl") system("clear");
    else if (action == "graphics") return 1;
  }
  return 0;
}
